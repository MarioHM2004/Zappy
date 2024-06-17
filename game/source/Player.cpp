#include "Player.hpp"
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector3.hpp>

zappy::Player::Player(godot::SceneTree *tree, std::size_t number,
    godot::Vector3 position, Orientation orientation)
    : _position(position), _number(number), _orientation(orientation),
      _tree(tree)
{
    godot::Ref<godot::Resource> resource =
        godot::ResourceLoader::get_singleton()->load(_path.c_str());

    if (resource.is_null()) {
        godot::UtilityFunctions::print("Resource not found");
        return;
    }

    // TODO(jabolo): Add null checks
    godot::Ref<godot::PackedScene> packed_scene =
        godot::Object::cast_to<godot::PackedScene>(resource.ptr());
    godot::Node3D *instantiated_scene =
        godot::Object::cast_to<godot::Node3D>(packed_scene->instantiate());
    godot::CharacterBody3D *character_body =
        godot::Object::cast_to<godot::CharacterBody3D>(
            instantiated_scene->get_child(0));

    // TODO(jabolo): Fix this setting position incorrectly
    instantiated_scene->set_position(position);

    _robot_scene = instantiated_scene;
    _robot_body = character_body;

    spawn();
}

zappy::Player::~Player()
{
    // TODO: Free resources
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

    _tree->get_root()->add_child(_robot_scene);
}

void zappy::Player::set_orientation(Orientation orientation)
{
    _orientation = orientation;
}

zappy::Orientation zappy::Player::get_orientation() const
{
    return _orientation;
}
