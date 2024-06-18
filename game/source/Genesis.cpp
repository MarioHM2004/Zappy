#include "Genesis.hpp"
#include <algorithm>
#include <format>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "Common.hpp"
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector3.hpp>

void godot::Genesis::_bind_methods()
{
    // TODO(jabolo): fix string_view mismatch to use signals from Common.hpp
    ADD_SIGNAL(MethodInfo("error", PropertyInfo(Variant::STRING, "value")));
    ADD_SIGNAL(MethodInfo("wsize", PropertyInfo(Variant::INT, "x"),
        PropertyInfo(Variant::INT, "y")));
}

godot::Genesis::Genesis()
{
    _callbacks = {
        {
            zappy::Constants::Commands::MAP_SIZE,
            [this](const std::vector<std::string> &response) {
                int x = std::stoi(response.at(1));
                int y = std::stoi(response.at(2));

                _world = std::make_unique<zappy::World>(x, y);
                emit_signal("wsize", x, y);
            },
        },
        {
            zappy::Constants::Commands::TILE_CONTENT,
            [this](const std::vector<std::string> &response) {
                std::size_t x = std::stoi(response.at(1));
                std::size_t y = std::stoi(response.at(2));

                std::vector<std::size_t> resources;
                std::transform(response.begin() + 3, response.end(),
                    std::back_inserter(resources),
                    [](const std::string &elem) {
                        return std::stoi(elem);
                    });

                for (auto it = resources.begin(); it != resources.end();
                     ++it) {
                    _world->set_resource(x, y,
                        static_cast<zappy::ResourceType>(
                            std::distance(resources.begin(), it)),
                        *it);
                }
            },
        },
        {
            zappy::Constants::Commands::ECHO,
            [](const std::vector<std::string> &response) {
                std::string message = response.at(1);

                UtilityFunctions::print(
                    std::format(">> echo: `{}`", message).c_str());
            },
        },
        {
            zappy::Constants::Commands::SERVER_OPEN,
            [this](const std::vector<std::string> &_response) {
                _socket->send_message(zappy::Constants::TEAM_NAME);
            },
        },
        {
            zappy::Constants::Commands::TIME_UNIT_MODIFICATION,
            [this](const std::vector<std::string> &response) {
                // TODO(jabolo): verify if this is the correct command
                _socket->time_unit(std::stoi(response.at(1)));
            },
        },
        {
            zappy::Constants::Commands::TIME_UNIT_REQUEST,
            [this](const std::vector<std::string> &response) {
                // TODO(jabolo): verify if this is the correct command
                _socket->time_unit(std::stoi(response.at(1)));
            },
        },
        {
            zappy::Constants::Commands::PLAYER_INVENTORY,
            [](const std::vector<std::string> &response) {
                // TODO(jabolo): find player and update inventory
            },
        },
        {
            zappy::Constants::Commands::PLAYER_JOINED,
            [this](const std::vector<std::string> &response) {
                std::size_t number = std::stoi(response.at(1));
                std::size_t x = std::stoi(response.at(2));
                std::size_t y = std::stoi(response.at(3));
                zappy::Orientation orientation =
                    static_cast<zappy::Orientation>(std::stoi(response.at(4)));
                std::size_t level = std::stoi(response.at(5));
                std::string team = response.at(6);

                UtilityFunctions::print(
                    std::format(">> player joined: `{}`", number).c_str());

                if (_teams.find(team) == _teams.end()) {
                    return UtilityFunctions::print(
                        std::format(">> team not found: `{}`", team).c_str());
                }

                std::shared_ptr<zappy::Player> player =
                    std::make_unique<zappy::Player>(
                        get_tree(), number, Vector3(x, 1, y), orientation);

                player->set_level(level);

                _players[number] = player;
                _teams.at(team)->add_player(player);
            },
        },
        {
            zappy::Constants::Commands::PLAYER_LEVEL,
            [](const std::vector<std::string> &response) {
                // TODO(jabolo): find player and update level
            },
        },
        {
            zappy::Constants::Commands::TEAM_NAMES,
            [this](const std::vector<std::string> &response) {
                std::string name = response.at(1);

                if (_teams.find(name) != _teams.end()) {
                    return UtilityFunctions::print(
                        std::format(">> team already exists: `{}`", name)
                            .c_str());
                }

                _teams[name] = std::make_unique<zappy::Team>(name);
            },
        },
        {
            zappy::Constants::Commands::PLAYER_POSITION,
            [this](const std::vector<std::string> &response) {
                std::shared_ptr<zappy::Player> player =
                    _players.at(std::stoi(response.at(1)));
                std::size_t x = std::stoi(response.at(2));
                std::size_t y = std::stoi(response.at(3));

                player->set_position(Vector3(x, 1, y));
            },
        },
        {
            zappy::Constants::Commands::PLAYER_LEVEL,
            [this](const std::vector<std::string> &response) {
                std::shared_ptr<zappy::Player> player =
                    _players.at(std::stoi(response.at(1)));
                std::size_t level = std::stoi(response.at(2));

                player->set_level(level);
            },
        },
        {
            zappy::Constants::Commands::PLAYER_INVENTORY,
            [this](const std::vector<std::string> &response) {
                std::size_t number = std::stoi(response.at(1));
                std::size_t x = std::stoi(response.at(2));
                std::size_t y = std::stoi(response.at(3));

                std::array<std::size_t, 7> resources;

                std::transform(response.begin() + 4, response.end(),
                    resources.begin(), [](const std::string &elem) {
                        return std::stoi(elem);
                    });

                std::shared_ptr<zappy::Player> player = _players.at(number);

                player->set_position(Vector3(x, 1, y));
                player->get_inventory().set_all(resources);
            },
        },
        {
            zappy::Constants::Commands::SERVER_KO,
            [](const std::vector<std::string> &_response) {
                UtilityFunctions::print(">> critical error: server KO");
            },
        },
    };
}

