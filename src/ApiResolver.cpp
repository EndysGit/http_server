#include "ApiResolver.hpp"
#include "Database.hpp"

#include <sstream>
#include <chrono>

static std::string getLogId() {
    return std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
}

static void addDbLog(const std::string& message, const std::string& key = "", const std::string& value = "") {
    auto& logDb = getLogDatabaseRef();
    std::string logMessage(message);
    if (!key.empty()) {
        logMessage.append(": key = ").append(key);
        logMessage.append("; value = ").append(value);
    }

    logDb.insertQuery(getLogId(), logMessage);
}


static cwt_http::HttpResponse successfulResponse(const std::string& key, const std::string& value) {
    auto response = cwt_http::HttpResponse{
            cwt_http::core::HttpVersion::HTTP_1_1,
            cwt_http::core::HttpStatusCode::OK,
            "OK"};

    response.body().append("<html><body>");
    response.body().append("key = ").append(key).append("; ");
    response.body().append("value = ").append(value);
    response.body().append("</body></html>");

    return response;
}

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

cwt_http::HttpResponse
ApiResolver::getMethod(const cwt_http::HttpRequest& request) const {
    auto queryMap = cwt_http::parseQuery(request.getStartLine().getQuery());

    auto& db = getDataDatabaseRef();
    auto dbQueryResult = db.selectQuery(queryMap["key"]);

    if (dbQueryResult.has_value()) {
        return successfulResponse(dbQueryResult.value().first, dbQueryResult.value().second);
    } else {
        return unsuccessfulResponse("Item not found");
    }
}

cwt_http::HttpResponse
ApiResolver::postMethod(const cwt_http::HttpRequest& request) const {
    auto queryMap =  cwt_http::parseQuery(request.getStartLine().getQuery());

    auto& db = getDataDatabaseRef();
    auto dbQueryResult = db.insertQuery(queryMap["value"]);

    if (dbQueryResult.has_value()) {
        addDbLog("Item was inserted", dbQueryResult.value().first, dbQueryResult.value().second);
        return successfulResponse(dbQueryResult.value().first, dbQueryResult.value().second);
    } else {
        return unsuccessfulResponse("Item already exists");
    }
}

cwt_http::HttpResponse
ApiResolver::putMethod(const cwt_http::HttpRequest& request) const {
    auto queryMap =  cwt_http::parseQuery(request.getStartLine().getQuery());

    auto& db = getDataDatabaseRef();
    auto dbQueryResult = db.updateQuery(queryMap["key"], queryMap["value"]);
    if (!dbQueryResult.has_value()) {
        dbQueryResult = db.insertQuery(queryMap["key"], queryMap["value"]);
        if (dbQueryResult.has_value()) {
            addDbLog("Item was inserted", dbQueryResult.value().first,
                     dbQueryResult.value().second);
        }
    } else {
        // TODO: also old value
        addDbLog("Item was updated", dbQueryResult.value().first, dbQueryResult.value().second);
    }

    if (dbQueryResult.has_value()) {
        return successfulResponse(dbQueryResult.value().first, dbQueryResult.value().second);
    } else {
        return unsuccessfulResponse("Item already exists");
    }
}

cwt_http::HttpResponse
ApiResolver::deleteMethod(const cwt_http::HttpRequest& request) const {
    auto queryMap =  cwt_http::parseQuery(request.getStartLine().getQuery());

    auto& db = getDataDatabaseRef();
    auto dbQueryResult = db.deleteQuery(queryMap["key"]);

    if (dbQueryResult.has_value()) {
        addDbLog("Item was deleted", dbQueryResult.value().first, dbQueryResult.value().second);
        return successfulResponse(dbQueryResult.value().first, dbQueryResult.value().second);
    } else {
        return unsuccessfulResponse("Item not found");
    }
}
