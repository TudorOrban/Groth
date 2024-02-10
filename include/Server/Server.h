#pragma once

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory>

#include "RouteConfig.h"

class Server {
public:
    Server(int port, std::shared_ptr<RouteConfig> routeConfig);
    ~Server();
    void run();

    static constexpr int BUFFER_SIZE = 1024;

private:
    int listenPort;
    SOCKET listenSocket;
    std::shared_ptr<RouteConfig> routeConfig;
    void setupSocket();
    void acceptConnections() const;
    void handleConnection(SOCKET clientSocket) const;
};