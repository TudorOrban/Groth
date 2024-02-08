#pragma once
#include <string>
#include <unordered_map>

class HttpRequest {
public:
    HttpRequest(const std::string& rawRequest);
    std::string getMethod() const;
    std::string getPath() const;
    std::string getHeader(const std::string& name) const;
    std::string getBody() const;

private:
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

    void parseRequest(const std::string& rawRequest);
};