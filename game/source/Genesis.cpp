#include "Genesis.hpp"
#include <format>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void godot::Genesis::_bind_methods()
{
    ADD_SIGNAL(MethodInfo("hello", PropertyInfo(Variant::STRING, "value")));
}

godot::Genesis::Genesis()
{
    _callbacks = {
        {
            "msz",
            [this](const std::string &response) {
                std::string x = response.substr(4, response.find(' '));
                std::string y = response.substr(response.find(' ') + 1);
                _world =
                    std::make_unique<zappy::World>(std::stoi(x), std::stoi(y));
            },
        },
        {
            "echo",
            [](const std::string &response) {
                std::string message = response.substr(5);
                UtilityFunctions::print(
                    std::format("echo :: `{}`", message).c_str());
            },
        },
    };
}

godot::Genesis::~Genesis()
{
}

void godot::Genesis::_ready()
{
    if (Engine::get_singleton()->is_editor_hint()) {
        return set_process_mode(ProcessMode::PROCESS_MODE_DISABLED);
    }

    if (_socket == nullptr) {
        _socket = std::make_unique<zappy::TCPSocket>("127.0.0.1", 4242);
    }

    if (!_socket->is_ready()) {
        return UtilityFunctions::print("Socket is not ready, aborting...");
    }

    // TODO(jabolo): Add an alias to avoid hardcoding commands
    dispatch("msz");
}

void godot::Genesis::_process(double delta)
{
    _ellapsed += delta;

    if (_ellapsed > 1) {
        _ellapsed = 0;
    }
}

void godot::Genesis::dispatch(const std::string &payload)
{
    std::size_t it = payload.find(' ');
    std::string command =
        it == std::string::npos ? payload : payload.substr(0, it);

    if (_callbacks.find(command) == _callbacks.end()) {
        return UtilityFunctions::print(
            std::format("Command {} not found", command).c_str());
    }

    _socket->process_with(_callbacks.at(command), payload);
}
