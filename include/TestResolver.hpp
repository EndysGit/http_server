//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_TESTRESOLVER_HPP
#define QTHTTPSERVER_TEST_TESTRESOLVER_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Resolver.hpp"

class TestResolver : public cwt_http::Resolver {
public:
    [[nodiscard]] cwt_http::HttpResponse getMethod(const cwt_http::HttpRequest& request) const override;
};

#endif //QTHTTPSERVER_TEST_TESTRESOLVER_HPP
