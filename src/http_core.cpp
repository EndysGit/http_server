#include "http_core.hpp"

namespace cwt_http::core {
    HttpVersion string2HttpVersion(const std::string &protocol) {
        if (protocol == http_1_0) {
            return HttpVersion::HTTP_1_0;
        } else if (protocol == http_1_1) {
            return HttpVersion::HTTP_1_1;
        } else if (protocol == http_2_0) {
            return HttpVersion::HTTP_2_0;
        } else {
            return HttpVersion::UNSUPPORTED;
        }
    }

    std::string HttpVersion2string(HttpVersion protocol) {
        using std::string;
        // TODO add exceptional situation in case of invalid protocol
        switch (protocol) {
            case HttpVersion::HTTP_1_0:
                return string(http_1_0);
            case HttpVersion::HTTP_1_1:
                return string(http_1_1);
            case HttpVersion::HTTP_2_0:
                return string(http_2_0);
            default:
                break;
        }

        return string{};
    }

    HttpMethod string2HttpMethod(const std::string &method) {
        if (method == getMethod) {
            return HttpMethod::GET;
        } else if (method == postMethod) {
            return HttpMethod::POST;
        } else if (method == putMethod) {
            return HttpMethod::PUT;
        } else if (method == deleteMethod) {
            return HttpMethod::DELETE;
        } else {
            return HttpMethod::UNSUPPORTED;
        }
    }

    std::string HttpMethod2string(HttpMethod method) {
        switch (method) {
            case HttpMethod::GET: return { getMethod.begin(), getMethod.end() };
            case HttpMethod::POST: return { postMethod.cbegin(), postMethod.cend() };
            case HttpMethod::PUT: return { putMethod.cbegin(), putMethod.cend() };
            case HttpMethod::DELETE: return { deleteMethod.cbegin(), deleteMethod.cend() };

            default: return {};
        }
    }
}