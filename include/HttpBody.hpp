//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTPBODY_HPP
#define QTHTTPSERVER_TEST_HTTPBODY_HPP

#include <iostream>
#include <string>

namespace cwt_http {
    class HttpBody {
    public:
        using value_type = std::string;

        virtual ~HttpBody() = default;

        static void write(std::istream& in, HttpBody& body);

        [[nodiscard]] const value_type& body() const {
            return m_body;
        }

        value_type& body() {
            return m_body;
        }

    protected:
        [[nodiscard]] virtual std::string toString() const {
            return m_body;
        }

    private:
        value_type m_body;
    };
}

#endif //QTHTTPSERVER_TEST_HTTPBODY_HPP
