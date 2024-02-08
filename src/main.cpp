#include<iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Server/Server.h"

int main() {
    try {
        // Initialize server on port 8080
        Server myServer(8080);

        // Run server to start listening for connections
        myServer.run();


    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception occurred." << std::endl;
        return 1;
    }





    return 0;
}


// WSADATA wsaData;
//     int iResult;

//     // Initialize Winsock
//     iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//     if (iResult != 0) {
//         std::cerr << "WSAStartup failed: " << iResult << std::endl;
//         return 1;
//     } else {
//         std::cout << "WSAStartup success" << std::endl;
//     }

//     // Create a socket for the server to listen for incoming connections
//     SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if (listenSocket == INVALID_SOCKET) {
//         std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
//         WSACleanup();
//         return 1;
//     } else {
//         std::cout << "Socket created" << std::endl;
//     }

//     // Bind the socket to a local address and port
//     sockaddr_in serverAddr;
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_addr.s_addr = INADDR_ANY; // Listen on all available network interfaces
//     serverAddr.sin_port = htons(8080);

//     if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
//         std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
//         closesocket(listenSocket);
//         WSACleanup();
//         return 1;
//     }

//     // Listen for incoming connections
//     if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
//         std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
//         closesocket(listenSocket);
//         WSACleanup();
//         return 1;
//     }

//     std::cout << "Server listening on port 8080..." << std::endl;

//     const int BUFFER_SIZE = 1024;

//     // Accept incoming connections
//     while (true) {
//         // Accept a client socket
//         SOCKET clientSocket = accept(listenSocket, NULL, NULL);
//         if (clientSocket == INVALID_SOCKET) {
//             std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
//             closesocket(listenSocket);
//             WSACleanup();
//             return 1;
//         }

//         // Receive incoming HTTP request
//         char buffer[BUFFER_SIZE];
//         int receivedResult = recv(clientSocket, buffer, BUFFER_SIZE, 0);
//         if (receivedResult == SOCKET_ERROR) {
//             std::cerr << "Received failed: " << WSAGetLastError() << std::endl;
//             closesocket(clientSocket);
//             continue;
//         }

//         // Process received data
//         std::cout << "Received HTTP request:\n" << buffer << std::endl;

//         // Send response
//         const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>";
//         int sendResult = send(clientSocket, response, strlen(response), 0);
//         if (sendResult == SOCKET_ERROR) {
//             std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
//         }


//         // Close client socket
//         closesocket(clientSocket);
//     }


//     // Clean up
//     WSACleanup();