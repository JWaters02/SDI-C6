//
// Created by bobby on 08/01/2022.
//

#ifndef ETM_DBHANDLER_H
#define ETM_DBHANDLER_H

#include <pqxx/pqxx>
#include <iostream>

class DBHandler {
private:
    pqxx::result queryText(const std::string& query);

public:
    static std::string getResult(const std::string& query);
    void callTest();
};


#endif //ETM_DBHANDLER_H
