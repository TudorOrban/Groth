#include "Http/HttpResponse.h"

HttpResponse::HttpResponse(): statusCode(200) {}

void HttpResponse::setStatusCode(int code) {
    statusCode = code;
}

void HttpResponse::setHeader(const std::string& name, const std::string& value) {
    headers[name] = value;
}

void HttpResponse::setBody(const std::string& bodyContent) {
    body = bodyContent;
}

std::string HttpResponse::toString() const {
    std::ostringstream responseStream;
    responseStream << "HTTP/1.1 " << statusCode << " OK\r\n";
    for (const auto& header : headers) {
        responseStream << header.first << ": " << header.second << "\r\n";
    }
    responseStream << "\r\n" << body;
    return responseStream.str();
}