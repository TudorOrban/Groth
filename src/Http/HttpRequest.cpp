#include "HttpRequest.h"
#include <sstream>
#include <vector>

HttpRequest::HttpRequest(const std::string& rawRequest) {
    parseRequest(rawRequest);
}

void HttpRequest::parseRequest(const std::string& rawRequest) {
    std::istringstream requestStream(rawRequest);
    std::string line;
    
    // Parse request line
    std::getline(requestStream, line);
    std::istringstream lineStream(line);
    lineStream >> method >> path;

    // Parse headers
    while (std::getline(requestStream, line) && line != "\r") {
        std::istringstream headerStream(line);
        std::string headerName;
        std::string headerValue;
        std::getline(headerStream, headerName, ':');
        std::getline(headerStream, headerValue);
        if (!headerName.empty() && !headerValue.empty()) {
            headers[headerName] = headerValue.substr(1); // Remove leading space
        }
    }

    // If Content-Length is present, read the body
    auto it = headers.find("Content-Length");
    if (it != headers.end()) {
        int length = std::stoi(it->second);
        char* buffer = new char[length + 1];
        requestStream.read(buffer, length);
        buffer[length] = '\0'; // Null-terminate the string
        body.assign(buffer, length);
        delete[] buffer;
    }
}

std::string HttpRequest::getMethod() const {
    return method;
}

std::string HttpRequest::getPath() const {
    return path;
}

std::string HttpRequest::getHeader(const std::string& name) const {
    auto it = headers.find(name);
    if (it != headers.end()) {
        return it->second;
    }
    return ""; // Return empty if not found
}

std::string HttpRequest::getBody() const {
    return body;
}