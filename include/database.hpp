//
// Created by endyxx on 13.02.2022.
//

#ifndef QTHTTPSERVER_TEST_DATABASE_HPP
#define QTHTTPSERVER_TEST_DATABASE_HPP

#include <optional>
#include <unordered_map>
#include <memory>

class Database {
public:
    using table_type = std::unordered_map<std::string, std::string>;
    using key_type = typename table_type::key_type;
    using mapped_type = typename table_type::mapped_type;
    using query_result_type = std::optional<std::pair<key_type, mapped_type>>;

    Database() = default;

    query_result_type insertQuery(const key_type& key, const mapped_type& value) {
        auto rowIt = m_data.emplace(key, value);
        if (rowIt.second) {
            return std::make_pair(rowIt.first->first, rowIt.first->second);
        }

        return std::nullopt;
    }

    std::optional<table_type> selectQuery() const {
        if (!m_data.empty()) {
            return m_data;
        }

        return std::nullopt;
    }

    query_result_type selectQuery(const key_type& key) const {
        auto rowIt = m_data.find(key);
        if (rowIt != m_data.cend()) {
            return std::make_pair(rowIt->first, rowIt->second);
        }

        return std::nullopt;
    }

    query_result_type updateQuery(const key_type& key, const mapped_type& value) {
        auto rowIt = m_data.find(key);
        if (rowIt != m_data.cend()) {
            rowIt->second = value;
            return std::make_pair(rowIt->first, rowIt->second);
        }

        return std::nullopt;
    }

    query_result_type deleteQuery(const key_type& key) {
        auto rowIt = m_data.find(key);
        if (rowIt != m_data.cend()) {
            auto result = std::make_pair(rowIt->first, rowIt->second);
            m_data.erase(key);
            return result;
        }

        return std::nullopt;
    }

private:
    table_type m_data;
};

static Database& getDatabaseInstanceRef() {
    static Database database;
    return database;
}


#endif //QTHTTPSERVER_TEST_DATABASE_HPP
