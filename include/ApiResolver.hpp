//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_APIRESOLVER_HPP
#define QTHTTPSERVER_TEST_APIRESOLVER_HPP

#include "Resolver.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class ApiResolver : public cwt_http::Resolver {
public:
    [[nodiscard]] cwt_http::HttpResponse getMethod(const cwt_http::HttpRequest& request) const override;
    [[nodiscard]] cwt_http::HttpResponse postMethod(const cwt_http::HttpRequest& request) const override;
    [[nodiscard]] cwt_http::HttpResponse putMethod(const cwt_http::HttpRequest& request)  const override;
    [[nodiscard]] cwt_http::HttpResponse deleteMethod(const cwt_http::HttpRequest& request) const override;
};

#endif //QTHTTPSERVER_TEST_APIRESOLVER_HPP
