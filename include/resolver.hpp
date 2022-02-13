//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_RESOLVER_HPP
#define QTHTTPSERVER_TEST_RESOLVER_HPP

#include "http_core.hpp"
#include "http_request.h"
#include "http_response.hpp"

namespace cwt_http {
    class Resolver {
    public:
        virtual cwt_http::HttpResponse getMethod(cwt_http::HttpRequest) {
            return cwt_http::HttpResponse{core::HttpVersion::HTTP_1_1,
                                          core::HttpStatusCode::METHOD_NOT_ALLOWED,
                                          "Method not allowed"};
        }

        virtual cwt_http::HttpResponse postMethod(cwt_http::HttpRequest) {
            return cwt_http::HttpResponse{core::HttpVersion::HTTP_1_1,
                                          core::HttpStatusCode::METHOD_NOT_ALLOWED,
                                          "Method not allowed"};
        }

        virtual cwt_http::HttpResponse putMethod(cwt_http::HttpRequest) {
            return cwt_http::HttpResponse{core::HttpVersion::HTTP_1_1,
                                          core::HttpStatusCode::METHOD_NOT_ALLOWED,
                                          "Method not allowed"};
        }

        virtual cwt_http::HttpResponse deleteMethod(cwt_http::HttpRequest) {
            return cwt_http::HttpResponse{core::HttpVersion::HTTP_1_1,
                                          core::HttpStatusCode::METHOD_NOT_ALLOWED,
                                          "Method not allowed"};
        }

        virtual ~Resolver() = default;
    };
}

#endif //QTHTTPSERVER_TEST_RESOLVER_HPP
