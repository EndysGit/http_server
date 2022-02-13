//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_TEST_HPP
#define QTHTTPSERVER_TEST_TEST_HPP

#include "http_request.h"
#include "http_response.hpp"
#include "resolver.hpp"

class Test : public cwt_http::Resolver {
public:
    cwt_http::HttpResponse getMethod(cwt_http::HttpRequest) override {
        auto response = cwt_http::HttpResponse{cwt_http::core::HttpVersion::HTTP_1_1,
                                               cwt_http::core::HttpStatusCode::OK,
                                               "OK"};
        response.set_body("Hello from test get method");
        return response;
    }
private:
};

#endif //QTHTTPSERVER_TEST_TEST_HPP
