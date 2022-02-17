#include "TestTaskApp.hpp"

#include <memory>

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

int main() {
    auto testApp = std::make_unique<TestTaskApp>();
    return testApp->run();
}
