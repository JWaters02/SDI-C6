#include "Order.h"

std::vector<OrderInfo> Order::getPastOrders(const std::string& username) {
    // Call to DB to get orders given username where status is delivered or cancelled
    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE username = '"
            << username
            << "' AND (orderStatus = 'Delivered' OR orderStatus = 'Cancelled')";
    std::vector<std::vector<std::string>> pastOrders = DBHandler::getResult2DVector(query.str());
    return parseOrderInfo(pastOrders);
}

std::vector<OrderInfo> Order::getCurrentOrders(const std::string& username) {
    // Call to DB to get orders given username where status is pending
    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE username = '"
            << username
            << "' AND orderStatus = 'Pending'";
    std::vector<std::vector<std::string>> currentOrders = DBHandler::getResult2DVector(query.str());
    return parseOrderInfo(currentOrders);
}

std::vector<OrderInfo> Order::getAllCurrentOrders() {
    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE orderStatus = 'Pending'";
    std::vector<std::vector<std::string>> allCurrentOrders = DBHandler::getResult2DVector(query.str());
    return parseOrderInfo(allCurrentOrders);
}

std::vector<OrderInfo> Order::getTakenOrders(const EUserTypes& userType, const std::string& username) {
    std::string type = getType(userType);

    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE "
            << type
            << " = '"
            << username
            << "' AND orderStatus = 'Pending'";
    std::vector<std::vector<std::string>> takenOrders = DBHandler::getResult2DVector(query.str());
    return parseOrderInfo(takenOrders);
}

std::vector<OrderInfo> Order::getAllTakenOrders(const EUserTypes& userType) {
    std::string type = getType(userType);

    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE "
            << type
            << " != 'NONE' AND orderStatus = 'Pending'";
    std::vector<std::vector<std::string>> allTakenOrders = DBHandler::getResult2DVector(query.str());
    return parseOrderInfo(allTakenOrders);
}

std::vector<OrderInfo> Order::parseOrderInfo(const std::vector<std::vector<std::string>>& orderInfo) {
    std::vector<OrderInfo> parsedOrderInfo;
    for (const auto& order : orderInfo) {
        OrderInfo parsedOrder;
        parsedOrder.id = order[0];
        parsedOrder.username = order[1];
        parsedOrder.date = order[2];
        parsedOrder.time = order[3];
        parsedOrder.status = order[4];
        parsedOrder.itemName = order[5];
        parsedOrder.unitPrice = std::stod(order[6]);
        parsedOrder.quantity = std::stoi(order[7]);
        parsedOrderInfo.push_back(parsedOrder);
    }
    return parsedOrderInfo;
}

void Order::makeOrder(const std::string& username, const std::string& itemName, const int& quantity, const double& unitPrice) {
    // Get existing order IDs
    std::vector<std::string> IDs = getOrderIDs();
    // Loop through IDs to find the first that isn't used
    int previous = 0;
    for (std::string id : IDs) {
        if (std::stoi(id) > previous) previous = std::stoi(id);
    }
    std::string unused = std::to_string(previous + 1);

    const std::string status = "Pending";

    std::stringstream query;
    query   << "INSERT INTO OrderGoods VALUES ('"
            << unused
            << "', '"
            << username
            << "', '"
            << currentDate()
            << "', '"
            << currentTime()
            << "', '"
            << status
            << "', '"
            << itemName
            << "', "
            << std::to_string(unitPrice)
            << ", "
            << std::to_string(quantity)
            << ");";
    DBHandler::writeFields(query.str());
}

void Order::takeOrder(const EUserTypes& userType, const std::string& username, const std::string& orderID) {
    std::string type = getType(userType);
    std::stringstream query;
    query   << "UPDATE OrderGoods SET "
            << type
            << " = '"
            << username
            << "' WHERE orderID = '"
            << orderID
            << "';";
    DBHandler::writeFields(query.str());
}

std::vector<std::string> Order::getOrderIDs() {
    std::stringstream query;
    query   << "SELECT orderID FROM OrderGoods";
    std::vector<std::string> IDs = DBHandler::getResultVector(query.str());
    return IDs;
}

std::string Order::getType(const EUserTypes& userType) {
    if (userType == EUserTypes::CARGO_OWNER) {
        return "orderCargoOwnerName";
    } else if (userType == EUserTypes::DRIVER) {
        return "orderDriverName";
    } else if (userType == EUserTypes::FORWARDER) {
        return "orderForwarderName";
    } else if (userType == EUserTypes::COURIER) {
        return "orderCourierName";
    }
    return "";
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






