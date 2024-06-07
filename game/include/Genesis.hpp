#include "Client.hpp"
#include "World.hpp"
#include <godot_cpp/classes/camera3d.hpp>
#include <unordered_map>

#ifndef __GENESIS
    #define __GENESIS

namespace godot
{
    class Genesis : public Camera3D {
        GDCLASS(Genesis, Camera3D)

      private:
        double _ellapsed = 0;
        std::size_t _side = 3;
        std::unique_ptr<zappy::TCPSocket> _socket;
        std::unordered_map<std::string, zappy::FnCallback> _callbacks;
        std::unique_ptr<zappy::World> _world;

      protected:
        static void _bind_methods();

      public:
        Genesis();
        ~Genesis();

        void _ready() override;
        void _process(double delta) override;

        void dispatch(const std::string &command);
    };
} // namespace godot

#endif /* __GENESIS */
