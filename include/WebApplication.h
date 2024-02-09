#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include "BaseController.h"
#include "RouteConfig.h"
#include "Server/Server.h"

class WebApplication
{
public:
    WebApplication(int port);
    void run();

    template <typename ControllerType>
    void addController()
    {
        try
        {
            std::cout << "Adding controller" << std::endl;
            auto controller = std::make_shared<ControllerType>();
            controller->registerRoutes(*routeConfig);
            controllers.push_back(controller);
            std::cout << "Controller added" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception in addController: " << e.what() << std::endl;
        }
    }

private:
    std::vector<std::shared_ptr<BaseController>> controllers;
    std::shared_ptr<RouteConfig> routeConfig;
    std::unique_ptr<Server> server;
    int port;
};
