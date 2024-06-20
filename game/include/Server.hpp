#include <array>
#include <chrono>
#include <netinet/in.h>
#include <random>
#include <string>
#include <sys/select.h>
#include <thread>
#include <vector>

#ifndef __SERVER
    #define __SERVER

namespace zappy
{
    class Server {
      public:
        int getServerSocket();
        void setServerSocket(int serverSocket);
        void setMapSize(int x, int y);
        int createServerSocket(int port);
        void runServer();
        void newClient();
        void clientActivity();
        void clientConnection(int clientSocket);
        std::string generate(int x, int y);

        void sendWelcome(int clientSocket);
        void sendMapSize(int clientSocket);
        void sendMapContent(int clientSocket);
        void initTeams(int clientSocket);
        void addNewPlayer(int clientSocket);
        void movePlayer(int clientSocket);
        void sendInitialData(int clientSocket);
        void sendPeriodicData();
        void sendOtherData(int clientSocket);
        void incantation(int clientSocket);
        void incantationEnd(int clientSocket);

      private:
        int playerCount = 9;
        int _x = 10;
        int _y = 10;
        struct sockaddr_in _clientAddr;
        int _serverSocket;
        int _clientSockets[FD_SETSIZE];
        int _clientSocket;
        std::string _clientResponse;
        fd_set _currentSockets;
        fd_set _readySockets;
        std::vector<std::string> _inputs;
        std::mt19937 rng;

        std::array<bool, FD_SETSIZE> _initialDataSent;
    };
} // namespace zappy

#endif /* __SERVER */
