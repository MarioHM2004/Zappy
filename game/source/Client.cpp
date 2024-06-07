#include "Client.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

zappy::TCPSocket::TCPSocket(const std::string &ip, int port)
    : _sockfd(socket(AF_INET, SOCK_STREAM, 0))
{
    if (_sockfd < 0) {
        godot::UtilityFunctions::print(std::strerror(errno));
        return;
    }

    _address.sin_family = AF_INET;
    _address.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &_address.sin_addr) <= 0) {
        godot::UtilityFunctions::print(std::strerror(errno));
        return;
    }

    if (connect(_sockfd, (struct sockaddr *) &_address, sizeof(_address))
        < 0) {
        godot::UtilityFunctions::print(std::strerror(errno));
        return;
    }

    _ready = true;
}

zappy::TCPSocket::~TCPSocket()
{
    if (_sockfd >= 0) {
        close(_sockfd);
    }
    _ready = false;
}

zappy::TCPSocket::TCPSocket(TCPSocket &&other) noexcept
    : _sockfd(other._sockfd), _address(other._address)
{
    other._sockfd = -1;
    _ready = other._ready;
}

zappy::TCPSocket &zappy::TCPSocket::operator=(TCPSocket &&other) noexcept
{
    if (this != &other) {
        if (_sockfd >= 0) {
            close(_sockfd);
        }
        _sockfd = other._sockfd;
        _address = other._address;
        other._sockfd = -1;
        _ready = other._ready;
    }
    return *this;
}

template <typename T>
    requires std::is_trivially_copyable_v<T>
void zappy::TCPSocket::send_data(const T &data)
{
    if (send(_sockfd, &data, sizeof(T), 0) < 0) {
        godot::UtilityFunctions::print(std::strerror(errno));
        return;
    }
}

template <typename T>
    requires std::is_trivially_copyable_v<T>
T zappy::TCPSocket::receive_data()
{
    T data;
    if (recv(_sockfd, &data, sizeof(T), 0) < 0) {
        godot::UtilityFunctions::print(std::strerror(errno));
        return;
    }
    return data;
}

void zappy::TCPSocket::send_string(const std::string &message)
{
    if (send(_sockfd, message.c_str(), message.size(), 0) < 0) {
        godot::UtilityFunctions::print(std::strerror(errno));
        return;
    }
}

std::string zappy::TCPSocket::receive_string(size_t length)
{
    std::vector<char> buffer(length);
    ssize_t bytes_received = recv(_sockfd, buffer.data(), length, 0);
    if (bytes_received < 0) {
        godot::UtilityFunctions::print(std::strerror(errno));
        return "";
    }
    return std::string(buffer.data(), bytes_received);
}

void zappy::TCPSocket::process_with(
    zappy::FnCallback &callback, const std::string &command)
{
    std::future<void> sendFuture = async_send_string(command);
    sendFuture.get();

    std::future<std::string> receiveFuture = async_receive_string(BUFFER_SIZE);
    std::string response = receiveFuture.get();

    callback(response);
}

template <typename T>
    requires std::is_trivially_copyable_v<T>
std::future<void> zappy::TCPSocket::async_send_data(const T &data)
{
    return std::async(std::launch::async, [this, data]() {
        send_data(data);
    });
}

template <typename T>
    requires std::is_trivially_copyable_v<T>
std::future<T> zappy::TCPSocket::async_receive_data()
{
    return std::async(std::launch::async, [this]() {
        return receive_data<T>();
    });
}

std::future<void> zappy::TCPSocket::async_send_string(
    const std::string &message)
{
    return std::async(std::launch::async, [this, message]() {
        send_string(message);
    });
}

std::future<std::string> zappy::TCPSocket::async_receive_string(size_t length)
{
    return std::async(std::launch::async, [this, length]() {
        return receive_string(length);
    });
}

bool zappy::TCPSocket::is_ready() const
{
    return _ready;
}
