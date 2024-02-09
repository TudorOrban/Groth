#pragma once
#include <memory>
#include <vector>
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
        auto controller = std::make_shared<ControllerType>();
        controller->registerRoutes(*routeConfig);
        controllers.push_back(controller);
    }

private:
    std::vector<std::shared_ptr<BaseController>> controllers;
    std::shared_ptr<RouteConfig> routeConfig;
    std::unique_ptr<Server> server;
    int port;
};
