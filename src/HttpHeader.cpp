#include "HttpHeader.hpp"

#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>

namespace cwt_http {
    void
    HttpHeader::write(std::istream &in, HttpHeader& header) {
        using std::string;
        using std::istringstream;

        while (std::isspace(in.peek())) {
            in.get();
        }

        std::string headerLine;
        while (getline(in, headerLine)) {
            while (!headerLine.empty() && std::isspace(headerLine.back())) {
                headerLine.pop_back();
            }

            if (!headerLine.empty()) {
                istringstream headerLineStream{headerLine};

                key_type headerKey;
                headerLineStream >> headerKey;
                headerKey.pop_back();

                auto &headerValue = header.m_headers.emplace(move(headerKey),
                                                             mapped_type{}).first->second;

                std::copy(std::istream_iterator<char>(headerLineStream),
                          std::istream_iterator<char>(),
                          std::back_inserter(headerValue));
            } else {
                break;
            }
        }
    }

    std::string
    HttpHeader::toString() const {
        std::string headersStr;

        for (const auto& [key,value]: m_headers) {
            headersStr.append(key).append(": ").append(value).append("\r\n");
        }

        headersStr.append("\r\n");

        return headersStr;
    }
}