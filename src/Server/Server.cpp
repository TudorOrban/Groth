#include "Server/Server.h"
#include "Http/HttpRequest.h"
#include "Http/HttpResponse.h"
#include "Thread/ThreadPool.h"

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <chrono>
#include <atomic>

Server::Server(int port, std::shared_ptr<RouteConfig> routeConfig)
    : listenPort(port), listenSocket(INVALID_SOCKET), routeConfig(routeConfig)
{
    setupSocket();
}

Server::~Server()
{
    closesocket(listenSocket);
    WSACleanup();
}

void Server::setupSocket()
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        exit(1);
    }

    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET)
    {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(1);
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(listenPort);

    if (bind(listenSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }
}

void Server::run()
{
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }
    std::cout << "Server listening on port " << listenPort << std::endl;
    acceptConnections();
}

void Server::acceptConnections() const
{
    ThreadPool pool(4);

    while (true)
    {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
        {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }


        pool.enqueue([this, clientSocket]() {
            this->handleConnection(clientSocket);
        });
    }
}

void Server::handleConnection(SOCKET clientSocket) const {
    // Buffer
    char buffer[Server::BUFFER_SIZE];
    ZeroMemory(buffer, Server::BUFFER_SIZE);

    // Receive data from client
    int bytesReceived = recv(clientSocket, buffer, Server::BUFFER_SIZE, 0);
    if (bytesReceived == SOCKET_ERROR)
    {
        std::cerr << "Error in recv(): " << WSAGetLastError() << std::endl;
    }
    else if (bytesReceived > 0)
    {
        // Parse request from the client
        std::string requestStr(buffer, bytesReceived);
        HttpRequest request(requestStr);

        // Prepare to collect dynamic route parameters
        RouteParameters params;

        // Try to find a handler for the request
        auto handlerResult = routeConfig->getHandler(request.getMethod(), request.getPath(), params);

        HttpResponse response;
        if (handlerResult.has_value())
        {
            response = handlerResult.value()(request, params);
        }
        else
        {
            // Return 404
            response.setStatusCode(404);
            response.setHeader("Content-Type", "text/html");
            response.setBody("<html><body><h1>404 Not Found</h1></body></html>");
        }

        // Send response to the client
        std::string responseStr = response.toString();
        send(clientSocket, responseStr.c_str(), responseStr.length(), 0);
    }

    closesocket(clientSocket);
}