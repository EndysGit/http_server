#include "HttpRequest.hpp"

namespace cwt_http {
    std::unordered_map<std::string, std::string>
    parseQuery(const std::string& query) {
        std::unordered_map<std::string, std::string> queryMap;

        std::istringstream is{ query };
        std::string keyValuePair;
        while (std::getline(is, keyValuePair, '&')) {
            std::istringstream kvs{ keyValuePair };
            std::string key;
            getline(kvs, key, '=');
            std::string value;
            getline(kvs, value);
            queryMap.emplace(key, value);
        }

        return queryMap;
    }

    RequestTarget::RequestTarget(const std::string& requestTarget) {
        using std::string;
        auto delimiterIt = std::find(requestTarget.cbegin(),
                                     requestTarget.cend(),
                                     '?');

        m_path = string(requestTarget.cbegin(), delimiterIt);
        if (delimiterIt != requestTarget.cend()) {
            m_query = string(std::next(delimiterIt), requestTarget.cend());
        }
    }

    void
    RequestLine::write(std::istream &in, RequestLine &requestLine) {
        using std::string;

        auto ok = true;

        string requestMethod;
        ok = ok && (in >> requestMethod);
        requestLine.m_method = core::string2HttpMethod(requestMethod);

        string requestTarget;
        ok = ok && (in >> requestTarget);
        requestLine.m_requestTarget = RequestTargetType(requestTarget);
        // validate

        string protocolVersion;
        ok = ok && (in >> protocolVersion);
        requestLine.m_protocol = core::string2HttpVersion(protocolVersion);

        if (!ok) {
            throw "Failed to parse request line";
        }
    }

    std::string
    RequestLine::toString() const {
        std::stringstream requestLineStream;

        requestLineStream << core::HttpMethod2string(m_method) << ' ';
        requestLineStream << m_requestTarget.path() << m_requestTarget.query() << ' ';
        requestLineStream <<  core::HttpVersion2string(m_protocol)  << '\r' << '\n';

        return requestLineStream.str();
    }

    HttpRequest::HttpRequest(const std::string &request) {
        using std::istringstream;

        istringstream requestStream{request};

        RequestLine::write(requestStream, m_requestLine);
        HttpHeader::write(requestStream, *this);
        HttpBody::write(requestStream, *this);
    }

    void printRequest(const HttpRequest& request) {
        std::cout << request.toString() << '\n';
    }
}