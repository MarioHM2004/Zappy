#include <arpa/inet.h>
#include <atomic>
#include <cstring>
#include <netinet/in.h>
#include <poll.h>
#include <queue>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <godot_cpp/classes/mutex.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/thread.hpp>

#ifndef __CLIENT
    #define __CLIENT

namespace zappy
{
    using FnCallback = std::function<void(const std::vector<std::string> &)>;

    class TCPSocket : public godot::Node {
      private:
        void setup_socket();
        void poll_socket();

        std::string _address;
        int _port;
        int _sockfd;
        bool _connected;
        std::atomic<bool> _stop;
        std::queue<std::string> _message_queue;

        godot::Ref<godot::Thread> _thread;
        godot::Ref<godot::Mutex> _mutex;

      public:
        TCPSocket(const std::string &address, int port);
        ~TCPSocket();

        void start_polling();
        void stop_polling();
        bool pop_message(std::string &msg);
        void send_message(const std::string &msg);
        bool connected() const;
        std::size_t message_count() const;
    };
} // namespace zappy

#endif /* __CLIENT */
