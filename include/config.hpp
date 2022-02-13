//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_CONFIG_HPP
#define QTHTTPSERVER_TEST_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <utility>
#include <unordered_map>
#include <filesystem>
#include <string>

class ConfigException : public std::invalid_argument {
public:
    explicit ConfigException(const std::string& msg) : std::invalid_argument(msg) {}
};

template <typename KeyT = std::string, typename ValueT = std::string,
        typename Container = std::unordered_map<KeyT, ValueT>>
class Config {
public:
    using path_type = std::filesystem::path;
    using key_type = typename Container::key_type;
    using value_type = typename Container::mapped_type;

    Config() = default;

    // Add check and config path validation
    // and check if input not failed
    template <typename ... Args>
    Config(Args&& ... args) : m_configPath(std::forward<Args>(args)...) {
        std::ifstream in{ m_configPath };
        if (!in.is_open()) {
            throw ConfigException("Failed to open file: " + m_configPath.string());
        }

        while (in) {
            key_type key;
            value_type value;
            in >> key >> value;
            auto date_it = m_data.emplace(std::move(key), std::move(value));
            std::cout << date_it.first->first << ' ' << date_it.first->second << '\n';
        }
    }

    [[nodiscard]] const value_type& get(const key_type& key) const {
        return m_data.at(key);
    }
private:
    path_type m_configPath;
    std::unordered_map<key_type, value_type> m_data;
};

#endif //QTHTTPSERVER_TEST_CONFIG_HPP
