//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTP_CORE_HPP
#define QTHTTPSERVER_TEST_HTTP_CORE_HPP

#include <string>
#include <string_view>

// Experimental dependencies
#include <utility>
#include <iterator>
#include <sstream>

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

    HttpVersion string2HttpVersion(const std::string &protocol);
    std::string HttpVersion2string(HttpVersion protocol);

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

    HttpMethod string2HttpMethod(const std::string &method);
    std::string HttpMethod2string(HttpMethod method);

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
