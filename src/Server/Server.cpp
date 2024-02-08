#include "Server.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>

Server::Server(int port) : listenPort(port), listenSocket(INVALID_SOCKET)
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
    int BUFFER_SIZE = 1024;
    while (true)
    {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
        {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        // Buffer
        char buffer[BUFFER_SIZE];
        ZeroMemory(buffer, 1024);

        // Receive data from client
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            std::cerr << "Error in recv(): " << WSAGetLastError() << std::endl;
        }
        else if (bytesReceived > 0)
        {
            std::cout << "Received request:\n"
                      << std::string(buffer, 0, bytesReceived) << std::endl;

            // HttpResponse response;
            // Send response
            const char *response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n" // Inform the client to close the connection
                "\r\n"
                "<html><body><h1>Hello, World!</h1></body></html>";

            int sendResult = send(clientSocket, response, strlen(response), 0);
            if (sendResult == SOCKET_ERROR)
            {
                std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
            }
            closesocket(clientSocket);
        }
    }
}