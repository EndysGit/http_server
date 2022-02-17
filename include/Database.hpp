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

    Database(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&) = delete;

    query_result_type insertQuery(const mapped_type& value);
    query_result_type insertQuery(const key_type& key, const mapped_type& value);
    std::optional<table_type> selectQuery() const;
    query_result_type selectQuery(const key_type& key) const;
    query_result_type updateQuery(const key_type& key, const mapped_type& value);
    query_result_type deleteQuery(const key_type& key);
private:
    table_type m_data;
};

Database& getDataDatabaseRef();
Database& getLogDatabaseRef();


#endif //QTHTTPSERVER_TEST_DATABASE_HPP
