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
    godot::Node3D *egg = instantiate(_egg_path);
    if (egg == nullptr) {
        return;
    }

    _orientation = orientation;
    _egg_scene = egg;
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
        return;
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
    _egg_scene->queue_free();
    _egg_scene = nullptr;
    _state = PlayerState::PLAYER;

    godot::Node3D *robot = instantiate(_path);
    if (robot == nullptr) {
        godot::UtilityFunctions::print("instantiated scene is null");
        return;
    }

    godot::CharacterBody3D *character_body =
        godot::Object::cast_to<godot::CharacterBody3D>(robot->get_child(0));
    if (character_body == NULL) {
        godot::UtilityFunctions::print("character body not found");
        return;
    }

    robot->set_position(_position);
    robot->scale_object_local(godot::Vector3(0.5, 0.5, 0.5));

    _robot_scene = robot;
    _robot_body = character_body;

    if (_robot_scene->get_child_count() <= 0) {
        return godot::UtilityFunctions::print("Robot body is malformed");
    }

    tint(_accent);
    _tree->get_root()->add_child(_robot_scene);
    look_at(_orientation);
}

void zappy::Player::lay_egg()
{
    _egg_scene->set_scale(godot::Vector3(0.5, 0.5, 0.5));
    _egg_scene->set_position(
        godot::Vector3(_position.x + .25, 1.75, _position.z - .25));
    _tree->get_root()->add_child(_egg_scene);
}

void zappy::Player::set_orientation(Orientation orientation)
{
    _orientation = orientation;
    look_at(_orientation);
}

zappy::Orientation zappy::Player::get_orientation() const
{
    return _orientation;
}

void zappy::Player::tint(godot::Color accent)
{
    if (_state != PlayerState::PLAYER) {
        return;
    }

    if (_robot_body == nullptr) {
        return;
    }

    if (!_robot_body->has_method("tint")) {
        return godot::UtilityFunctions::print("Method `tint` not found");
    }

    _accent = accent;
    _robot_body->call("tint", _main_body, _pupils, _accent, _eye_bg);
}

void zappy::Player::invocation(int level, bool init)
{
    if (_state != PlayerState::PLAYER) {
        return;
    }

    if (_robot_body == nullptr) {
        return;
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
}

void zappy::Player::invocation_anim() const
{
    if (_robot_body == nullptr) {
        return;
    }
    if (!_robot_body->has_method("invocation_anim")) {
        return godot::UtilityFunctions::print(
            "Method `invocation_anim` not found");
    }
    _robot_body->call("invocation_anim");
}

void zappy::Player::egg_anim() const
{
    if (_robot_body == nullptr) {
        return;
    }
    if (!_robot_body->has_method("egg_anim")) {
        return godot::UtilityFunctions::print("Method `egg_anim` not found");
    }
    _robot_body->call("egg_anim");
}

void zappy::Player::death_anim() const
{
    if (_robot_body == nullptr) {
        return;
    }
    if (!_robot_body->has_method("death_anim")) {
        return godot::UtilityFunctions::print("Method `death_anim` not found");
    }
    _robot_body->call("death_anim");
}

void zappy::Player::idle_anim() const
{
    if (_robot_body == nullptr) {
        return;
    }
    if (!_robot_body->has_method("idle_anim")) {
        return godot::UtilityFunctions::print("Method `idle_anim` not found");
    }
    _robot_body->call("idle_anim");
}

void zappy::Player::drop_anim() const
{
    if (_robot_body == nullptr) {
        return;
    }
    if (!_robot_body->has_method("drop_anim")) {
        return godot::UtilityFunctions::print("Method `drop_anim` not found");
    }
    _robot_body->call("drop_anim");
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

void zappy::Player::destroy()
{
    if (_robot_scene != nullptr) {
        _robot_scene->queue_free();
    }
    if (_egg_scene != nullptr) {
        _egg_scene->queue_free();
    }
}

godot::Node3D *zappy::Player::instantiate(std::string &path)
{
    godot::Ref<godot::Resource> resource =
        godot::ResourceLoader::get_singleton()->load(path.c_str());

    if (resource.is_null()) {
        godot::UtilityFunctions::print("Resource not found");
        return nullptr;
    }

    godot::Ref<godot::PackedScene> packed_scene =
        godot::Object::cast_to<godot::PackedScene>(resource.ptr());
    if (packed_scene.is_null()) {
        godot::UtilityFunctions::print("packed scene not found");
        return nullptr;
    }

    godot::Node3D *instantiated_scene =
        godot::Object::cast_to<godot::Node3D>(packed_scene->instantiate());
    if (instantiated_scene == NULL) {
        godot::UtilityFunctions::print("instantiated scene not found");
        return nullptr;
    }

    return instantiated_scene;
}

void zappy::Player::set_accent_color(godot::Color color)
{
    _accent = color;
}

zappy::PlayerState zappy::Player::get_state() const
{
    return _state;
}

void zappy::Player::look_at(Orientation orientation)
{
    if (_robot_body == nullptr) {
        return;
    }
    if (!_robot_body->has_method("rotate_to")) {
        return godot::UtilityFunctions::print("Method `rotate_to` not found");
    }

    godot::Vector3 target;

    switch (orientation) {
        case NORTH: target = godot::Vector3(0, 0, -1); break;
        case EAST: target = godot::Vector3(1, 0, 0); break;
        case SOUTH: target = godot::Vector3(0, 0, 1); break;
        case WEST: target = godot::Vector3(-1, 0, 0); break;
        default: return godot::UtilityFunctions::print("Invalid orientation");
    }

    _robot_body->call("rotate_to", target);
}
