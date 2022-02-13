//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTP_CORE_HPP
#define QTHTTPSERVER_TEST_HTTP_CORE_HPP

#include <string>
#include <string_view>

namespace cwt_http::core {
    constexpr auto http_1_0 = std::string_view("HTTP/1.0");
    constexpr auto http_1_1 = std::string_view("HTTP/1.1");
    constexpr auto http_2_0 = std::string_view("HTTP/2.0");

    enum class HttpVersion {
        HTTP_1_0,
        HTTP_1_1,
        HTTP_2_0,
        UNSUPPORTED
    };

    HttpVersion string2HttpVersion(const std::string &protocol) {
        if (protocol == http_1_0) {
            return HttpVersion::HTTP_1_0;
        } else if (protocol == http_1_1) {
            return HttpVersion::HTTP_1_1;
        } else if (protocol == http_2_0) {
            return HttpVersion::HTTP_2_0;
        } else {
            return HttpVersion::UNSUPPORTED;
        }
    }

    std::string HttpVersion2string(HttpVersion protocol) {
        using std::string;
        // TODO add exceptional situation in case of invalid protocol
        switch (protocol) {
            case HttpVersion::HTTP_1_0:
                return string(http_1_0);
            case HttpVersion::HTTP_1_1:
                return string(http_1_1);
            case HttpVersion::HTTP_2_0:
                return string(http_2_0);
            default:
                break;
        }

        return string{};
    }

    constexpr auto getMethod = std::string_view("GET");
    constexpr auto postMethod = std::string_view("POST");
    constexpr auto putMethod = std::string_view("PUT");
    constexpr auto deleteMethod = std::string_view("DELETE");

    enum class HttpMethod {
        GET,
        POST,
        PUT,
        DELETE,
        UNSUPPORTED
    };

    HttpMethod string2HttpMethod(const std::string &method) {
        if (method == getMethod) {
            return HttpMethod::GET;
        } else if (method == postMethod) {
            return HttpMethod::POST;
        } else if (method == putMethod) {
            return HttpMethod::PUT;
        } else if (method == deleteMethod) {
            return HttpMethod::DELETE;
        } else {
            return HttpMethod::UNSUPPORTED;
        }
    }


    enum class HttpStatusCode {
        CONTINUE = 100,
        SWITCHING_PROTOCOLS_SECTION = 101,
        OK = 200,
        CREATED_SECTION = 201,
        ACCEPTED = 202,
        NON_AUTHORITATIVE_INFORMATION = 203,
        NO_CONTENT = 204,
        RESET_CONTENT = 205,
        PARTIAL_CONTENT_SECTION = 206,
        MULTIPLE_CHOICES = 300,
        MOVED_PERMANENTLY = 301,
        FOUND = 302,
        SEE_OTHER = 303,
        NOT_MODIFIED = 304,
        USE_PROXY = 305,
        TEMPORARY_REDIRECT = 307,
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        PAYMENT_REQUIRED = 402,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        METHOD_NOT_ALLOWED = 405,
        NOT_ACCEPTABLE = 406,
        PROXY_AUTHENTICATION_REQUIRED = 407,
        REQUEST_TIMEOUT = 408,
        CONFLICT = 409,
        GONE = 410,
        LENGTH_REQUIRED = 411,
        PRECONDITION_FAILED = 412,
        PAYLOAD_TOO_LARGE = 413,
        URI_TOO_LONG = 414,
        UNSUPPORTED_MEDIA_TYPE = 415,
        RANGE_NOT_SATISFIABLE = 416,
        EXPECTATION_FAILED = 417,
        UPGRADE_REQUIRED = 426,
        INTERNAL_SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
        BAD_GATEWAY = 502,
        SERVICE_UNAVAILABLE = 503,
        GATEWAY_TIMEOUT = 504,
        HTTP_VERSION_NOT_SUPPORTED = 505,
    };
}

#endif //QTHTTPSERVER_TEST_HTTP_CORE_HPP
