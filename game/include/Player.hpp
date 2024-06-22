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
    enum Orientation { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

    enum PlayerState {
        EGG = 0,
        PLAYER = 1,
        DEAD = 2,
    };

    class Player {
      private:
        godot::Vector3 _position;
        std::size_t _number;
        std::size_t _level = 0;
        Orientation _orientation = NORTH;
        std::string _path = "res://scenes/robot.tscn";
        std::string _egg_path = "res://scenes/sprites/egg.tscn";
        std::unique_ptr<Inventory> _inventory = std::make_unique<Inventory>();
        bool _frozen = false;
        godot::Color _accent;
        godot::Color _main_body = godot::Color(0, 0, 0, 255);
        godot::Color _pupils = godot::Color(0, 0, 0, 255);
        godot::Color _eye_bg = godot::Color(255, 255, 255, 255);

        godot::SceneTree *_tree;
        godot::Node3D *_robot_scene = nullptr;
        godot::CharacterBody3D *_robot_body = nullptr;
        godot::Node3D *_egg_scene = nullptr;

        PlayerState _state = EGG;

      public:
        Player(godot::SceneTree *tree, std::size_t number,
            godot::Vector3 position, Orientation orientation);

        std::size_t get_number() const;
        std::size_t get_level() const;
        Inventory &get_inventory() const;
        const godot::Vector3 &get_position() const;
        void set_frozen(bool frozen);
        bool is_frozen() const;

        void set_level(std::size_t level);
        void set_position(godot::Vector3 position);
        void set_orientation(Orientation orientation);
        Orientation get_orientation() const;
        void set_accent_color(godot::Color color);
        PlayerState get_state() const;

        void spawn();
        void lay_egg();
        void tint(godot::Color accent);
        void invocation(int level, bool init);
        void invocation_anim() const;
        void death_anim() const;
        void idle_anim() const;
        void drop_anim() const;
        void egg_anim() const;
        void destroy();

        static godot::Color get_accent_color(std::size_t level);
        static godot::Node3D *instantiate(std::string &path);
    };
} // namespace zappy

#endif /* __PLAYER */
