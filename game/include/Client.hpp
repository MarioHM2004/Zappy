#include <arpa/inet.h>
#include <cstring>
#include <functional>
#include <future>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#ifndef __CLIENT
    #define __CLIENT

namespace zappy
{
    using FnCallback = std::function<void(const std::string &)>;

    class TCPSocket {
      private:
        int _sockfd;
        bool _ready = false;
        struct sockaddr_in _address;

      public:
        static constexpr size_t BUFFER_SIZE = 2048;

        TCPSocket(const std::string &ip, int port);
        ~TCPSocket();

        TCPSocket(const TCPSocket &) = delete;
        TCPSocket &operator=(const TCPSocket &) = delete;

        TCPSocket(TCPSocket &&other) noexcept;

        TCPSocket &operator=(TCPSocket &&other) noexcept;

        template <typename T>
            requires std::is_trivially_copyable_v<T>
        void send_data(const T &data);

        template <typename T>
            requires std::is_trivially_copyable_v<T>
        T receive_data();

        void send_string(const std::string &message);

        std::string receive_string(size_t length);

        void process_with(FnCallback &processor, const std::string &command);

        template <typename T>
            requires std::is_trivially_copyable_v<T>
        std::future<void> async_send_data(const T &data);

        template <typename T>
            requires std::is_trivially_copyable_v<T>
        std::future<T> async_receive_data();

        std::future<void> async_send_string(const std::string &message);

        std::future<std::string> async_receive_string(size_t length);

        bool is_ready() const;
    };
} // namespace zappy

#endif /* __CLIENT */
