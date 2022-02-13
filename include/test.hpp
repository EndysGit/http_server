//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_TEST_HPP
#define QTHTTPSERVER_TEST_TEST_HPP

#include "database.hpp"
#include "http_request.h"
#include "http_response.hpp"
#include "resolver.hpp"

//<table>
//<tr>
//<th>Company</th>
//<th>Contact</th>
//<th>Country</th>
//</tr>
//<tr>
//<td>Alfreds Futterkiste</td>
//<td>Maria Anders</td>
//<td>Germany</td>
//</tr>
//<tr>
//<td>Centro comercial Moctezuma</td>
//<td>Francisco Chang</td>
//<td>Mexico</td>
//</tr>
//</table>

class Test : public cwt_http::Resolver {
public:
    cwt_http::HttpResponse getMethod(cwt_http::HttpRequest request) override {
        auto queryMap = cwt_http::parseQuery(request.getStartLine().getQuery());

        auto& db = getDatabaseInstanceRef();
        auto dbQueryResult = db.selectQuery();

        if (dbQueryResult.has_value()) {
            auto response = cwt_http::HttpResponse{
                    cwt_http::core::HttpVersion::HTTP_1_1,
                    cwt_http::core::HttpStatusCode::OK,
                    "OK"};

            std::string body{"<html><body><table><tr><th>Key</th><th>Value</th></tr>"};
            for (const auto& keyValuePair_i: dbQueryResult.value()) {
                body.append("<tr>");
                body.append("<td>");
                body.append(keyValuePair_i.first);
                body.append("</td>");
                body.append("<td>");
                body.append(keyValuePair_i.second);
                body.append("</td>");
                body.append("</tr>");
            }

            body.append("</table></body></html>");

            response.set_body(body);
            return response;
        } else {
            auto response = cwt_http::HttpResponse{
                    cwt_http::core::HttpVersion::HTTP_1_1,
                    cwt_http::core::HttpStatusCode::OK,
                    "OK"};

            response.set_body("<html><body>Noting found</body></html>");
            return response;
        }
    }
private:
};

#endif //QTHTTPSERVER_TEST_TEST_HPP
