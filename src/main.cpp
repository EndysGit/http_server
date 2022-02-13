#include "http_server.hpp"
#include "api.hpp"
#include "test.hpp"

/*
 * Реализовать REST http сервер, используя Qt и класс QTcpServer.
 * Сервер должен обрабатывать запросы POST, PUT, GET и DELETE на адресе http://127.0.0.1:1234/api и
 * менять "таблицу" в оперативной памяти с id и значением (можно использовать QMap). На запрос POST возвращается id добавленного элемента.
 * Также обрабатывать запрос на адресе http://127.0.0.1:1234/test и возвращать простую HTML страницу, в
 * которой выводилась бы простая таблица с id и значением, а после неё список совершенных
 * действий (например: item with id <> has been added, item with id <> has been deleted, item with id <> has been changed).
 * Использовать сторонние библиотеки запрещено.
 * Для обработки запросов рекомендуется переопределить виртуальный метод QTcpServer::incomingConnection.
 */

class Application {
public:
    virtual int run() = 0;
    ~Application() = default;
};

class TestTaskApp : public Application {
public:
    TestTaskApp() = default;

    int run() override {
        try {
            m_httpServer.addResolver("/api", std::make_unique<Api>());
            m_httpServer.addResolver("/test", std::make_unique<Test>());
            m_httpServer.start();
        } catch (...) {
            return 1;
        }

        return 0;
    }
private:
    cwt_http::HttpServer m_httpServer;
};

int main() {
    auto testApp = std::make_unique<TestTaskApp>();
    return testApp->run();
}