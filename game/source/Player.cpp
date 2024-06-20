#include "Player.hpp"
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/variant/color.hpp>
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
    instantiated_scene->scale_object_local(godot::Vector3(0.5, 0.5, 0.5));
    character_body->rotate_object_local(
        godot::Vector3(0, 1, 0), 90 * orientation);

    _robot_scene = instantiated_scene;
    _robot_body = character_body;
    _orientation = orientation;

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

    _accent = accent;
    _robot_body->call("tint", _main_body, _pupils, _accent, _eye_bg);
}

void zappy::Player::invocation(int level, bool init)
{
    if (_robot_body == nullptr) {
        return godot::UtilityFunctions::print("Robot body is null");
    }

    _frozen = init;

    invocation_anim();

    if (init) {
        _robot_body->call(
            "tint", godot::Color(1, 1, 1), _pupils, _accent, _eye_bg);
        _level = level;
        return;
    }

    _main_body = get_accent_color(_level);
    _robot_body->call("tint", _main_body, _pupils, _accent, _eye_bg);

    idle_anim();
}

void zappy::Player::invocation_anim() const
{
    if (_robot_body == nullptr) {
        return godot::UtilityFunctions::print("Robot body is null");
    }
    if (!_robot_body->has_method("invocation_anim")) {
        return godot::UtilityFunctions::print(
            "Method `invocation_anim` not found");
    }
    _robot_body->call("invocation_anim");
}

void zappy::Player::death_anim() const
{
    if (_robot_body == nullptr) {
        return godot::UtilityFunctions::print("Robot body is null");
    }
    if (!_robot_body->has_method("death_anim")) {
        return godot::UtilityFunctions::print("Method `death_anim` not found");
    }
    _robot_body->call("death_anim");
}

void zappy::Player::idle_anim() const
{
    if (_robot_body == nullptr) {
        return godot::UtilityFunctions::print("Robot body is null");
    }
    if (!_robot_body->has_method("idle_anim")) {
        return godot::UtilityFunctions::print("Method `idle_anim` not found");
    }
    _robot_body->call("idle_anim");
}

godot::Color zappy::Player::get_accent_color(std::size_t level)
{
    if (level == 6) {
        return godot::Color(1, 1, 1, 1);
    }

    if (level > 6) {
        return godot::Color(1, 0, 0, 1);
    }

    return godot::Color(level * 0.17, level * 0.17, level * 0.17, 1);
}
