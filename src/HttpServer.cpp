//
// Created by endyxx on 15.02.2022.
//

#include "HttpServer.hpp"

namespace cwt_http {
    void
    HttpServer::addResolver(const std::string& resolverPath, std::unique_ptr<Resolver> resolver) {
        m_resolvers.emplace(resolverPath, move(resolver));
    }

    void
    HttpServer::start(Config<std::string, std::string> config) {
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

    void
    HttpServer::serverLoop() {
        // TODO: Reduce busy wait
        while (m_server.isListening()) {
            if (m_server.hasPendingConnections()) {
                // This code should be in other thread
                // ThreadPool::doWork(dispatchConnection, m_server.nextPendingConnection());
                // In thread pool should be task queue which few threads uses to get task
                processConnection(m_server.nextPendingConnection());
            } else {
                m_server.waitForNewConnection(1);
            }
        }
    }

    void
    HttpServer::processConnection(QTcpSocket *connection) {
        // TODO: move to log
        std::cout << "New accepted connection: "
                  << connection->peerAddress().toString().toStdString()
                  << '\n';

        if (connection->isOpen() && connection->isReadable() &&
            connection->isWritable())
        {
            connection->waitForReadyRead();

            auto responseData = getResponse(connection->readAll().toStdString()).toString();
            connection->write(responseData.data(), responseData.size());

            connection->waitForBytesWritten();
            connection->close();
        } else {
            connection->close();
        }
    }

    HttpResponse
    HttpServer::getResponse(const std::string &requestData) const {
        HttpRequest request{ requestData };

        printRequest(request);
        auto&& requestTargetPath = request.getStartLine().getRequestTarget().path();

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

}