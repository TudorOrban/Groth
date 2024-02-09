#include "WebApplication.h"
#include "MyController.h"

int main() {
    WebApplication app(8080);
    app.addController<MyController>();
    app.run();
    return 0;
}