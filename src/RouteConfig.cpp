#include "RouteConfig.h"
#include <iostream>

void RouteConfig::addRoute(const std::string& method, const std::string& path, RouteHandler handler) {
    std::string key = method + path;
    routes[key] = handler;
    std::cout << "Route added: " << key << std::endl;
}

RouteHandler RouteConfig::getHandler(const std::string& method, const std::string& path) const {
    std::string key = method + path;
    std::cout << "Looking up route: " << key << std::endl;
    auto it = routes.find(key);
    if (it != routes.end()) {
        std::cout << "Route found: " << key << std::endl;
        return it->second;
    } else {
        std::cout << "Route not found: " << key << std::endl;
        return nullptr;
    }
}
