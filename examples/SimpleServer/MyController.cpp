#include "MyController.h"
#include <iostream>
#include <string>

void MyController::registerRoutes(RouteConfig& routeConfig) {
    std::cout << "Registering routes in MyController" << std::endl;
    routeConfig.addRoute("GET", "/users", [](const HttpRequest& req, const RouteParameters& params) -> HttpResponse {
        HttpResponse res;
        res.setStatusCode(200);
        res.setHeader("Content-Type", "text/html");
        res.setBody("<html><body><h1>Welcome to MyController!</h1></body></html>");
        return res;
    });

    routeConfig.addRoute("GET", "/users/{userId}", [](const HttpRequest& req, const RouteParameters& params) -> HttpResponse {
        HttpResponse res;
        
        auto userIdOpt = RouteConfig::getParam<int>(params, "userId");
        if (userIdOpt) {
            res.setStatusCode(200);
            res.setHeader("Content-Type", "text/html");
            res.setBody("<html><body><h1>User ID: " + std::to_string(userIdOpt.value()) + "</h1></body></html>");
        } else {
            // Handle missing or invalid userId parameter
            res.setStatusCode(400); // Bad Request
            res.setBody("<html><body><h1>Error: User ID not provided or invalid</h1></body></html>");
        }

        return res;
    });
}
