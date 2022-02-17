//
// Created by endyxx on 15.02.2022.
//

#include "TestResolver.hpp"
#include "Database.hpp"

static cwt_http::HttpResponse unsuccessfulResponse(const std::string& message) {
    auto response = cwt_http::HttpResponse{
            cwt_http::core::HttpVersion::HTTP_1_1,
            cwt_http::core::HttpStatusCode::OK,
            "OK"};

    response.body().append("<html><body>");
    response.body().append(message);
    response.body().append("</body></html>");

    return response;
}

template <typename It>
static std::string makeHtmlTableStr(It begin, It end, const std::string& th1, const std::string& th2) {
    std::string htmlTable;

    htmlTable.append("<table>");
    htmlTable.append("<tr>");
    htmlTable.append("<th>").append(th1).append("</th>");
    htmlTable.append("<th>").append(th2).append("</th>");
    htmlTable.append("</tr>");

    for (;begin != end; ++begin) {
        htmlTable.append("<tr>");
        htmlTable.append("<td>").append(begin->first).append("</td>");
        htmlTable.append("<td>").append(begin->second).append("</td>");
        htmlTable.append("</tr>");
    }

    htmlTable.append("</table>");
    return htmlTable;
}

cwt_http::HttpResponse
TestResolver::getMethod(const cwt_http::HttpRequest&) const {
    auto& db = getDataDatabaseRef();
    auto& logDb = getLogDatabaseRef();

    auto dbQueryResult = db.selectQuery();
    auto logDbQueryResult = logDb.selectQuery();

    if (dbQueryResult.has_value()) {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};
        response.body().append("<html><body>");

        response.body().append(makeHtmlTableStr(dbQueryResult.value().cbegin(),
                                                dbQueryResult.value().cend(), "Key", "Value"));

        response.body().append(makeHtmlTableStr(logDbQueryResult.value().cbegin(),
                                                logDbQueryResult.value().cend(), "Log key", "Log message"));

        response.body().append("</html></body>");

        return response;
    } else {
        return unsuccessfulResponse("Nothing found");
    }
}
