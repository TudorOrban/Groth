#include "WebApplication.h"
#include "MyController.h"
#include "MyOtherController.h"

int main() {
    WebApplication app(8080);
    app.addController<MyController>();
    app.addController<MyOtherController>();
    app.run();
    return 0;
}