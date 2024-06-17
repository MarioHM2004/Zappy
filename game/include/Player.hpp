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
    enum Orientation { NORTH = 1, EAST = 2, SOUTH = 3, WEST = 4 };

    class Player {
      private:
        godot::Vector3 _position;
        std::size_t _number;
        std::size_t _level = 0;
        Orientation _orientation = NORTH;
        std::string _path = "res://scenes/robot.tscn";
        std::unique_ptr<Inventory> _inventory;

        godot::SceneTree *_tree;
        godot::Node3D *_robot_scene = nullptr;
        godot::CharacterBody3D *_robot_body = nullptr;

      public:
        Player(godot::SceneTree *tree, std::size_t number,
            godot::Vector3 position, Orientation orientation);
        ~Player();

        std::size_t get_number() const;
        std::size_t get_level() const;
        const Inventory &get_inventory() const;
        const godot::Vector3 &get_position() const;

        void set_level(std::size_t level);
        void set_position(godot::Vector3 position);
        void set_orientation(Orientation orientation);
        Orientation get_orientation() const;

        void spawn();
    };
} // namespace zappy

#endif /* __PLAYER */
