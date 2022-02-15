//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTPREQUEST_HPP
#define QTHTTPSERVER_TEST_HTTPREQUEST_HPP

#include "http_core.hpp"
#include "HttpMessageBase.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <string_view>
#include <sstream>
#include <unordered_map>

namespace cwt_http {
    std::unordered_map<std::string, std::string> parseQuery(const std::string& query);

    class RequestTarget {
    public:
        using PathType = std::string;
        using QueryType = std::string;

        RequestTarget() = default;
        explicit RequestTarget(const std::string& requestTarget);

        [[nodiscard]] const PathType& path() const {
            return m_path;
        }

        [[nodiscard]] const QueryType& query() const {
            return m_query;
        }

    private:
        PathType m_path;
        QueryType m_query;
        std::unordered_map<std::string, std::string> m_mapped_query;
    };

    class RequestLine final {
    public:
        using MethodType = core::HttpMethod;
        using RequestTargetType = RequestTarget;
        using ProtocolType = core::HttpVersion;

        RequestLine() = default;
        RequestLine(MethodType method,
                    RequestTargetType requestTarget,
                    ProtocolType protocol)
                    : m_method{ method }
                    , m_requestTarget{ std::move(requestTarget) }
                    , m_protocol{ protocol } {

        }

        static void write(std::istream& in, RequestLine& requestLine);

        [[nodiscard]] MethodType getMethod() const {
            return m_method;
        }

        [[nodiscard]] ProtocolType getProtocol() const {
            return m_protocol;
        }

        [[nodiscard]] const std::string& getPath() const {
            return m_requestTarget.path();
        }

        [[nodiscard]] const std::string& getQuery() const {
            return m_requestTarget.query() ;
        }

        [[nodiscard]] const RequestTargetType& getRequestTarget() const {
            return m_requestTarget;
        }

        [[nodiscard]] std::string toString() const;
    private:
        MethodType m_method;
        RequestTargetType m_requestTarget;
        ProtocolType m_protocol;
    };

    class HttpRequest : public core::HttpMessageBase {
    public:
        using StartLineType = RequestLine;

        HttpRequest() = default;
        HttpRequest(StartLineType::MethodType method,
                    StartLineType::RequestTargetType requestTarget,
                    StartLineType::ProtocolType protocol)
                    : m_requestLine{method,
                                    std::move(requestTarget),
                                    protocol} {}
        // Make it for move semantics
        explicit HttpRequest(const std::string &request);

        [[nodiscard]] const StartLineType& getStartLine() const {
            return m_requestLine;
        }

        [[nodiscard]] std::string toString() const override {
            return m_requestLine.toString()
                    .append(HttpHeader::toString())
                    .append(HttpBody::toString());
        }

    private:
        StartLineType m_requestLine;
    };

    void printRequest(const HttpRequest& request);
}

#endif //QTHTTPSERVER_TEST_HTTPREQUEST_HPP
