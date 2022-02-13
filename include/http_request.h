//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTP_REQUEST_H
#define QTHTTPSERVER_TEST_HTTP_REQUEST_H

#include "http_core.hpp"
#include "http_header.hpp"
#include "http_body.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <string_view>
#include <sstream>
#include <unordered_map>

namespace cwt_http {
    std::unordered_map<std::string, std::string> parseQuery(const std::string& query) {
        std::unordered_map<std::string, std::string> queryMap;

        std::istringstream is{ query };
        std::string keyValuePair;
        while (std::getline(is, keyValuePair, '&')) {
            std::istringstream kvs{ keyValuePair };
            std::string key;
            getline(kvs, key, '=');
            std::string value;
            getline(kvs, value);
            queryMap.emplace(key, value);
        }

        return queryMap;
    }

    template <typename PathT = std::string, typename QueryT = std::string>
    struct RequestTarget {
        using PathType = PathT;
        using QueryType = QueryT;

        PathT path;
        QueryT query;

        RequestTarget() = default;
        explicit RequestTarget(const std::string& requestTarget) {
            using std::string;
            auto delimiterIt = std::find(requestTarget.cbegin(),
                                         requestTarget.cend(),
                                         '?');

            path = string(requestTarget.cbegin(), delimiterIt);
            if (delimiterIt != requestTarget.cend()) {
                query = string(std::next(delimiterIt), requestTarget.cend());
            }
        }
    };

    class RequestLine{
    public:
        using MethodType = core::HttpMethod;
        using RequestTargetType = RequestTarget<std::string, std::string>;
        using ProtocolType = core::HttpVersion;

        RequestLine() = default;

        explicit RequestLine(const std::string& line) {
            using std::stringstream;
            using std::string;
            stringstream requestStream{line};

            auto ok = true;

            string requestMethod;
            ok = ok && (requestStream >> requestMethod);
            m_method = core::string2HttpMethod(requestMethod);

            string requestTarget;
            ok = ok && (requestStream >> requestTarget);
            m_requestTarget = RequestTargetType(requestTarget);
            // validate

            string protocolVersion;
            ok = ok && (requestStream >> protocolVersion);
            m_protocol = core::string2HttpVersion(protocolVersion);
        }

        [[nodiscard]] MethodType getMethod() const {
            return m_method;
        }

        [[nodiscard]] ProtocolType getProtocol() const {
            return m_protocol;
        }

        [[nodiscard]] const std::string& getPath() const {
            return m_requestTarget.path;
        }

        [[nodiscard]] const std::string& getQuery() const {
            return m_requestTarget.query;
        }

        [[nodiscard]] const RequestTargetType& getRequestTarget() const {
            return m_requestTarget;
        }

    private:
        MethodType m_method;
        RequestTargetType m_requestTarget;
        ProtocolType m_protocol;
    };

    // TODO: invalid case need invalidate stream
    std::istream& operator>>(std::istream& in, RequestLine& requestLine) {
        std::string requestLineStr;
        std::getline(in, requestLineStr);
        requestLine = RequestLine(requestLineStr);

        return in;
    }

    class HttpRequest {
    public:
        using StartLineType = RequestLine;
        using BodyT = Body<std::string>;

        using HeadersType = Headers<std::unordered_map<std::string, std::string>>;
        using HeaderKeyType = typename HeadersType::key_type;
        using HeaderValueType = typename HeadersType::mapped_type;
        using BodyType = typename BodyT::value_type;

        // Make it for move semantics
        explicit HttpRequest(const std::string &request) {
            using std::istringstream;
            using std::string;
            using std::getline;
            using std::move;

            istringstream requestStream{request};
            // Make this like requestStream >> m_requestLine >> m_headers >> m_body;
            requestStream >> m_requestLine;
            HeadersType::write(requestStream, m_headers);
            BodyT::write(requestStream, m_body);
        }

        [[nodiscard]] const StartLineType& getStartLine() const {
            return m_requestLine;
        }

        [[nodiscard]] HeadersType& getHeaders() {
            return m_headers;
        }

        [[nodiscard]] const HeaderValueType& getHeader(const HeaderKeyType& key) const {
            return m_headers.at(key);
        }

        [[nodiscard]] const BodyType& getBody() const {
            return m_body;
        }

        void setHeader(const HeaderKeyType& key, const HeaderValueType& value) {
            m_headers.set(key, value);
        }

        void setBody(const BodyType& body) {
            m_body = body;
        }

        std::string toString() const {
            return std::string();
        }

    private:
        StartLineType m_requestLine;
        HeadersType m_headers;
        BodyType m_body;
    };

    void printRequest(HttpRequest& request) {
        std::cout << static_cast<int>(request.getStartLine().getMethod()) << ' '
                  << request.getStartLine().getPath() << ' ' << request.getStartLine().getQuery() << ' '
                  << core::HttpVersion2string(request.getStartLine().getProtocol()) << '\n';

        std::cout << "Headers:\n";
        for (auto& header: request.getHeaders()) {
            std::cout << header.first << ": " << header.second << '\n';
        }

        std::cout << "Body:\n";
        std::cout << request.getBody() << '\n' << '\n';
    }

    //using core::HttpMessage<RequestLine, Headers, Body>;
}

#endif //QTHTTPSERVER_TEST_HTTP_REQUEST_H
