//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_RESOLVER_HPP
#define QTHTTPSERVER_TEST_RESOLVER_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

namespace cwt_http {
    class Resolver {
    public:
        virtual ~Resolver() = default;

        virtual cwt_http::HttpResponse getMethod(const cwt_http::HttpRequest& request) const {
            return defaultImpl(request);
        }

        virtual cwt_http::HttpResponse postMethod(const cwt_http::HttpRequest& request) const {
            return defaultImpl(request);
        }

        virtual cwt_http::HttpResponse putMethod(const cwt_http::HttpRequest& request) const {
            return defaultImpl(request);
        }

        virtual cwt_http::HttpResponse deleteMethod(const cwt_http::HttpRequest& request) const {
            return defaultImpl(request);
        }
    private:
        [[nodiscard]] cwt_http::HttpResponse defaultImpl(const cwt_http::HttpRequest&) const {
            return cwt_http::HttpResponse{core::HttpVersion::HTTP_1_1,
                                          core::HttpStatusCode::METHOD_NOT_ALLOWED,
                                          "Method not allowed"};
        }
    };
}

#endif //QTHTTPSERVER_TEST_RESOLVER_HPP
