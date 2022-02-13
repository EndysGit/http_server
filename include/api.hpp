//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_API_HPP
#define QTHTTPSERVER_TEST_API_HPP

#include "resolver.hpp"
#include "http_request.h"
#include "http_response.hpp"
#include "database.hpp"

#include <sstream>



class Api : public cwt_http::Resolver {
public:
    cwt_http::HttpResponse getMethod(cwt_http::HttpRequest request) override {
        auto queryMap = cwt_http::parseQuery(request.getStartLine().getQuery());

        auto& db = getDatabaseInstanceRef();
        auto dbQueryResult = db.selectQuery(queryMap["key"]);

        if (dbQueryResult.has_value()) {
            auto response = cwt_http::HttpResponse{
                cwt_http::core::HttpVersion::HTTP_1_1,
                cwt_http::core::HttpStatusCode::OK,
                "OK"};
            response.set_body("<html><body>Result:"
                              " key = " + dbQueryResult.value().first
                              + "; value = " + dbQueryResult.value().second
                              +  "</body></html>");

            return response;
        } else {
            auto response = cwt_http::HttpResponse{
                    cwt_http::core::HttpVersion::HTTP_1_1,
                    cwt_http::core::HttpStatusCode::OK,
                    "OK"};

            response.set_body("<html><body>Item not found</body></html>");
            return response;
        }
    }

    cwt_http::HttpResponse postMethod(cwt_http::HttpRequest request) override {
        auto queryMap =  cwt_http::parseQuery(request.getStartLine().getQuery());

        auto& db = getDatabaseInstanceRef();
        auto dbQueryResult = db.insertQuery(queryMap["key"], queryMap["value"]);

        if (dbQueryResult.has_value()) {
            auto response = cwt_http::HttpResponse{
                    cwt_http::core::HttpVersion::HTTP_1_1,
                    cwt_http::core::HttpStatusCode::OK,
                    "OK"};
            response.set_body("<html><body>Result:"
                              " key = " + dbQueryResult.value().first
                              + "; value = " + dbQueryResult.value().second
                              +  "</body></html>");

            return response;
        } else {
            auto response = cwt_http::HttpResponse{
                    cwt_http::core::HttpVersion::HTTP_1_1,
                    cwt_http::core::HttpStatusCode::OK,
                    "OK"};

            response.set_body("<html><body>Item already exists</body></html>");
            return response;
        }
    }
    cwt_http::HttpResponse putMethod(cwt_http::HttpRequest request) override {
        auto queryMap =  cwt_http::parseQuery(request.getStartLine().getQuery());

        auto& db = getDatabaseInstanceRef();
        auto dbQueryResult = db.insertQuery(queryMap["key"], queryMap["value"]);

        if (dbQueryResult.has_value()) {
            auto response = cwt_http::HttpResponse{
                    cwt_http::core::HttpVersion::HTTP_1_1,
                    cwt_http::core::HttpStatusCode::OK,
                    "OK"};
            response.set_body("<html><body>Result:"
                              " key = " + dbQueryResult.value().first
                              + "; value = " + dbQueryResult.value().second
                              +  "</body></html>");

            return response;
        } else {
            auto response = cwt_http::HttpResponse{
                    cwt_http::core::HttpVersion::HTTP_1_1,
                    cwt_http::core::HttpStatusCode::OK,
                    "OK"};

            response.set_body("<html><body>Item already exists</body></html>");
            return response;
        }
    }
    cwt_http::HttpResponse deleteMethod(cwt_http::HttpRequest request) override {
        auto queryMap =  cwt_http::parseQuery(request.getStartLine().getQuery());

        auto& db = getDatabaseInstanceRef();
        auto dbQueryResult = db.deleteQuery(queryMap["key"]);

        if (dbQueryResult.has_value()) {
            auto response = cwt_http::HttpResponse{
                    cwt_http::core::HttpVersion::HTTP_1_1,
                    cwt_http::core::HttpStatusCode::OK,
                    "OK"};
            response.set_body("<html><body>Result:"
                              " key = " + dbQueryResult.value().first
                              + "; value = " + dbQueryResult.value().second
                              +  "</body></html>");

            return response;
        } else {
            auto response = cwt_http::HttpResponse{
                    cwt_http::core::HttpVersion::HTTP_1_1,
                    cwt_http::core::HttpStatusCode::OK,
                    "OK"};

            response.set_body("<html><body>Item not found</body></html>");
            return response;
        }
    }

private:
};

#endif //QTHTTPSERVER_TEST_API_HPP
