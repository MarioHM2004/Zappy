
#include <netinet/in.h>
#include <random>
#include <string>
#include <sys/select.h>
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
        void clientHandler(int bytes);
        void trim(std::string &s);
        void responseParser();
        void clientInteractions();
        std::string generate(int x, int y);

      private:
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
    };
} // namespace zappy

#endif /* __SERVER */
