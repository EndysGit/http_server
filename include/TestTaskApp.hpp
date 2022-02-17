//
// Created by endyxx on 15.02.2022.
//

#ifndef QTHTTPSERVER_TEST_TESTTASKAPP_HPP
#define QTHTTPSERVER_TEST_TESTTASKAPP_HPP

#include "Application.hpp"
#include "HttpServer.hpp"

class TestTaskApp final : public Application {
public:
    int run() override;
private:
    cwt_http::HttpServer m_httpServer;
};


#endif //QTHTTPSERVER_TEST_TESTTASKAPP_HPP
