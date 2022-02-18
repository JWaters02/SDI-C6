//
// Created by bobby on 08/01/2022.
//

#include "DBHandler.h"

pqxx::result DBHandler::queryText(const std::string& query) {
    pqxx::connection c("dbname=etm user=postgres password=password hostaddr=127.0.0.1 port=5432");
    pqxx::work txn{c};
    pqxx::result r{txn.exec(query)};
    txn.commit();
    return r;
}

std::string DBHandler::getResult(const std::string &query) {
    std::string ret;
    try {
        pqxx::result r = queryText(query);
        for (auto && row : r) {
            for (auto && column : row) {
                ret += column.c_str();
            }
        }
    } catch (pqxx::sql_error const &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        std::cerr << "Query was: " << e.what() << std::endl;
        return "";
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return "";
    }
    return ret;
}

std::vector<std::vector<std::string>> DBHandler::getResult2DVector(const std::string &query) {
    std::vector<std::vector<std::string>> ret;
    try {
        pqxx::result r = queryText(query);
        for (auto && row : r) {
            std::vector<std::string> rowVector;
            for (auto && column : row) {
                rowVector.emplace_back(column.c_str());
            }
            ret.push_back(rowVector);
        }
    } catch (pqxx::sql_error const &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        std::cerr << "Query was: " << e.what() << std::endl;
        return {};
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return {};
    }
    return ret;
}

void DBHandler::writeFields(const std::string& query) {
    try {
        pqxx::connection c("dbname=etm user=postgres password=password hostaddr=127.0.0.1 port=5432");
        pqxx::work txn{c};
        txn.exec(query);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        throw e;
    }
}