void godot::Genesis::_ready()
{
    if (Engine::get_singleton()->is_editor_hint()) {
        _socket = nullptr;
        Input::get_singleton()->set_mouse_mode(
            Input::MouseMode::MOUSE_MODE_VISIBLE);
        return set_process_mode(ProcessMode::PROCESS_MODE_DISABLED);
    } else {
        Engine::get_singleton()->set_max_fps(60);
        Input::get_singleton()->set_mouse_mode(
            Input::MouseMode::MOUSE_MODE_HIDDEN);
        set_process_mode(ProcessMode::PROCESS_MODE_INHERIT);
    }

    if (_socket == nullptr) {
        _socket = std::make_unique<zappy::TCPSocket>("127.0.0.1", 4242);
    }

    if (!_socket->connected()) {
        emit_signal("error", std::strerror(errno));
        return UtilityFunctions::print("Socket is not ready, aborting...");
    }

    _socket->start_polling();
}

void godot::Genesis::_process(double delta)
{
    _ellapsed += delta;

    if (_ellapsed > 0.2) {
        tick();
        _ellapsed = 0;
    }

    Vector3 move_dir;

    if (_movement & FORWARD)
        move_dir += Vector3(0, 0, -1);
    if (_movement & BACKWARD)
        move_dir += Vector3(0, 0, 1);
    if (_movement & LEFT)
        move_dir += Vector3(-1, 0, 0);
    if (_movement & RIGHT)
        move_dir += Vector3(1, 0, 0);
    if (_movement & UP)
        move_dir += Vector3(0, 1, 0);
    if (_movement & DOWN)
        move_dir += Vector3(0, -1, 0);

    if (move_dir.length_squared() > 0) {
        translate_object_local(move_dir.normalized() * delta * 10);
    }

    Vector3 pos = get_position();

    if (pos.y < 1) {
        pos.y = 1;
        set_position(pos);
    }
}

void godot::Genesis::_input(const Ref<InputEvent> &event)
{
    if (auto key = Object::cast_to<InputEventKey>(*event)) {
        key_input(key);
    } else if (auto mouse = Object::cast_to<InputEventMouseMotion>(*event)) {
        mouse_input(mouse);
    }
}

void godot::Genesis::key_input(const Ref<InputEventKey> &key)
{
    if (!key.is_valid()) {
        return;
    }

    bool is_pressed = key->is_pressed();

    auto set_movement = [this, &is_pressed](int flag) {
        if (is_pressed) {
            _movement |= flag;
        } else {
            _movement &= ~flag;
        }
    };

    switch (key->get_keycode()) {
        case KEY_W: set_movement(FORWARD); break;
        case KEY_S: set_movement(BACKWARD); break;
        case KEY_A: set_movement(LEFT); break;
        case KEY_D: set_movement(RIGHT); break;
        case KEY_SHIFT: set_movement(DOWN); break;
        case KEY_SPACE: set_movement(UP); break;
        case KEY_P:
        case KEY_ESCAPE:
            Input::get_singleton()->set_mouse_mode(is_pressed
                    ? (key->get_keycode() == KEY_ESCAPE
                              ? Input::MouseMode::MOUSE_MODE_VISIBLE
                              : Input::MouseMode::MOUSE_MODE_HIDDEN)
                    : Input::get_singleton()->get_mouse_mode());
            break;
        default: break;
    }
}

void godot::Genesis::mouse_input(const Ref<InputEventMouseMotion> &mouse)
{
    if (!mouse.is_valid()) {
        return;
    }

    if (mouse->get_relative().length() == 0) {
        return;
    }

    if (Input::get_singleton()->get_mouse_mode()
        == Input::MouseMode::MOUSE_MODE_VISIBLE) {
        return;
    }

    Vector3 camera_rotation = get_rotation();
    camera_rotation.x += mouse->get_relative().y / -_speed;
    camera_rotation.y += mouse->get_relative().x / -_speed;

    float pi_half = M_PI / 2;
    camera_rotation.x = std::clamp(camera_rotation.x, -pi_half, pi_half);

    set_rotation(camera_rotation);
}

void godot::Genesis::dispatch(const std::string &payload)
{
    _socket->send_message(payload);
}

void godot::Genesis::dispatch(const std::string_view &command)
{
    return dispatch(std::string(command));
}

void godot::Genesis::tick()
{
    if (!_socket->connected() || _socket->message_count() == 0) {
        return;
    }

    std::string message;

    while (_socket->pop_message(message)) {
        std::istringstream iss(message);
        std::vector<std::string> response;

        for (std::string token; std::getline(iss, token, ' ');) {
            response.push_back(token);
        }

        if (response.empty()) {
            continue;
        }

        std::string command = response.at(0);

        std::transform(command.begin(), command.end(), command.begin(),
            [](unsigned char c) {
                return std::tolower(c);
            });

        if (_callbacks.find(command) != _callbacks.end()) {
            _callbacks.at(command)(response);
        } else {
            UtilityFunctions::print(
                std::format(">> unknown command: `{}`", command).c_str());
        }
    }
}
