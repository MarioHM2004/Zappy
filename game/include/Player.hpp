#include <cstddef>
#include <memory>
#include "Inventory.hpp"
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#ifndef __PLAYER
    #define __PLAYER

namespace zappy
{
    class Player : public godot::Node {
      private:
        godot::Vector3 _position;
        std::size_t _number;
        std::size_t _level = 0;
        std::string _path = "res://scenes/robot.tscn";
        std::unique_ptr<Inventory> _inventory;
        std::unique_ptr<godot::PackedScene> _scene;
        std::unique_ptr<godot::Node3D> _robot_scene;
        std::unique_ptr<godot::CharacterBody3D> _robot_body;

      public:
        Player(std::size_t number, godot::Vector3 position);

        std::size_t get_number() const;
        std::size_t get_level() const;
        const Inventory &get_inventory() const;
        const godot::Vector3 &get_position() const;

        void set_level(std::size_t level);
        void set_position(godot::Vector3 position);

        void spawn();
    };
} // namespace zappy

#endif /* __PLAYER */
