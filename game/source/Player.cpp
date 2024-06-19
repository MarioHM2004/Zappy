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

    godot::Ref<godot::PackedScene> packed_scene =
        godot::Object::cast_to<godot::PackedScene>(resource.ptr());
    if (packed_scene.is_null()) {
        godot::UtilityFunctions::print("packed scene not found");
        return;
    }

    godot::Node3D *instantiated_scene =
        godot::Object::cast_to<godot::Node3D>(packed_scene->instantiate());
    if (instantiated_scene == NULL) {
        godot::UtilityFunctions::print("instantiated scene not found");
        return;
    }

    godot::CharacterBody3D *character_body =
        godot::Object::cast_to<godot::CharacterBody3D>(
            instantiated_scene->get_child(0));
    if (character_body == NULL) {
        godot::UtilityFunctions::print("character body not found");
        return;
    }

    instantiated_scene->set_position(position);

    double degrees = 90 * orientation;
    instantiated_scene->set_rotation_degrees(godot::Vector3(0, degrees, 0));

    _robot_scene = instantiated_scene;
    _robot_body = character_body;

    spawn();
}

std::size_t zappy::Player::get_number() const
{
    return _number;
}

std::size_t zappy::Player::get_level() const
{
    return _level;
}

zappy::Inventory &zappy::Player::get_inventory() const
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

void zappy::Player::set_frozen(bool frozen)
{
    _frozen = frozen;
}

bool zappy::Player::is_frozen() const
{
    return _frozen;
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
    // TODO(jabolo): Set orientation (maybe)
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

void zappy::Player::tint(godot::Color accent)
{
    if (_robot_body == nullptr) {
        return godot::UtilityFunctions::print("Robot body is null");
    }

    if (!_robot_body->has_method("tint")) {
        return godot::UtilityFunctions::print("Method `tint` not found");
    }

    godot::Color main_body(0, 0, 0, 255);
    godot::Color pupils(0, 0, 0, 255);
    godot::Color eye_bg(255, 255, 255, 255);

    _robot_body->call("tint", main_body, pupils, accent, eye_bg);
}
