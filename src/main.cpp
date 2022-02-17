#include "TestTaskApp.hpp"

#include <memory>

int main() {
    auto testApp = std::make_unique<TestTaskApp>();
    return testApp->run();
}
