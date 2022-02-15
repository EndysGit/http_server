#include "ApiResolver.hpp"
#include "Database.hpp"

#include <sstream>

cwt_http::HttpResponse
ApiResolver::getMethod(const cwt_http::HttpRequest& request) const {
    auto queryMap = cwt_http::parseQuery(request.getStartLine().getQuery());

    auto& db = getDatabaseInstanceRef();
    auto dbQueryResult = db.selectQuery(queryMap["key"]);

    if (dbQueryResult.has_value()) {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};
        response.body() = "<html><body>Result:"
        " key = " + dbQueryResult.value().first
        + "; value = " + dbQueryResult.value().second
        +  "</body></html>";

        return response;
    } else {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};

        response.body() = "<html><body>Item not found</body></html>";
        return response;
    }
}

cwt_http::HttpResponse
ApiResolver::postMethod(const cwt_http::HttpRequest& request) const {
    auto queryMap =  cwt_http::parseQuery(request.getStartLine().getQuery());

    auto& db = getDatabaseInstanceRef();
    auto dbQueryResult = db.insertQuery(queryMap["value"]);

    if (dbQueryResult.has_value()) {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};
        response.body() = "<html><body>Result:"
        " key = " + dbQueryResult.value().first
        + "; value = " + dbQueryResult.value().second
        +  "</body></html>";

        return response;
    } else {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};

        response.body() = "<html><body>Item already exists</body></html>";
        return response;
    }
}
cwt_http::HttpResponse
ApiResolver::putMethod(const cwt_http::HttpRequest& request) const {
    auto queryMap =  cwt_http::parseQuery(request.getStartLine().getQuery());

    auto& db = getDatabaseInstanceRef();
    auto dbQueryResult = db.updateQuery(queryMap["key"], queryMap["value"]);
    if (!dbQueryResult.has_value()) {
        dbQueryResult = db.insertQuery(queryMap["key"], queryMap["value"]);
    }

    if (dbQueryResult.has_value()) {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};
        response.body() = "<html><body>Result:"
        " key = " + dbQueryResult.value().first
        + "; value = " + dbQueryResult.value().second
        +  "</body></html>";

        return response;
    } else {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};

        response.body() = "<html><body>Item already exists</body></html>";
        return response;
    }
}
cwt_http::HttpResponse
ApiResolver::deleteMethod(const cwt_http::HttpRequest& request) const {
    auto queryMap =  cwt_http::parseQuery(request.getStartLine().getQuery());

    auto& db = getDatabaseInstanceRef();
    auto dbQueryResult = db.deleteQuery(queryMap["key"]);

    if (dbQueryResult.has_value()) {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};
        response.body() = "<html><body>Result:"
        " key = " + dbQueryResult.value().first
        + "; value = " + dbQueryResult.value().second
        +  "</body></html>";

        return response;
    } else {
        auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};

        response.body() = "<html><body>Item not found</body></html>";
        return response;
    }
}
