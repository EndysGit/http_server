//
// Created by endyxx on 15.02.2022.
//

#include "TestResolver.hpp"
#include "Database.hpp"

cwt_http::HttpResponse
TestResolver::getMethod(const cwt_http::HttpRequest& request) const {
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

        response.body() = body;
        return response;
    } else {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};

        response.body() = "<html><body>Noting found</body></html>";
        return response;
    }
}
