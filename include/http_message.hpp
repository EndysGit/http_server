//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTP_MESSAGE_HPP
#define QTHTTPSERVER_TEST_HTTP_MESSAGE_HPP

#include "http_core.hpp"

namespace experimental {
    struct RequestLineTag{};
    struct ResponseLineTag{};

    template <typename StartLineT>
    struct StartLineTrait {
        using value_type = StartLineT;
        static_assert(std::is_base_of_v<RequestLineTag, value_type> ||
                      std::is_base_of_v<ResponseLineTag, value_type>,
                      "Bad start line type");

        //static void read(std::istream&, value_type&);
        //static void write(std::ostream&, value_type&);
    };

    template <typename HeadersT>
    struct HeadersTrait {
        using header_type = typename HeadersT::value_type;
        using key_type = typename HeadersT::key_type;
        using value_type = typename HeadersT::mapped_type;

        //static void read(std::istream&, header_type&);
        //static void write(std::ostream&, header_type&);
    };

    template <typename BodyT>
    struct BodyTrait {
        using value_type = typename BodyT::value_type;

        //static void read(std::istream&, value_type&);
        //static void write(std::ostream&, value_type&);
    };

    template<typename StartLineT, typename HeadersT, typename BodyT>
    class HttpMessage {
    public:
        using StartLineType = typename StartLineTrait<StartLineT>::value_type;
        using HeadersType = HeadersT;
        using HeaderKeyType = typename HeadersTrait<HeadersType>::key_type;
        using HeaderValueType = typename HeadersTrait<HeadersType>::value_type;
        using BodyType = typename BodyTrait<BodyT>::value_type;

        HttpMessage() = default;

        // Need add checkss
        template<typename ... Args>
        explicit HttpMessage(Args&& ... args) : m_start_line(std::forward<Args>(args)...) {
        }

        explicit HttpMessage(const std::string& request) {
            std::istringstream requestStream{ request };

            StartLineType::write(requestStream, m_start_line);
            HeadersType::write(requestStream, m_headers);
            BodyType::write(requestStream, m_body);
        }

        StartLineType& start_line() {
            return m_start_line;
        }

        const StartLineType& start_line() const {
            return m_start_line;
        }

        HeadersType& headers() {
            return m_headers;
        }

        const HeadersType& headers() const {
            return m_headers;
        }

        BodyType& body() {
            return m_body;
        }

        const BodyType& body() const {
            return m_body;
        }

    private:
        StartLineType m_start_line;
        HeadersType m_headers;
        BodyType m_body;
    };
}

#endif //QTHTTPSERVER_TEST_HTTP_MESSAGE_HPP
