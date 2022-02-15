//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_HTTPHEADER_HPP
#define QTHTTPSERVER_TEST_HTTPHEADER_HPP

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_map>

namespace cwt_http {
    class HttpHeader {
    public:
        using Container = std::unordered_map<std::string, std::string>;
        using key_type = typename Container::key_type;
        using mapped_type = typename Container::mapped_type;

        virtual ~HttpHeader() = default;

        static void write(std::istream& in, HttpHeader& header);

        HttpHeader& headers() {
            return *this;
        }

        const HttpHeader& headers() const {
            return *this;
        }

        void set(const key_type& key, const mapped_type& value) {
            m_headers.emplace(key, value);
        }

        mapped_type& at(const key_type& key) {
            return m_headers.at(key);
        }

        const mapped_type& at(const key_type& key) const {
            return m_headers.at(key);
        }

        typename Container::iterator begin() {
            return m_headers.begin();
        }

        typename Container::iterator end() {
            return m_headers.end();
        }

        typename Container::const_iterator begin() const {
            return m_headers.cbegin();
        }

        typename Container::const_iterator end() const {
            return m_headers.cend();
        }

        typename Container::const_iterator cbegin() const {
            return m_headers.cbegin();
        }

        typename Container::const_iterator cend() const {
            return m_headers.cend();
        }

        virtual std::string toString() const;
    private:
        Container m_headers;
    };
}

#endif //QTHTTPSERVER_TEST_HTTPHEADER_HPP
