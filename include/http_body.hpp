//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTP_BODY_HPP
#define QTHTTPSERVER_TEST_HTTP_BODY_HPP

#include <iostream>
#include <string>

template <typename T>
struct  Body {
    using value_type = T;

    static void write(std::istream& in, value_type& body) {
        while (in) {
            value_type bodyPart;
            getline(in, bodyPart);
            body.append(bodyPart);
        }
    }
};

#endif //QTHTTPSERVER_TEST_HTTP_BODY_HPP
