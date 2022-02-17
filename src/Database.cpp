#include "Database.hpp"

#include <optional>
#include <unordered_map>

Database::query_result_type
Database::insertQuery(const mapped_type& value) {
    static unsigned long uid{ 0ul };

    auto rowIt = m_data.try_emplace(std::to_string(uid), value);
    ++uid;
    if (rowIt.second) {
        return std::make_pair(rowIt.first->first, rowIt.first->second);
    }

    return std::nullopt;
}

Database::query_result_type
Database::insertQuery(const key_type& key, const mapped_type& value) {
    auto rowIt = m_data.try_emplace(key, value);
    if (rowIt.second) {
        return std::make_pair(rowIt.first->first, rowIt.first->second);
    }

    return std::nullopt;
}

std::optional<Database::table_type>
Database::selectQuery() const {
    if (!m_data.empty()) {
        return m_data;
    }

    return std::nullopt;
}

Database::query_result_type
Database::selectQuery(const key_type& key) const {
    auto rowIt = m_data.find(key);
    if (rowIt != m_data.cend()) {
        return std::make_pair(rowIt->first, rowIt->second);
    }

    return std::nullopt;
}

Database::query_result_type
Database::updateQuery(const key_type& key, const mapped_type& value) {
    auto rowIt = m_data.find(key);
    if (rowIt != m_data.cend()) {
        rowIt->second = value;
        return std::make_pair(rowIt->first, rowIt->second);
    }

    return std::nullopt;
}

Database::query_result_type
Database::deleteQuery(const key_type& key) {
    auto rowIt = m_data.find(key);
    if (rowIt != m_data.cend()) {
        auto result = std::make_pair(rowIt->first, rowIt->second);
        m_data.erase(key);
        return result;
    }

    return std::nullopt;
}

Database& getDataDatabaseRef() {
    static Database database;
    return database;
}

Database& getLogDatabaseRef() {
    static Database logDatabase;
    return logDatabase;
}