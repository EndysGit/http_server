#ifndef QTHTTPSERVER_TEST_APPLICATION_HPP
#define QTHTTPSERVER_TEST_APPLICATION_HPP

class Application {
public:
    ~Application() = default;
    virtual int run() = 0;
};

#endif //QTHTTPSERVER_TEST_APPLICATION_HPP
