#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include <optional>
#include<regex>

#include "Http/HttpRequest.h"
#include "Http/HttpResponse.h"

using RouteParameters = std::unordered_map<std::string, std::string>;

typedef std::function<HttpResponse(const HttpRequest&, const RouteParameters&)> RouteHandler;

struct RoutePattern {
    std::regex pattern;
    RouteHandler handler;
    std::vector<std::string> paramNames;
};

class RouteConfig {
public:
    void addRoute(const std::string& method, const std::string& path, RouteHandler handler);
    std::optional<RouteHandler> getHandler(const std::string& method, const std::string& path, RouteParameters& params) const;

    // Util for converting dynamic parameter to specified type
    // To be upgraded in the future to support better conversion
    template<typename T>
    static std::optional<T> getParam(const RouteParameters& params, const std::string& key) {
        auto it = params.find(key);
        if (it != params.end()) {
            std::istringstream iss(it->second);
            T value;
            if (iss >> value) {
                return value;
            }
        }
        return std::nullopt;
    }

private:
    std::vector<RoutePattern> routes;

    // Util to convert path pattern to regex
    std::regex pathToRegex(const std::string& path, std::vector<std::string>& paramNames) const;
};
