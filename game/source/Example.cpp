#include <arpa/inet.h>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#define PORT 4242

void send_random_data(int new_socket)
{
    std::srand(std::time(0));
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::cerr << "Sending random data to the client...\n";

        int random_number = std::rand() % 100;
        std::string message = "{ { " + std::to_string(random_number) + " } }";

        int s = send(new_socket, message.c_str(), message.size(), 0);

        if (s == -1) {
            perror("send");
            close(new_socket);
            exit(EXIT_FAILURE);
        }
    }
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    if ((new_socket = accept(
             server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen))
        < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Client connected!" << std::endl;

    std::thread(send_random_data, new_socket).detach();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
