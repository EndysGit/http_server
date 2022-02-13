//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTP_SERVER_HPP
#define QTHTTPSERVER_TEST_HTTP_SERVER_HPP

#include "config.hpp"
#include "http_core.hpp"
#include "resolver.hpp"
#include "http_request.h"
#include "http_response.hpp"

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

namespace cwt_http {
    class HttpServer {
    public:
        using TransporLayerServerType = QTcpServer;

        void addResolver(const std::string& resolverPath, std::unique_ptr<Resolver> resolver) {
            m_resolvers.emplace(resolverPath, move(resolver));
        }

        void start() {
            constexpr auto configPath{"config/tcp_srv.cfg"};
            Config config{ configPath };

            auto ipAddress = QHostAddress(config.get("ipAddress").data());
            auto port = std::stoi(config.get("port"));
            auto maxPendingConnections = std::stoi(
                    config.get("maxPendingConnections"));

            m_server.setMaxPendingConnections(maxPendingConnections);
            if (!m_server.listen(ipAddress, port)) {
                std::cout << m_server.errorString().toStdString();
                std::abort();
            }

            serverLoop();
        }
    private:
        TransporLayerServerType m_server;
        std::unordered_map<std::string, std::unique_ptr<Resolver>> m_resolvers;

        HttpResponse processRequest(const HttpRequest& request) {
            auto&& requestTargetPath = request.getStartLine().getRequestTarget().path;

            auto resolverIt = m_resolvers.find(requestTargetPath);
            if (resolverIt != m_resolvers.cend()) {
                switch (request.getStartLine().getMethod()) {
                    case core::HttpMethod::GET: {
                        return resolverIt->second->getMethod(request);
                    }
                    case core::HttpMethod::POST: {
                        return resolverIt->second->postMethod(request);
                    }
                    case core::HttpMethod::PUT: {
                        return resolverIt->second->putMethod(request);
                    }
                    case core::HttpMethod::DELETE: {
                        return resolverIt->second->deleteMethod(request);
                    }
                    default: {
                        return HttpResponse{core::HttpVersion::HTTP_1_1,
                                            core::HttpStatusCode::NOT_IMPLEMENTED,
                                            "Not implemented"};
                    }
                }
            } else {
                 return HttpResponse{core::HttpVersion::HTTP_1_1,
                                     core::HttpStatusCode::NOT_FOUND,
                                     "Not found"};
            }
        }

        void processConnection(QTcpSocket *connection) {
            std::cout << "New accepted connection: "
                      << connection->peerAddress().toString().toStdString()
                      << '\n';

            if (connection->isOpen() && connection->isReadable() &&
                connection->isWritable()) {
                connection->waitForReadyRead();

                // HttpServer getRequestFromQue();
                // here need move
                HttpRequest request{ connection->readAll().toStdString() };
                printRequest(request);
                auto response = processRequest(request);

                connection->write(QByteArray::fromStdString(response.toString()));
                connection->waitForBytesWritten();
                connection->close();
            } else {
                connection->close();
            }
        }

        void serverLoop() {
            while (m_server.isListening()) {
                if (m_server.hasPendingConnections()) {
                    processConnection(m_server.nextPendingConnection());
                } else {
                    m_server.waitForNewConnection(1);
                }
            }
        }
    };
}

#endif //QTHTTPSERVER_TEST_HTTP_SERVER_HPP
