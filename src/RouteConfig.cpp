#include "RouteConfig.h"
#include <iostream>
#include <sstream>

void RouteConfig::addRoute(const std::string& method, const std::string& path, RouteHandler handler) {
    // Convert path pattern to regex and extract parameter names
    std::vector<std::string> paramNames;
    std::regex pattern = pathToRegex(path, paramNames);

    // Create a RoutePattern object and add it to the routes
    RoutePattern routePattern{pattern, handler, paramNames};
    routes.push_back(routePattern);

    std::cout << "Route added: " << method + path << std::endl;
}

std::optional<RouteHandler> RouteConfig::getHandler(const std::string& method, const std::string& path, RouteParameters& params) const {
    for (const auto& routePattern : routes) {
        // Check if the request path matches the pattern
        std::smatch matches;
        if (std::regex_match(path, matches, routePattern.pattern)) {
            // If it matches, extract dynamic parameters
            for (size_t i = 0; i < routePattern.paramNames.size(); ++i) {
                // Matches are 1-indexed, matches[0] is the full match
                params[routePattern.paramNames[i]] = matches[i + 1];
            }
            return routePattern.handler;
        }
    }

    std::cout << "Route not found: " << method + path << std::endl;
    return std::nullopt; // No handler was found
}

std::regex RouteConfig::pathToRegex(const std::string& path, std::vector<std::string>& paramNames) const {
    std::string regexPattern = "^";
    std::istringstream pathStream(path);
    std::string segment;

    while (std::getline(pathStream, segment, '/')) {
        if (segment.empty()) continue;

        if (segment.front() == '{' && segment.back() == '}') {
            std::string paramName = segment.substr(1, segment.length() - 2);
            paramNames.push_back(paramName);
            regexPattern += "/([^/]+)";
        } else {
            regexPattern += "/" + segment;
        }
    }
    
    regexPattern += "$";
    return std::regex(regexPattern);
}

