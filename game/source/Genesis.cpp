#include "Genesis.hpp"
#include <algorithm>
#include <format>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "Common.hpp"
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/vector3.hpp>

void godot::Genesis::_bind_methods()
{
    ADD_SIGNAL(MethodInfo("error", PropertyInfo(Variant::STRING, "value")));
    ADD_SIGNAL(MethodInfo("wsize", PropertyInfo(Variant::INT, "x"),
        PropertyInfo(Variant::INT, "y")));
    ADD_SIGNAL(MethodInfo("resource", PropertyInfo(Variant::STRING, "kind"),
        PropertyInfo(Variant::INT, "x"), PropertyInfo(Variant::INT, "y")));
    ADD_SIGNAL(MethodInfo("gameover"));
    ClassDB::bind_method(
        D_METHOD("handle_settings"), &Genesis::handle_settings);
    ClassDB::bind_method(D_METHOD("handle_console"), &Genesis::handle_console);
    ClassDB::bind_method(D_METHOD("handle_focus"), &Genesis::handle_focus);
    ADD_SIGNAL(
        MethodInfo("last_command", PropertyInfo(Variant::STRING, "command")));
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
                int x = std::stoi(response.at(1));
                int y = std::stoi(response.at(2));

                std::vector<std::size_t> resources;
                std::transform(response.begin() + 3, response.end(),
                    std::back_inserter(resources),
                    [](const std::string &elem) {
                        return std::stoi(elem);
                    });

                for (auto it = resources.begin(); it != resources.end();
                     ++it) {
                    zappy::ResourceType kind =
                        static_cast<zappy::ResourceType>(
                            std::distance(resources.begin(), it));
                    if (*it > 0) {
                        emit_signal("resource",
                            zappy::World::resource_to_string(kind).c_str(), x,
                            y);
                    }
                    _world->set_resource(x, y, kind, *it);
                }
            },
        },
        {
            zappy::Constants::Commands::ECHO,
            [](const std::vector<std::string> &response) {
                std::string message = response.at(1);

                UtilityFunctions::print(
                    std::format("echo: `{}`", message).c_str());
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
                _socket->time_unit(std::stoi(response.at(1)));
            },
        },
        {
            zappy::Constants::Commands::TIME_UNIT_REQUEST,
            [this](const std::vector<std::string> &response) {
                _socket->time_unit(std::stoi(response.at(1)));
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
                    std::format("player joined: `{}`", number).c_str());

                if (_teams.find(team) == _teams.end()) {
                    emit_signal("error",
                        std::format("team not found: `{}`", team).c_str());
                    return;
                }

                if (_players.find(number) != _players.end()) {
                    emit_signal("error",
                        std::format("player already exists: `{}`", number)
                            .c_str());
                    return;
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
            zappy::Constants::Commands::TEAM_NAMES,
            [this](const std::vector<std::string> &response) {
                std::string name = response.at(1);

                if (_teams.find(name) != _teams.end()) {
                    emit_signal("error",
                        std::format("team already exists: `{}`", name)
                            .c_str());
                    return;
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
            [this](const std::vector<std::string> &_response) {
                emit_signal(
                    "error", "Critical error, server is not responding");
            },
        },
        {
            zappy::Constants::Commands::PLAYER_EXPULSION,
            [this](const std::vector<std::string> &response) {
                std::size_t id = std::stoi(response.at(1));

                auto p = _players.find(id);

                if (p == _players.end()) {
                    emit_signal(
                        "error", std::format("could not find {}", id).c_str());
                    return;
                }

                std::for_each(_teams.begin(), _teams.end(),
                    [id](const std::pair<const std::string,
                        std::unique_ptr<zappy::Team>> &team) {
                        team.second->remove_player(id);
                    });

                p->second->destroy();

                _players.erase(p);
            },
        },
        {
            zappy::Constants::Commands::START_INCANTATION,
            [this](const std::vector<std::string> &response) {
                std::vector<std::shared_ptr<zappy::Player>> players;
                std::size_t x = std::stoi(response.at(1));
                std::size_t y = std::stoi(response.at(2));
                std::size_t level = std::stoi(response.at(3));
                std::string key = std::format("{}:{}", x, y);

                std::transform(response.begin() + 4, response.end(),
                    std::back_inserter(players),
                    [this](const std::string &elem) {
                        return _players.at(std::stoi(elem));
                    });

                std::for_each(
                    players.begin(), players.end(), [&level](auto &player) {
                        player->invocation(level, true);
                    });

                _incantations[key] = players;
            },
        },
        {
            zappy::Constants::Commands::END_INCANTATION,
            [this](const std::vector<std::string> &response) {
                std::size_t x = std::stoi(response.at(1));
                std::size_t y = std::stoi(response.at(2));
                std::size_t result = std::stoi(response.at(3));
                std::string key = std::format("{}:{}", x, y);
                std::vector<std::shared_ptr<zappy::Player>> players =
                    _incantations.at(key);

                std::for_each(
                    players.begin(), players.end(), [&result](auto &player) {
                        player->invocation(result, false);
                    });

                _incantations.erase(key);
            },
        },
        {
            zappy::Constants::Commands::END_GAME,
            [this](const std::vector<std::string> &response) {
                std::string team = response.at(1);

                if (team == "GRAPHIC") {
                    emit_signal("gameover");
                    return;
                }

                auto t = _teams.find(team);

                if (t == _teams.end()) {
                    emit_signal("error",
                        std::format("could not find team {}", team).c_str());
                    return;
                }

                t->second->clear_players();
                _teams.erase(t);
            },
        },
        {
            zappy::Constants::Commands::EGG_CONNECTION,
            [this](const std::vector<std::string> &response) {
                std::size_t id = std::stoi(response.at(1));

                auto player = _players.find(id);
                if (player == _players.end()) {
                    emit_signal("error",
                        std::format("could not find player {}", id).c_str());
                    return;
                }

                player->second->spawn();
            },
        },
        {
            zappy::Constants::Commands::EGG_DEATH,
            [this](const std::vector<std::string> &response) {
                std::size_t id = std::stoi(response.at(1));

                auto player = _players.find(id);
                if (player == _players.end()) {
                    emit_signal("error",
                        std::format("could not find player {}", id).c_str());
                    return;
                }

                if (player->second->get_state() == zappy::PlayerState::EGG) {
                    player->second->destroy();
                    _players.erase(player);
                }
            },
        },
        {
            zappy::Constants::Commands::UNKNOWN_COMMAND,
            [this](const std::vector<std::string> &_response) {
                emit_signal(
                    "error", "Unknown command, please check your input");
            },
        },
        {
            zappy::Constants::Commands::BAD_PARAMETER,
            [this](const std::vector<std::string> &_response) {
                emit_signal(
                    "error", "Invalid parameter, please check your input");
            },
        },
        {
            zappy::Constants::Commands::EGG_LAYING,
            [this](const std::vector<std::string> &response) {
                std::size_t id = std::stoi(response.at(1));
                std::shared_ptr<zappy::Player> player = _players.at(id);

                emit_signal("resource",
                    zappy::World::resource_to_string(zappy::EGGY).c_str(),
                    player->get_position().x, player->get_position().z);
                player->egg_anim();
            },
        },
        {
            zappy::Constants::Commands::RESOURCE_DROPPING,
            [this](const std::vector<std::string> &response) {
                std::size_t id = std::stoi(response.at(1));
                std::shared_ptr<zappy::Player> player = _players.at(id);
                player->drop_anim();
            },
        },
        {
            zappy::Constants::Commands::RESOURCE_COLLECTING,
            [this](const std::vector<std::string> &response) {
                std::size_t id = std::stoi(response.at(1));
                std::shared_ptr<zappy::Player> player = _players.at(id);
                player->drop_anim();
            },
        },
        {
            zappy::Constants::Commands::PLAYER_DEATH,
            [this](const std::vector<std::string> &response) {
                std::size_t id = std::stoi(response.at(1));

                auto p = _players.find(id);

                if (p == _players.end()) {
                    emit_signal(
                        "error", std::format("could not find {}", id).c_str());
                    return;
                }

                p->second->death_anim();
            },
        },
        {
            zappy::Constants::Commands::EGG_LAID,
            [](const std::vector<std::string> &response) {
                UtilityFunctions::print("egg laid");
            },
        },
        {
            zappy::Constants::Commands::SERVER_MESSAGE,
            [](const std::vector<std::string> &response) {
                std::string message = response.at(1);

                UtilityFunctions::print(
                    std::format("server message: `{}`", message).c_str());
            },
        },
        {
            zappy::Constants::Commands::BROADCAST,
            [](const std::vector<std::string> &response) {
                std::string message = response.at(1);

                UtilityFunctions::print(
                    std::format("broadcast: `{}`", message).c_str());
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

    Control *settings = Object::cast_to<Control>(
        get_tree()->get_root()->get_child(0)->get_child(4));

    if (settings) {
        settings->set_visible(true);
        Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
        settings->connect("server_address", Callable(this, "handle_settings"));
    }

    Control *console = Object::cast_to<Control>(
        get_tree()->get_root()->get_child(0)->get_child(5));

    if (console) {
        console->set_visible(false);
        console->connect("server_command", Callable(this, "handle_console"));
        console->connect("console_focus", Callable(this, "handle_focus"));
    }
}

void godot::Genesis::_process(double delta)
{
    if (!_setup) {
        return;
    }

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
    if (!_setup || _console_focused) {
        return;
    }

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

void godot::Genesis::handle_settings(String address, String port)
{
    if (_setup) {
        emit_signal("error", "Socket already setup!");
        return;
    }

    if (address.is_empty()) {
        _address = "127.0.0.1";
    } else {
        CharString utf8_str = address.utf8();
        const char *c_str = utf8_str.get_data();
        if (c_str && *c_str != '\0') {
            _address = std::string(c_str);
        } else {
            _address = "127.0.0.1";
        }
    }

    if (port.is_empty()) {
        _port = 4242;
    } else {
        CharString port_utf8_str = port.utf8();
        _port = std::stoi(std::string(port_utf8_str.get_data()));
    }

    _socket = std::make_unique<zappy::TCPSocket>(_address, _port);

    if (!_socket->connected()) {
        emit_signal("error", std::strerror(errno));
        emit_signal("error", "Socket is not ready, aborting...");
        return;
    }

    Input::get_singleton()->set_mouse_mode(
        Input::MouseMode::MOUSE_MODE_HIDDEN);

    Control *settings = Object::cast_to<Control>(
        get_tree()->get_root()->get_child(0)->get_child(4));

    if (settings) {
        settings->set_visible(false);
    }

    Control *console = Object::cast_to<Control>(
        get_tree()->get_root()->get_child(0)->get_child(5));

    if (console) {
        console->set_visible(true);
    }

    _setup = true;
    _socket->start_polling();
}

void godot::Genesis::handle_console(String command)
{
    CharString utf8_str = command.utf8();
    const char *c_str = utf8_str.get_data();
    std::string str = std::string(c_str);

    if (str.starts_with("!")) {
        str = str.substr(1);
        std::vector<std::string> response;
        std::istringstream iss(str);

        for (std::string token; std::getline(iss, token, ' ');) {
            response.push_back(token);
        }

        if (response.empty()) {
            return;
        }

        std::string command = response.at(0);

        std::transform(command.begin(), command.end(), command.begin(),
            [](unsigned char c) {
                return std::tolower(c);
            });

        if (_callbacks.find(command) != _callbacks.end()) {
            _callbacks.at(command)(response);
        } else {
            emit_signal("error",
                std::format("unknown command: `{}`", command).c_str());
            return;
        }
    }

    dispatch(str);
}

void godot::Genesis::handle_focus(bool active)
{
    _console_focused = active;
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

        emit_signal("last_command", message.c_str());

        std::string command = response.at(0);

        std::transform(command.begin(), command.end(), command.begin(),
            [](unsigned char c) {
                return std::tolower(c);
            });

        if (_callbacks.find(command) != _callbacks.end()) {
            _callbacks.at(command)(response);
        } else {
            emit_signal("error",
                std::format("unknown command: `{}`", command).c_str());
            return;
        }
    }
}
