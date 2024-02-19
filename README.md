Groth is a mini-library for building REST API's in C++, currently available only for Windows servers. It employs a thread pool for efficiently handling concurrent requests, and supports dynamic route parameters with limited type checking.

### Usage
Groth is not yet packaged as a library, but you can use it by following these steps:
1. Ensure you have a C++ compiler that supports the C++ 17 standard and CMake installed.
2. Fetch the repository into your project's directory and link it by adding a line in the root CMakeLists such as:
```
add_subdirectory(examples/SimpleServer)
```
3. Create a WebApplication as shown in the [examples](https://github.com/TudorOrban/Groth/tree/main/examples/SimpleServer), specifying the port:
```c++
#include "WebApplication.h"

int main() {
    WebApplication app(8080);
}
```
4. To add routes, create a Controller that extends BaseController:
```c++
// MyController.h
class MyController : public BaseController {
public:
    MyController() {
        std::cout << "Controller instantiated" << std::endl;
    }
    void registerRoutes(RouteConfig& routeConfig) override;
};
```
and configure your routes like this:
```c++
// MyController.cpp
void MyController::registerRoutes(RouteConfig& routeConfig) {
    std::cout << "Registering routes in MyController" << std::endl;
    routeConfig.addRoute("GET", "/users", [](const HttpRequest& req, const RouteParameters& params) -> HttpResponse {
        HttpResponse res;
        res.setStatusCode(200);
        res.setHeader("Content-Type", "text/html");
        res.setBody("<html><body><h1>Welcome to MyController!</h1></body></html>");
        return res;
    });
}
```
5. Register your controller and run the server:
```c++
#include "WebApplication.h"
#include "MyController.h"

int main() {
    WebApplication app(8080);
    app.addController<MyController>();
    app.run();
    return 0;
}
```
6. Finally, create a build folder in the root of Groth and run from there: `cmake ..`, `cmake --build . --config Release`. Then go to `build\YourProject\Release` and run `.\YourProject.exe`.

### Performance
A performance test has been run with [Apache JMeter](https://jmeter.apache.org/) on an AMD Ryzen 5 4600H with 16GB of memory. The results are available [here](https://github.com/TudorOrban/Groth/tree/main/tests/JMeter). The thread group made 50000 concurrent calls to a dynamic route that returns a simple HTML with the received parameter. The aggregate report:

![Aggregate](tests/JMeter/aggregate.csv "Aggregate report")

shows a good overall performance (124ms), with 50% of the requests being handled under 20ms, and and average of 1000 requests handled per second. On the other hand, the 99% percentile suggests a long-tail problem, partially attributed to the server cold start (see [response time graph](https://github.com/TudorOrban/Groth/blob/main/tests/JMeter/screenshots/GrothResponseTimeGraph.png)), and the high error rate is indicative of some underlying issues that will soon be addressed. See the [graph results](https://github.com/TudorOrban/Groth/blob/main/tests/JMeter/screenshots/GrothGraphResults.png) as well.