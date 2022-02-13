//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTP_HEADER_HPP
#define QTHTTPSERVER_TEST_HTTP_HEADER_HPP

#include <iostream>
#include <sstream>
#include <iterator>
#include <unordered_map>

namespace cwt_http {
    template <typename Container>
    class Headers {
    public:
        using key_type = typename Container::key_type;
        using mapped_type = typename Container::mapped_type;

        static void write(std::istream& in, Headers& header) {
            using std::string;
            using std::istringstream;

            std::string headerLine;
            while (getline(in, headerLine)) {
                while (!headerLine.empty() && std::isspace(headerLine.back())) {
                    headerLine.pop_back();
                }

                if (!headerLine.empty()) {
                    istringstream headerLineStream{ headerLine };

                    key_type headerKey;
                    headerLineStream >> headerKey;
                    headerKey.pop_back();

                    auto& headerValue = header.m_headers.emplace(move(headerKey), mapped_type{}).first->second;

                    std::copy(std::istream_iterator<char>(headerLineStream),
                              std::istream_iterator<char>(),
                              std::back_inserter(headerValue));
                } else {
                    break;
                }
            }
        }

        void set(const key_type& key, const mapped_type& value) {
            m_headers.emplace(key, value);
        }

        mapped_type& at(const key_type& key) & {
            return m_headers.at(key);
        }

        const mapped_type& at(const key_type& key) const & {
            return m_headers.at(key);
        }

        typename Container::iterator begin() & {
            return m_headers.begin();
        }

        typename Container::iterator end() & {
            return m_headers.end();
        }

        typename Container::const_iterator cbegin() const &{
            return m_headers.cbegin();
        }

        typename Container::const_iterator cend() const &{
            return m_headers.cend();
        }

    private:
        Container m_headers;
    };
}

#endif //QTHTTPSERVER_TEST_HTTP_HEADER_HPP
