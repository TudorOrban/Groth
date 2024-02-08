#pragma once
#include <string>
#include <unordered_map>
#include <sstream>

class HttpResponse {
public:
    HttpResponse();

    void setStatusCode(int statusCode);
    void setHeader(const std::string& name, const std::string& value);
    void setBody(const std::string& body);
    std::string toString() const;

private:
    int statusCode;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};
