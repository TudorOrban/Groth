#pragma once

#include <iostream>

#include "BaseController.h"

class MyOtherController : public BaseController {
public:
    MyOtherController() {
        std::cout << "Controller instantiated" << std::endl;
    }
    void registerRoutes(RouteConfig& routeConfig) override;
};