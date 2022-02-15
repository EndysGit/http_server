//
// Created by endyxx on 15.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTPMESSAGEBASE_HPP
#define QTHTTPSERVER_TEST_HTTPMESSAGEBASE_HPP

#include "http_core.hpp"
#include "HttpBody.hpp"
#include "HttpHeader.hpp"

#include <algorithm>


namespace cwt_http::core {
    class HttpMessageBase : public HttpHeader, public HttpBody {};
}

#endif //QTHTTPSERVER_TEST_HTTPMESSAGEBASE_HPP
