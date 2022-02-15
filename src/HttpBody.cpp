#include "HttpBody.hpp"

namespace cwt_http {
    void
    HttpBody::write(std::istream& in, HttpBody& body) {
        while (in) {
            value_type bodyPart;
            getline(in, bodyPart);
            body.m_body.append(bodyPart);
        }
    }
}