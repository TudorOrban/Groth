#include "WebApplication.h"
#include <iostream>

WebApplication::WebApplication(int port)
    : routeConfig(std::make_shared<RouteConfig>()), port(port) {}

void WebApplication::run()
{
    server = std::make_unique<Server>(port);

    try
    {
        std::cout << "Server running on port " << port << "..." << std::endl;
        server->run(); // Start the server
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred." << std::endl;
    }
}
