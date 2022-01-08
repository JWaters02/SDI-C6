//
// Created by bobby on 08/01/2022.
//

#ifndef ETM_DBHANDLER_H
#define ETM_DBHANDLER_H

#include <pqxx/pqxx>
#include <iostream>

class DBHandler {
private:
    pqxx::result queryTest();

public:
    void callTest();
};


#endif //ETM_DBHANDLER_H
