#pragma once

#include <iostream>

#include "BaseController.h"

class MyController : public BaseController {
public:
    MyController() {
        std::cout << "Controller instantiated" << std::endl;
    }
    void registerRoutes(RouteConfig& routeConfig) override;
};