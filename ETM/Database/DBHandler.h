//
// Created by bobby on 08/01/2022.
//

#ifndef ETM_DBHANDLER_H
#define ETM_DBHANDLER_H

#include <pqxx/pqxx>
#include <iostream>

class DBHandler {
private:
    static pqxx::result queryText(const std::string& query);
    const std::string dbConnection = "dbname=etm user=postgres password=postgres hostaddr=127.0.0.1 port=5432";

public:
    static std::string getResult(const std::string& query);
    static void writeFields(const std::string& query);
    static void callTest();
};


#endif //ETM_DBHANDLER_H
