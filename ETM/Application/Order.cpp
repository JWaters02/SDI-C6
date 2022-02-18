//
// Created by root on 18/02/2022.
//

#include "Order.h"

std::vector<OrderInfo> Order::getPastOrders(const std::string& username) {
    // Call to DB to get orders given username where status is delivered or cancelled
    std::stringstream query;
    query   << "SELECT * FROM Orders WHERE username = '"
            << username
            << "' AND (orderStatus = 'Delivered' OR orderStatus = 'Cancelled')";
    std::vector<std::vector<std::string>> pastOrders = DBHandler::getResult2DVector(query.str());
    return parseOrderInfo(pastOrders);
}

std::vector<OrderInfo> Order::getCurrentOrders(const std::string& username) {
    // Call to DB to get orders given username where status is pending
    std::stringstream query;
    query   << "SELECT * FROM Orders WHERE username = '"
            << username
            << "' AND orderStatus = 'Pending'";
    std::vector<std::vector<std::string>> currentOrders = DBHandler::getResult2DVector(query.str());
    return parseOrderInfo(currentOrders);
}

std::vector<OrderInfo> Order::parseOrderInfo(const std::vector<std::vector<std::string>>& orderInfo) {
    // Parse orderInfo into OrderInfo
    std::vector<OrderInfo> parsedOrderInfo;
    for (const auto& order : orderInfo) {
        OrderInfo parsedOrder;
        parsedOrder.id = std::to_string(std::stoi(order[0]));
        parsedOrder.date = order[1];
        parsedOrder.time = order[2];
        parsedOrder.status = order[3];
        parsedOrder.price = std::stod(order[4]);
        parsedOrder.name = order[6];
        parsedOrderInfo.push_back(parsedOrder);
    }
    return parsedOrderInfo;
}

std::string Order::currentDate() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);
    return buf;
}

std::string Order::currentTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    return buf;
}






