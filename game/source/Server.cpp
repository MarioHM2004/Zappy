#include <asm-generic/socket.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <random>
#include <sstream>
#include <string>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <system_error>
#include <unistd.h>
#include <vector>

#include "../include/Server.hpp"

using namespace server;

void Server::setServerSocket(int serverSocket)
{
    _serverSocket = serverSocket;
}

int Server::getServerSocket()
{
    return _serverSocket;
}

void Server::setMapSize(int x, int y)
{
}

int Server::createServerSocket(int port)
{
    struct sockaddr_in serverAddr;

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0)
        std::cerr << "Socket creation failed\n";
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(_serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
        std::cerr << "bind\n";
    listen(_serverSocket, 1024);
    return _serverSocket;

}

void Server::newClient()
{
    socklen_t addrSize = sizeof(_clientAddr);

    int newSocket = accept(_serverSocket, (struct sockaddr *)&_clientAddr, &addrSize);
    if (newSocket < 0)
        std::cerr << "accept error\n";
    std::cout << "A new bot has connected" << std::endl;
    FD_SET(newSocket, &_currentSockets);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (_clientSockets[i] == 0) {
            _clientSockets[i] = newSocket;
            break;
        }
    }
}

std::string Server::generate(int x, int y)
{
    std::stringstream msg;
    msg << "mct " << x << " " << y;
    std::random_device rd;
    rng.seed(rd());
    std::uniform_int_distribution<int> dist(0, 100);
    for (int i = 0; i < 7; ++i) {
        msg << " " << dist(rng);
    }
    return msg.str() + "\n";
}

void Server::clientInteractions()
{
    if (_inputs.empty()) {
        std::cerr << "input should be not empty";
    }
    if (_inputs[0] == "msz") {
        std::stringstream msg;
        msg << "msz " << _x << " " << _y << std::endl;
        std::string message = msg.str();
        ssize_t bytesSent = send(_clientSocket, message.c_str(), message.size(), 0);
        if (bytesSent < 0) {
            std::cerr << "Error sending data to client.\n";
        }
    }
    if (_inputs[0] == "mct") {
        for (int i = 0; i <= _x; i++) {
            for (int j = 0; j <= _y; j++) {
                std::string msg = generate(i, j);
                ssize_t bytesSent = send(_clientSocket, msg.c_str(), msg.size(), 0);
                if (bytesSent < 0) {
                    std::cerr << "Error sending data to client.\n";
                }
            }
        }
    }
}

void Server::trim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void Server::responseParser()
{
    _inputs.clear();
    trim(_clientResponse);
    std::istringstream iss(_clientResponse);
    std::string input;

    while (std::getline(iss, input, ' ') ) {
        if (!input.empty())
            _inputs.push_back(input);
    }
    clientInteractions();
    _clientResponse.clear();
}

void Server::clientHandler(int bytes)
{
    if (bytes <= 0) {
        if (bytes < 0)
            std::cerr << "read failed\n";
        close(_clientSocket);
        FD_CLR(_clientSocket, &_currentSockets);
    } else {
        std::cout << "response is -->" << _clientResponse << std::endl;
        responseParser();
    }
}

void Server::clientConnection(int clientSocket)
{
    int bytes = 0;
    char buffer[1024];

    _clientSocket = clientSocket;
    _clientResponse.clear();
    bytes = read(_clientSocket, buffer, sizeof(buffer));
    if (bytes < 0) {
        std::cerr << "Error reading from client socket.\n";
        close(_clientSocket);
        return;
    }
    _clientResponse += std::string(buffer, bytes);
    clientHandler(bytes);
}


void Server::clientActivity()
{
    int clientSocket = 0;

    for (int i = 0; i < FD_SETSIZE; i++) {
        clientSocket = _clientSockets[i];
        if (clientSocket > 0 && FD_ISSET(clientSocket, &_readySockets))
            clientConnection(clientSocket);
    }
}

void Server::runServer()
{
    FD_ZERO(&_currentSockets);
    FD_SET(_serverSocket, &_currentSockets);
    for (int i = 0; i < FD_SETSIZE; i++)
        _clientSockets[i] = 0;
    while (1) {
        _readySockets = _currentSockets;
        if (select(FD_SETSIZE, &_readySockets, NULL, NULL, NULL) < 0)
            std::cerr << "select error";
        if (FD_ISSET(_serverSocket, &_readySockets))
            newClient();
        clientActivity();
    }
}
int main(int ac, char **av)
{
    Server server;
    server.setMapSize(10, 10);
    int serverSocket = server.createServerSocket(std::atoi(av[1]));
    server.setServerSocket(serverSocket);
    server.runServer();
    close(server.getServerSocket());
    return 0;
}
