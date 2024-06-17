#include "Client.hpp"
#include <thread>
#include <godot_cpp/variant/utility_functions.hpp>

zappy::TCPSocket::TCPSocket(const std::string &address, int port)
    : _address(address), _port(port), _connected(false), _stop(false)
{
    setup_socket();
}

zappy::TCPSocket::~TCPSocket()
{
    stop_polling();
    close(_sockfd);
}

void zappy::TCPSocket::start_polling()
{
    _mutex.instantiate();
    _thread.instantiate();
    _thread->start(callable_mp(this, &TCPSocket::poll_socket),
        godot::Thread::PRIORITY_NORMAL);
}

void zappy::TCPSocket::stop_polling()
{
    _stop = true;
    _thread.unref();
}

bool zappy::TCPSocket::pop_message(std::string &msg)
{
    _mutex->lock();
    if (!_message_queue.empty()) {
        msg = _message_queue.front();
        _message_queue.pop();
        _mutex->unlock();
        return true;
    }
    _mutex->unlock();
    return false;
}

void zappy::TCPSocket::setup_socket()
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0) {
        return godot::UtilityFunctions::print(std::strerror(errno));
    }

    sockaddr_in serv_addr;
    std::memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(_address.c_str());
    serv_addr.sin_port = htons(_port);

    if (::connect(_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
        < 0) {
        _connected = false;
        return godot::UtilityFunctions::print(std::strerror(errno));
    } else {
        _connected = true;
    }
}

void zappy::TCPSocket::poll_socket()
{
    if (!_connected) {
        return;
    }

    while (!_stop) {
        char buffer[1024] = {0};
        int n = read(_sockfd, buffer, 1024);
        if (n < 0) {
            godot::UtilityFunctions::print(std::strerror(errno));
            continue;
        }

        std::string message(buffer, n);
        _mutex->lock();
        _message_queue.push(message);
        _mutex->unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void zappy::TCPSocket::send_message(const std::string &msg)
{
    if (!_connected) {
        return godot::UtilityFunctions::print(std::strerror(errno));
    }

    int n = write(_sockfd, msg.c_str(), msg.size());
    if (n < 0) {
        return godot::UtilityFunctions::print(std::strerror(errno));
    }
}

bool zappy::TCPSocket::connected() const
{
    return _connected;
}

std::size_t zappy::TCPSocket::message_count() const
{
    return _message_queue.size();
}
