//
// Created by bobby on 08/01/2022.
//

#include "DBHandler.h"

/**
 * Query the database for the given query and return the result.
 * @param query The query to execute.
 * @return The result of the query.
 */
pqxx::result DBHandler::queryText(const std::string& query) {
    pqxx::connection c(Secrets::getDBCredentials());
    pqxx::work txn{c};
    pqxx::result r{txn.exec(query)};
    txn.commit();
    return r;
}

/**
 * Query the database for the given query and expect a single string result.
 * @param query The query to execute.
 * @return The result of the query.
 */
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

/**
 * Query the database for the given query and expect a row result.
 * @param query The query to execute.
 * @return The row of results.
 */
std::vector<std::string> DBHandler::getResultVector(const std::string& query) {
    std::vector<std::string> ret;
    try {
        pqxx::result r = queryText(query);
        for (auto && row : r) {
            for (auto && field: row) {
                ret.push_back(field.c_str());
            }
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

/**
 * Query the database for the given query and expect a whole table.
 * @param query The query to execute.
 * @return The table of results.
 */
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

/**
 * Write data to the database given the query.
 * @param query The query to execute.
 */
void DBHandler::writeFields(const std::string& query) {
    try {
        pqxx::connection c(Secrets::getDBCredentials());
        pqxx::work txn{c};
        txn.exec(query);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        throw e;
    }
}
