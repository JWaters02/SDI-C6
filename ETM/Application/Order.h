//
// Created by root on 18/02/2022.
//

#ifndef ETM_ORDER_H
#define ETM_ORDER_H

#include <iostream>
#include <ctime>
#include <QString>
#include "Database/DBHandler.h"

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

enum EItemCategories {

};

struct ItemCategories {
    // Separate to enum because
    // converting enum to string is a pain in C++
    std::string Dry = "Dry";
    std::string Wet = "Wet";
    std::string Frozen = "Frozen";
};

struct OrderInfo {
    std::string id;
    std::string date;
    std::string time;
    std::string status;
    int price;
    std::string name;
};

struct ItemInfo {
    std::string id;
    EItemCategories category;
    std::string name;
    double weight;
    double volume;
    double price;
    int quantity;
};

struct CommissionInfo {
    double commissionPercentage;
};

class Order {
private:
    static std::vector<OrderInfo> parseOrderInfo(const std::vector<std::vector<std::string>>& orderInfo);
    static std::string currentDate();
    static std::string currentTime();

public:
    static std::vector<OrderInfo> getPastOrders(const std::string& username);
    static std::vector<OrderInfo> getCurrentOrders(const std::string& username);
};


#endif //ETM_ORDER_H
