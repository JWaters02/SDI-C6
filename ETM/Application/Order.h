#ifndef ETM_ORDER_H
#define ETM_ORDER_H

#include <iostream>
#include <ctime>
#include <QString>
#include "Database/DBHandler.h"
#include "Users/UserUtils.h"

/*
CREATE TABLE IF NOT EXISTS OrderGoods (
      orderID varchar(4) NOT NULL,
      username varchar(20) NOT NULL,
      orderDate date NOT NULL,
      orderTime time NOT NULL,
      orderStatus varchar(20) NOT NULL,
      orderItemName varchar(40) NOT NULL,
      orderUnitPrice double precision NOT NULL,
      orderQuantity integer NOT NULL,
      orderForwarderName varchar(20) DEFAULT 'NONE',
      orderCourierName varchar(20) DEFAULT 'NONE',
      orderDriverName varchar(20) DEFAULT 'NONE',
      orderCargoOwnerName varchar(20) DEFAULT 'NONE',
      orderFees double precision DEFAULT 0.0,
      FOREIGN KEY (username) REFERENCES Users(username),
      CONSTRAINT order_pk PRIMARY KEY (orderID)
);
*/

enum EOrderStatuses {
    PENDING,
    DELIVERED,
    CANCELLED
};

struct OrderStatuses {
    std::string Pending = "Pending";
    std::string Delivered = "Delivered";
    std::string Cancelled = "Cancelled";
};

struct OrderInfo {
    std::string id;
    std::string username;
    std::string date;
    std::string time;
    std::string status;
    std::string itemName;
    double unitPrice;
    int quantity;
    double fees;
};

class Order {
private:
    static std::vector<OrderInfo> parseOrderInfo(const std::vector<std::vector<std::string>>& orderInfo);
    static std::vector<std::string> getOrderIDs();
    static std::string getType(const EUserTypes& userType);
    static std::string currentDate();
    static std::string currentTime();

public:
    static std::vector<OrderInfo> getPastOrders(const std::string& username);
    static std::vector<OrderInfo> getCurrentOrders(const std::string& username);
    static std::vector<OrderInfo> getAllCurrentOrders();
    static std::vector<OrderInfo> getTakenOrders(const EUserTypes& userType, const std::string& username);
    static std::vector<OrderInfo> getAllTakenOrders(const EUserTypes& userType);

    static void increaseTotalPrice(const std::string& orderID, const double& income);
    static void makeOrder(const std::string& username, const std::string& itemName, const int& quantity, const double& unitPrice);
    static void takeOrder(const EUserTypes& userType, const std::string& username, const std::string& orderID);
};


#endif //ETM_ORDER_H
