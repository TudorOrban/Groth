#include "MyOtherController.h"
#include <iostream>

void MyOtherController::registerRoutes(RouteConfig& routeConfig) {
    std::cout << "Registering routes in MyOtherController" << std::endl;
    routeConfig.addRoute("GET", "/organizations", [](const HttpRequest& req, const RouteParameters& params) -> HttpResponse {
        HttpResponse res;
        res.setStatusCode(200);
        res.setHeader("Content-Type", "text/html");
        res.setBody("<html><body><h1>Welcome to MyOtherController!</h1></body></html>");
        return res;
    });

    routeConfig.addRoute("GET", "/organizations/{organizationId}", [](const HttpRequest& req, const RouteParameters& params) -> HttpResponse {
        HttpResponse res;
        res.setStatusCode(200);
        res.setHeader("Content-Type", "text/html");

        // Check if the organizationId parameter exists and use it
        if (params.find("organizationId") != params.end()) {
            std::string organizationId = params.at("organizationId");
            res.setBody("<html><body><h1>Organization ID: " + organizationId + "</h1></body></html>");
        } else {
            // In case the parameter was not found (which shouldn't happen if the route was matched correctly)
            res.setStatusCode(400); // Bad Request
            res.setBody("<html><body><h1>Error: Organization ID not provided</h1></body></html>");
        }

        return res;
    });
}
