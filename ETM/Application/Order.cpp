#include "Order.h"

/**
 * Get the the past orders of the customer.
 * @param username The username of the customer.
 * @return The past orders.
 */
std::vector<OrderInfo> Order::getPastOrders(const std::string& username) {
    // Call to DB to get orders given username where status is delivered or cancelled
    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE username = '"
            << username
            << "' AND (orderStatus = 'Delivered' OR orderStatus = 'Cancelled')";
    return parseOrderInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get current orders given the username.
 * @param username The username.
 * @return A vector of order info.
 */
std::vector<OrderInfo> Order::getCurrentOrders(const std::string& username) {
    // Call to DB to get orders given username where status is pending
    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE username = '"
            << username
            << "' AND orderStatus = 'Pending'";
    return parseOrderInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get all the current orders from the Orders table.
 * @return A vector of order info.
 */
std::vector<OrderInfo> Order::getAllCurrentOrders() {
    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE orderStatus = 'Pending'";
    return parseOrderInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get all the taken orders from the Orders table.
 * @param userType The user type.
 * @param username The username.
 * @return A vector of order info.
 */
std::vector<OrderInfo> Order::getTakenOrders(const EUserTypes& userType, const std::string& username) {
    std::string type = getType(userType);

    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE "
            << type
            << " = '"
            << username
            << "' AND orderStatus = 'Pending'";
    return parseOrderInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get all the taken orders from the Orders table.
 * @param userType The user type.
 * @return
 */
std::vector<OrderInfo> Order::getAllTakenOrders(const EUserTypes& userType) {
    std::string type = getType(userType);

    std::stringstream query;
    query   << "SELECT * FROM OrderGoods WHERE "
            << type
            << " != 'NONE' AND orderStatus = 'Pending'";
    return parseOrderInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Parse the order table from the database into a vector of order info (each row).
 * @param orderInfo The order info.
 * @return A vector of order info.
 */
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
        parsedOrder.fees = std::stod(order[12]);
        parsedOrderInfo.push_back(parsedOrder);
    }
    return parsedOrderInfo;
}

/**
 * Increase the total price of the orderID by the given amount.
 * @param orderID The order ID.
 * @param income The amount to increase the total price by.
 */
void Order::increaseTotalPrice(const std::string& orderID, const double& income) {
    std::stringstream query;
    query   << "UPDATE OrderGoods SET orderFees = orderFees + '"
            << std::to_string(income)
            << "' WHERE orderID = '"
            << orderID
            << "';";
    DBHandler::writeFields(query.str());
}

/**
 * Make a new order in the Orders table given the info.
 * @param username The username of the customer.
 * @param itemName The item name.
 * @param quantity The quantity of the item.
 * @param unitPrice The price of each item.
 */
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

/**
 * Take an order by the given order ID and username of the user taking it.
 * @param userType The user type of the user taking the order.
 * @param username The username of the user taking the order.
 * @param orderID The order ID.
 */
void Order::takeOrder(const EUserTypes& userType, const std::string& username, const std::string& orderID) {
    std::string type = getType(userType);
    std::stringstream query;
    query   << "UPDATE OrderGoods SET "
            << type
            << " = '"
            << username
            << "' WHERE orderID = '"
            << orderID
            << "'";
    DBHandler::writeFields(query.str());
}

/**
 * Deliver an order by the given order ID.
 * @param orderID The order ID.
 */
void Order::deliverOrder(const std::string& orderID) {
    std::stringstream query;
    query   << "UPDATE OrderGoods SET orderStatus = 'Delivered' WHERE orderID = '"
            << orderID
            << "';";
    DBHandler::writeFields(query.str());
    deleteAuctions(orderID);
}

/**
 * Delete the auctions associated with the given order ID.
 * @param orderID The order ID.
 */
void Order::deleteAuctions(const std::string& orderID) {
    // Go through the auction tables and delete the orders
    std::stringstream query;
    query   << "DELETE FROM DriverAuction WHERE orderID = '"
            << orderID
            << "';"
            << "DELETE FROM COAuction WHERE orderID = '"
            << orderID
            << "';";
    DBHandler::writeFields(query.str());
}

/**
 * Get the order IDs of all orders.
 * @return The order IDs.
 */
std::vector<std::string> Order::getOrderIDs() {
    std::stringstream query;
    query   << "SELECT orderID FROM OrderGoods";
    return DBHandler::getResultVector(query.str());
}

/**
 * Get the user column of the order with the given user type.
 * @param userType The user type.
 * @return The user column name.
 */
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

/**
 * Get the current date.
 * @return The current date in format 'dd-mm-yyyy'.
 */
std::string Order::currentDate() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);
    return buf;
}

/**
 * Get the current time.
 * @return The current time in format 'hh:mm:ss'.
 */
std::string Order::currentTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    return buf;
}






