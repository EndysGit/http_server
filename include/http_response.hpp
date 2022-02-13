//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTP_RESPONSE_HPP
#define QTHTTPSERVER_TEST_HTTP_RESPONSE_HPP

#include "http_core.hpp"

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

        std::string toString() {
            std::stringstream statusLineStream;

            statusLineStream << core::HttpVersion2string(m_protocol) << ' ';
            statusLineStream << std::to_string(static_cast<int>(m_statusCode)) << ' ';
            statusLineStream << m_reasonPhrase << '\n';

            return statusLineStream.str();
        }

    private:
        core::HttpVersion m_protocol;
        core::HttpStatusCode m_statusCode;
        std::string m_reasonPhrase;
    };



    class HttpResponse {
    public:
        using StartLineType = StatusLine;
        using BodyT = Body<std::string>;

        using HeadersType = Headers<std::unordered_map<std::string, std::string>>;
        using HeaderKeyType = typename HeadersType::key_type;
        using HeaderValueType = typename HeadersType::mapped_type;
        using BodyType = typename BodyT::value_type;

        HttpResponse() = default;
        HttpResponse(core::HttpVersion protocol,
                     core::HttpStatusCode statusCode,
                     const std::string& reasonPhrase)
                : m_statusLine{protocol, statusCode, reasonPhrase} {
        }

        void set_body(const std::string& body) {
            m_body = body;
        }

        std::string toString() {
            return m_statusLine.toString().append("\r\n").append(m_body);
        }

    private:
        StartLineType m_statusLine;
        HeadersType m_headers;
        BodyType m_body;
    };

    //using core::HttpMessage<StatusLine, Headers, Body>;
}

#endif //QTHTTPSERVER_TEST_HTTP_RESPONSE_HPP
