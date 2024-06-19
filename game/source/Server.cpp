#include <algorithm>
#include <arpa/inet.h>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <format>
#include <iostream>
#include <netinet/in.h>
#include <random>
#include <sstream>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "../include/Server.hpp"

void zappy::Server::setServerSocket(int serverSocket)
{
    _serverSocket = serverSocket;
}

int zappy::Server::getServerSocket()
{
    return _serverSocket;
}

void zappy::Server::setMapSize(int x, int y)
{
    _x = x;
    _y = y;
}

int zappy::Server::createServerSocket(int port)
{
    struct sockaddr_in serverAddr;

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0)
        std::cerr << "Socket creation failed\n";
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(
            _serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr))
        == -1)
        std::cerr << "bind\n";
    listen(_serverSocket, 1024);
    return _serverSocket;
}

void zappy::Server::newClient()
{
    socklen_t addrSize = sizeof(_clientAddr);

    int newSocket =
        accept(_serverSocket, (struct sockaddr *) &_clientAddr, &addrSize);
    if (newSocket < 0)
        std::cerr << "accept error\n";
    FD_SET(newSocket, &_currentSockets);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (_clientSockets[i] == 0) {
            _clientSockets[i] = newSocket;
            _initialDataSent[i] = false; // Reset initial data sent flag
            sendInitialData(newSocket);  // Send initial data immediately
            break;
        }
    }
}

std::string zappy::Server::generate(int x, int y)
{
    std::stringstream msg;
    msg << "bct " << x << " " << y;
    std::random_device rd;
    rng.seed(rd());
    std::uniform_int_distribution<int> dist(0, 5);
    for (int i = 0; i < 7; ++i) {
        msg << " " << dist(rng);
    }
    return msg.str() + "\n";
}

void zappy::Server::sendMapSize(int clientSocket)
{
    std::stringstream msg;
    msg << "msz " << _x << " " << _y << std::endl;
    std::string message = msg.str();
    ssize_t bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
    std::cout << message.c_str();
    if (bytesSent < 0) {
        std::cerr << "Error sending map size to client.\n";
        close(clientSocket);
        FD_CLR(clientSocket, &_currentSockets);
    }
}

void zappy::Server::sendMapContent(int clientSocket)
{
    for (int i = 0; i <= _x; i++) {
        for (int j = 0; j <= _y; j++) {
            std::string msg = generate(i, j);
            ssize_t bytesSent = send(clientSocket, msg.c_str(), msg.size(), 0);
            std::cout << msg.c_str();
            if (bytesSent < 0) {
                std::cerr << "Error sending map content to client.\n";
                close(clientSocket);
                FD_CLR(clientSocket, &_currentSockets);
                return;
            }
        }
    }
}

void zappy::Server::addNewPlayer(int clientSocket)
{
    for (int n = 0; n < playerCount; ++n) {
        std::stringstream msg;
        msg << "pnw " << n << " " << 0 << " " << n << " 2 1 " << n << std::endl;
        std::string message = msg.str();
        ssize_t bytesSent =
            send(clientSocket, message.c_str(), message.size(), 0);
        std::cout << message.c_str();
        if (bytesSent < 0) {
            std::cerr << "Error sending map size to client.\n";
            close(clientSocket);
            FD_CLR(clientSocket, &_currentSockets);
        }
    }
}

void zappy::Server::initTeams(int clientSocket)
{
    for (int n = 0; n < playerCount; ++n) {
        std::stringstream msg;
        msg << "tna " << n << std::endl;
        std::string message = msg.str();
        ssize_t bytesSent =
            send(clientSocket, message.c_str(), message.size(), 0);
        std::cout << message.c_str();
        if (bytesSent < 0) {
            std::cerr << "Error sending map size to client.\n";
            close(clientSocket);
            FD_CLR(clientSocket, &_currentSockets);
        }
    }
}

void zappy::Server::sendWelcome(int clientSocket)
{
    std::stringstream msg;
    msg << "WELCOME" << std::endl;
    std::string message = msg.str();
    ssize_t bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
    std::cout << message.c_str();
    if (bytesSent < 0) {
        std::cerr << "Error sending map size to client.\n";
        close(clientSocket);
        FD_CLR(clientSocket, &_currentSockets);
    }
}

void zappy::Server::movePlayer(int clientSocket)
{
    for (int n = 0; n < playerCount; ++n) {
        std::stringstream msg;
        msg << "ppo " << n << " " << _x -1 - n << " " << _y - 1 - n << " " << 0 << std::endl;
        std::string message = msg.str();
        ssize_t bytesSent =
            send(clientSocket, message.c_str(), message.size(), 0);
        std::cout << message.c_str();
        if (bytesSent < 0) {
            std::cerr << "Error sending map size to client.\n";
            close(clientSocket);
            FD_CLR(clientSocket, &_currentSockets);
        }
    }
}

void zappy::Server::sendInitialData(int clientSocket)
{
    sendWelcome(clientSocket);
    sendMapSize(clientSocket);
    // sendMapContent(clientSocket);
    initTeams(clientSocket);
    addNewPlayer(clientSocket);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    movePlayer(clientSocket);
    // move to

    // 0, 0
    // 0, 1

    // _x - 1 - n, 0
    // _y - 1 - n, 0
}

void zappy::Server::sendOtherData(int clientSocket)
{
    // Example: Send some other message or data
    // std::string msg = "other_data " + std::to_string(rand() % 100) + "\n";
    // ssize_t bytesSent = send(clientSocket, msg.c_str(), msg.size(), 0);
    // if (bytesSent < 0) {
    //    std::cerr << "Error sending other data to client.\n";
    //    close(clientSocket);
    //    FD_CLR(clientSocket, &_currentSockets);
    //}
}

void zappy::Server::sendPeriodicData()
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        int clientSocket = _clientSockets[i];
        if (clientSocket != 0 && _initialDataSent[i]) {
            sendOtherData(clientSocket);
        }
    }
}

void zappy::Server::runServer()
{
    FD_ZERO(&_currentSockets);
    FD_SET(_serverSocket, &_currentSockets);
    for (int i = 0; i < FD_SETSIZE; i++) {
        _clientSockets[i] = 0;
        _initialDataSent[i] = false; // Initialize initial data sent flag
    }

    while (1) {
        _readySockets = _currentSockets;
        if (select(FD_SETSIZE, &_readySockets, NULL, NULL, NULL) < 0)
            std::cerr << "select error";

        if (FD_ISSET(_serverSocket, &_readySockets))
            newClient();

        sendPeriodicData();
        std::this_thread::sleep_for(
            std::chrono::seconds(5)); // Adjust interval as needed
    }
}

int main(int ac, char **av)
{
    zappy::Server server;
    server.setMapSize(9, 9);
    int serverSocket = server.createServerSocket(std::atoi(av[1]));
    server.setServerSocket(serverSocket);
    server.runServer();
    close(server.getServerSocket());
    return 0;
}
