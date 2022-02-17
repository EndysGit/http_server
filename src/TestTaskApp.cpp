//
// Created by endyxx on 15.02.2022.
//

#include "ApiResolver.hpp"
#include "TestResolver.hpp"
#include "TestTaskApp.hpp"
#include "Config.hpp"

int
TestTaskApp::run() {
    try {
        m_httpServer.addResolver("/api", std::make_unique<ApiResolver>());
        m_httpServer.addResolver("/test", std::make_unique<TestResolver>());

        constexpr auto configPath{"config/tcp_srv.cfg"};
        m_httpServer.start(Config{ configPath });
    } catch (...) {
        return 1;
    }

    return 0;
}
