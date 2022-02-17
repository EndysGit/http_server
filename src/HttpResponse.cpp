#include "HttpResponse.hpp"

namespace cwt_http {
    void StatusLine::write(std::istream& in, StatusLine& statusLine) {
        //TODO implement
    }

    std::string
    StatusLine::toString() const {
        std::stringstream statusLineStream;

        statusLineStream << core::HttpVersion2string(m_protocol) << ' ';
        statusLineStream << std::to_string(static_cast<int>(m_statusCode)) << ' ';
        statusLineStream << m_reasonPhrase << '\r' << '\n';

        return statusLineStream.str();
    }

    HttpResponse::HttpResponse(const std::string &request) {
        using std::istringstream;

        istringstream requestStream{request};
        // Make this like requestStream >> m_requestLine >> m_headers >> m_body;
        StatusLine::write(requestStream, m_statusLine);
        HttpHeader::write(requestStream, *this);
        HttpBody::write(requestStream, *this);
    }

}