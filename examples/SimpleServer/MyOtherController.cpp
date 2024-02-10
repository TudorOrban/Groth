#include "MyOtherController.h"
#include <iostream>

void MyOtherController::registerRoutes(RouteConfig& routeConfig) {
    std::cout << "Registering routes in MyOtherController" << std::endl;
    routeConfig.addRoute("GET", "/organizations", [](const HttpRequest& req) -> HttpResponse {
        HttpResponse res;
        res.setStatusCode(200);
        res.setHeader("Content-Type", "text/html");
        res.setBody("<html><body><h1>Welcome to MyOtherController!</h1></body></html>");
        return res;
    });
}
