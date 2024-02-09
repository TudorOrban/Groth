#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include "Http/HttpRequest.h"
#include "Http/HttpResponse.h"

typedef std::function<HttpResponse(const HttpRequest&)> RouteHandler;

class RouteConfig {
public:
    void addRoute(const std::string& method, const std::string& path, RouteHandler handler);
    RouteHandler getHandler(const std::string& method, const std::string& path) const;
private:
    std::unordered_map<std::string, RouteHandler> routes;
};