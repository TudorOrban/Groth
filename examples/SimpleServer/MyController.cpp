#include "MyController.h"
#include <iostream>

void MyController::registerRoutes(RouteConfig& routeConfig) {
    std::cout << "Registering routes in MyController" << std::endl;
    routeConfig.addRoute("GET", "/users", [](const HttpRequest& req) -> HttpResponse {
        HttpResponse res;
        res.setStatusCode(200);
        res.setHeader("Content-Type", "text/html");
        res.setBody("<html><body><h1>Welcome to MyController!</h1></body></html>");
        return res;
    });
}
