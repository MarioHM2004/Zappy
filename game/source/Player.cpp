#include "Player.hpp"

zappy::Player::Player(std::size_t number, godot::Vector3 position)
    : _position(position), _number(number),
      _scene(godot::Object::cast_to<godot::PackedScene>(
          godot::ResourceLoader::get_singleton()->load(_path.c_str()).ptr())),
      _robot_scene(Object::cast_to<godot::Node3D>(_scene->instantiate())),
      _robot_body(
          Object::cast_to<godot::CharacterBody3D>(_robot_scene->get_child(0)))
{
    if (_robot_scene == nullptr) {
        godot::UtilityFunctions::print("Failed to instantiate robot scene");
        return;
    }

    _robot_scene->set_position(position);
}

std::size_t zappy::Player::get_number() const
{
    return _number;
}

std::size_t zappy::Player::get_level() const
{
    return _level;
}

const zappy::Inventory &zappy::Player::get_inventory() const
{
    return *_inventory;
}

const godot::Vector3 &zappy::Player::get_position() const
{
    return _position;
}

void zappy::Player::set_level(std::size_t level)
{
    _level = level;
}

void zappy::Player::set_position(godot::Vector3 position)
{
    if (_robot_body == nullptr) {
        return godot::UtilityFunctions::print("Robot body is null");
    }

    if (!_robot_body->has_method("move_to_coordinate")) {
        return godot::UtilityFunctions::print(
            "Method `move_to_coordinate` not found");
    }
    _position = position;
    _robot_body->call("move_to_coordinate", position);
}

void zappy::Player::spawn()
{
    if (_robot_scene->get_child_count() <= 0) {
        return godot::UtilityFunctions::print("Robot body is null");
    }

    get_tree()->get_root()->add_child(_robot_scene.get());
}
