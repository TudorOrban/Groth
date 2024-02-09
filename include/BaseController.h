#pragma once
#include "RouteConfig.h"

class BaseController {
public: 
    virtual void registerRoutes(RouteConfig& routeConfig) = 0;
};