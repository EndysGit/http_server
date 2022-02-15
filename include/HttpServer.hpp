//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTPSERVER_HPP
#define QTHTTPSERVER_TEST_HTTPSERVER_HPP

#include "Config.hpp"
#include "http_core.hpp"
#include "Resolver.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

#include <QTcpServer>
#include <QTcpSocket>

#include <unordered_map>
#include <string>
#include <memory>

namespace cwt_http {
    class HttpServer {
    public:
        using TransporLayerServerType = QTcpServer;
        using ResolversContainerType = std::unordered_map<std::string, std::unique_ptr<Resolver>>;

        void addResolver(const std::string& resolverPath, std::unique_ptr<Resolver> resolver);
        void start(Config<std::string, std::string> config);
    private:
        TransporLayerServerType m_server;
        ResolversContainerType m_resolvers;

        HttpResponse dispatch(const HttpRequest& request) const;

        void processConnection(QTcpSocket *connection);
        void serverLoop();
    };
}

#endif //QTHTTPSERVER_TEST_HTTPSERVER_HPP
