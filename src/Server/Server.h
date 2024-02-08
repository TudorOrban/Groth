#pragma once

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

class Server {
public:
    Server(int port);
    ~Server();
    void run();

private:
    int listenPort;
    SOCKET listenSocket;
    void setupSocket();
    void acceptConnections() const;
};