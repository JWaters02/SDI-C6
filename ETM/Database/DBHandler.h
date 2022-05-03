//
// Created by bobby on 08/01/2022.
//

#ifndef ETM_DBHANDLER_H
#define ETM_DBHANDLER_H

#include <pqxx/pqxx>
#include <iostream>
#include <vector>

class DBHandler {
private:
    static pqxx::result queryText(const std::string& query);

public:
    static std::string getResult(const std::string& query);
    static std::vector<std::string> getResultVector(const std::string& query);
    static std::vector<std::vector<std::string>> getResult2DVector(const std::string& query);
    static void writeFields(const std::string& query);
};


#endif //ETM_DBHANDLER_H
