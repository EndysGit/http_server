//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTPRESPONSE_HPP
#define QTHTTPSERVER_TEST_HTTPRESPONSE_HPP

#include "http_core.hpp"
#include "HttpMessageBase.hpp"

#include <unordered_map>

namespace cwt_http {
    class StatusLine{
    public:
        StatusLine() = default;
        StatusLine(core::HttpVersion protocol,
                   core::HttpStatusCode statusCode,
                   std::string reasonPhrase)
                : m_protocol{ protocol }
                , m_statusCode{ statusCode }
                , m_reasonPhrase{ std::move(reasonPhrase) } {

        }

        static void write(std::istream& in, StatusLine& statusLine);

        [[nodiscard]] std::string toString() const;

    private:
        core::HttpVersion m_protocol;
        core::HttpStatusCode m_statusCode;
        std::string m_reasonPhrase;
    };

    class HttpResponse final : public core::HttpMessageBase {
    public:
        using StartLineType = StatusLine;

        HttpResponse() = default;
        HttpResponse(core::HttpVersion protocol,
                     core::HttpStatusCode statusCode,
                     const std::string& reasonPhrase)
                : m_statusLine{protocol, statusCode, reasonPhrase} {
        }

        explicit HttpResponse(const std::string &request);

        [[nodiscard]] const StartLineType& getStartLine() const {
            return m_statusLine;
        }

        [[nodiscard]] std::string toString() const override {
            return m_statusLine.toString()
            .append(HttpHeader::toString())
            .append(HttpBody::toString());
        }
    private:
        StartLineType m_statusLine;
    };

    //using core::HttpMessage<StatusLine, Headers, Body>;
}

#endif //QTHTTPSERVER_TEST_HTTPRESPONSE_HPP
