#include <memory>
#include <string>
#include "Client.hpp"
#include "Team.hpp"
#include "World.hpp"
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/transform2d.hpp>
#include <unordered_map>

#ifndef __GENESIS
    #define __GENESIS

namespace godot
{
    enum MovementDirections {
        FORWARD = 1 << 0,
        BACKWARD = 1 << 1,
        LEFT = 1 << 2,
        RIGHT = 1 << 3,
        UP = 1 << 4,
        DOWN = 1 << 5
    };

    class Genesis : public Camera3D {
        GDCLASS(Genesis, Camera3D)

      private:
        double _ellapsed = 0;
        std::size_t _side = 3;
        std::unique_ptr<zappy::TCPSocket> _socket;
        std::unordered_map<std::string_view, zappy::FnCallback> _callbacks;
        std::unique_ptr<zappy::World> _world;
        Vector3 _target_position;
        Vector3 _move_direction;
        int _movement = 0;
        const float _speed = 150;
        std::unordered_map<std::string, std::unique_ptr<zappy::Team>> _teams;

      protected:
        static void _bind_methods();

      public:
        Genesis();
        ~Genesis() = default;

        void _ready() override;
        void _process(double delta) override;
        void _input(const Ref<InputEvent> &event) override;

        void dispatch(const std::string &command);
        void dispatch(const std::string_view &command);
        void tick();
        void key_input(const Ref<InputEventKey> &key);
        void mouse_input(const Ref<InputEventMouseMotion> &mouse);
    };
} // namespace godot

#endif /* __GENESIS */
