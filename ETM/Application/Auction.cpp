#include "Auction.h"

/**
 * Parse the database result into cargo owner auction info data.
 * @param auctionInfo The database result.
 * @return The list of parsed cargo owner auction info rows.
 */
std::vector<COAuctionInfo> Auction::parseCOAuctionInfo(const std::vector<std::vector<std::string>>& auctionInfo) {
    std::vector<COAuctionInfo> parsedAuctionInfo;
    for (const auto& auction : auctionInfo) {
        COAuctionInfo parsedAuction;
        parsedAuction.auctionId = auction[0];
        parsedAuction.orderId = auction[1];
        parsedAuction.username = auction[2];
        parsedAuction.startPrice = std::stod(auction[3]);
        parsedAuction.bidPrice = std::stod(auction[4]);
        parsedAuction.commission = std::stod(auction[5]);
        parsedAuction.startDate = auction[6];
        parsedAuction.startTime = auction[7];
        parsedAuction.length = std::stoi(auction[8]);
        parsedAuction.status = auction[9];
        parsedAuction.bidder = auction[10];
        parsedAuctionInfo.push_back(parsedAuction);
    }
    return parsedAuctionInfo;
}

/**
 * Parse the database result into driver auction info data.
 * @param auctionInfo The database result.
 * @return The list of parsed driver auction info rows.
 */
std::vector<DriverAuctionInfo> Auction::parseDriverAuctionInfo(const std::vector<std::vector<std::string>>& auctionInfo) {
    std::vector<DriverAuctionInfo> parsedAuctionInfo;
    for (const auto& auction : auctionInfo) {
        DriverAuctionInfo parsedAuction;
        parsedAuction.auctionId = auction[0];
        parsedAuction.orderId = auction[1];
        parsedAuction.username = auction[2];
        parsedAuction.startPrice = std::stod(auction[3]);
        parsedAuction.bidPrice = std::stod(auction[4]);
        parsedAuction.commission = std::stod(auction[5]);
        parsedAuction.costPerMile = std::stod(auction[6]);
        parsedAuction.distance = std::stod(auction[7]);
        parsedAuction.startDate = auction[8];
        parsedAuction.startTime = auction[9];
        parsedAuction.length = std::stoi(auction[10]);
        parsedAuction.status = auction[11];
        parsedAuction.bidder = auction[12];
        parsedAuctionInfo.push_back(parsedAuction);
    }
    return parsedAuctionInfo;
}

/**
 * Get a list of running auctions for the user type and username specified from the database.
 * @param userType The user type.
 * @param username The username.
 * @return The list of running cargo owner auctions.
 */
std::vector<COAuctionInfo> Auction::getRunningAuctions(const EUserTypes& userType, const std::string& username) {
    std::stringstream query;
    query   << "SELECT * FROM "
            << getTable(userType)
            << " WHERE username = '"
            << username
            << "' AND auctionStatus = 'Running'";
    return parseCOAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get a list of ongoing cargo owner auctions from the database.
 * @param userType The user type.
 * @return The list of ongoing cargo owner auctions.
 */
std::vector<COAuctionInfo> Auction::getOngoingCOAuctions(const EUserTypes& userType) {
    std::stringstream query;
    query   << "SELECT * FROM "
            << getTable(userType)
            << " WHERE auctionStatus = 'Running'";
    return parseCOAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get a list of running driver auctions for the user type and username specified from the database.
 * @param userType The user type.
 * @param username The username.
 * @return The list of running driver auctions.
 */
std::vector<DriverAuctionInfo> Auction::getRunningDriverAuctions(const EUserTypes& userType, const std::string& username) {
    std::stringstream query;
    query   << "SELECT * FROM "
            << getTable(userType)
            << " WHERE username = '"
            << username
            << "' AND auctionStatus = 'Running'";
    return parseDriverAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get a list of won cargo owner auctions from the database.
 * @param username The username of the bidder.
 * @return The list of won cargo owner auctions.
 */
std::vector<COAuctionInfo> Auction::getWonCOAuctions(const std::string& username) {
    std::stringstream query;
    query   << "SELECT * FROM COAuction WHERE auctionBidder = '"
            << username
            << "' AND auctionStatus = 'Finished'";
    return parseCOAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get a list of ongoing driver auctions from the database.
 * @param userType The user type.
 * @return The list of ongoing driver auctions.
 */
std::vector<DriverAuctionInfo> Auction::getOngoingDriverAuctions(const EUserTypes& userType) {
    std::stringstream query;
    query   << "SELECT * FROM "
            << getTable(userType)
            << " WHERE auctionStatus = 'Running'";
    return parseDriverAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get a list of won driver auctions from the database.
 * @param username The username of the bidder.
 * @return The list of won driver auctions.
 */
std::vector<DriverAuctionInfo> Auction::getWonDriverAuctions(const std::string& username) {
    std::stringstream query;
    query   << "SELECT * FROM DriverAuction WHERE auctionBidder = '"
            << username
            << "' AND auctionStatus = 'Finished'";
    return parseDriverAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

/**
 * Get a list of all the auctionIDs from the specified table.
 * @param userType The table type.
 * @return The list of auctionIDs.
 */
std::vector<std::string> Auction::getAuctionIDs(const EUserTypes& userType) {
    std::stringstream query;
    query   << "SELECT auctionID FROM "
            << getTable(userType);
    std::vector<std::string> IDs = DBHandler::getResultVector(query.str());
    return IDs;
}

/**
 * Get a list of all the orderIDs from the specified auction table.
 * @param userType The table type.
 * @return The list of orderIDs.
 */
std::vector<std::string> Auction::getOrderIDs(const EUserTypes& userType) {
    std::stringstream query;
    query   << "SELECT orderID FROM "
            << getTable(userType);
    std::vector<std::string> IDs = DBHandler::getResultVector(query.str());
    return IDs;
}

/**
 * Create a new auction on the COAuction table in the database.
 * @param username The name of the auction owner.
 * @param orderId The orderID of the cargo.
 * @param startPrice The start price of the auction.
 * @param commission The commission of the auction.
 * @param length The length of the auction in hours.
 */
void Auction::makeCOAuction(const std::string& username, const std::string& orderId, const double& startPrice,
                            const double& commission, const int& length) {
    // Get existing auctionIDs
    std::vector<std::string> IDs = getAuctionIDs(EUserTypes::CARGO_OWNER);
    // Loop through IDs to find the first that isn't used
    int previous = 0;
    for (std::string id : IDs) {
        if (std::stoi(id) > previous) previous = std::stoi(id);
    }
    std::string unused = std::to_string(previous + 1);

    const std::string status = "Running";

    std::stringstream query;
    query   << "INSERT INTO COAuction VALUES ('"
            << unused
            << "', '"
            << orderId
            << "', '"
            << username
            << "', '"
            << std::to_string(startPrice)
            << "', '"
            << std::to_string(startPrice)
            << "', '"
            << std::to_string(commission)
            << "', '"
            << currentDate()
            << "', '"
            << currentTime()
            << "', '"
            << std::to_string(length)
            << "', '"
            << status
            << "');";
    DBHandler::writeFields(query.str());
}

/**
 * Create a new auction on the DriverAuction table in the database.
 * @param username The name of the auction owner.
 * @param orderId The orderID of the cargo.
 * @param startPrice The start price of the auction.
 * @param commission The commission of the auction.
 * @param cpm The cost per mile of the auction.
 * @param distance The distance of the auction in miles.
 * @param length The length of the auction in hours.
 */
void Auction::makeDriverAuction(const std::string& username, const std::string& orderId, const double& startPrice,
                                const double& commission, const double& cpm, const double& distance, const int& length) {
    // Get existing auctionIDs
    std::vector<std::string> IDs = getAuctionIDs(EUserTypes::DRIVER);
    // Loop through IDs to find the first that isn't used
    int previous = 0;
    for (std::string id : IDs) {
        if (std::stoi(id) > previous) previous = std::stoi(id);
    }
    std::string unused = std::to_string(previous + 1);

    const std::string status = "Running";

    std::stringstream query;
    query   << "INSERT INTO DriverAuction VALUES ('"
            << unused
            << "', '"
            << orderId
            << "', '"
            << username
            << "', '"
            << std::to_string(startPrice)
            << "', '"
            << std::to_string(startPrice)
            << "', '"
            << std::to_string(commission)
            << "', '"
            << std::to_string(cpm)
            << "', '"
            << std::to_string(distance)
            << "', '"
            << currentDate()
            << "', '"
            << currentTime()
            << "', '"
            << std::to_string(length)
            << "', '"
            << status
            << "');";
    DBHandler::writeFields(query.str());
}

/**
 * Set the auctionStatus of the selected auction table to 'Finished' based on the specified auctionID.
 * @param userType The type of auction table.
 * @param auctionID The auctionID of the auction to be finished.
 */
void Auction::endAuction(const EUserTypes& userType, const std::string& auctionID) {
    std::stringstream query;
    query   << "UPDATE "
            << getTable(userType)
            << " SET auctionStatus = 'Finished' WHERE auctionID = '"
            << auctionID
            << "';";
    DBHandler::writeFields(query.str());
}

/**
 * Update the bid amount of the selected auction table based on the specified auctionID.
 * @param userType The type of auction table.
 * @param auctionID The auctionID of the auction to be updated.
 * @param newBid The new bid amount.
 */
void Auction::setBidAmount(const EUserTypes& userType, const std::string& auctionID, const double& newBid) {
    std::stringstream query;
    query   << "UPDATE "
            << getTable(userType)
            << " SET auctionBidPrice = '"
            << std::to_string(newBid)
            << "' WHERE auctionID = '"
            << auctionID
            << "';";
    DBHandler::writeFields(query.str());
}

/**
 * Set the bidderName of the selected auction table based on the specified auctionID.
 * @param userType The type of auction table.
 * @param auctionID The auctionID of the auction to be updated.
 * @param username The username of the bidder.
 */
void Auction::setBidderName(const EUserTypes& userType, const std::string& auctionID, const std::string& username) {
    std::stringstream query;
    query   << "UPDATE "
            << getTable(userType)
            << " SET auctionBidder = '"
            << username
            << "' WHERE auctionID = '"
            << auctionID
            << "';";
    DBHandler::writeFields(query.str());
}

/**
 * Check if the specified auctionID has a bidder.
 * @param userType The type of auction table.
 * @param auctionID The auctionID of the auction to be checked.
 * @return True if the auction has a bidder, false otherwise.
 */
bool Auction::hasBidder(const EUserTypes& userType, const std::string& auctionID) {
    std::stringstream query;
    query   << "SELECT auctionBidder FROM "
            << getTable(userType)
            << " WHERE auctionID = '"
            << auctionID
            << "';";
    if (DBHandler::getResult(query.str()) != "NONE") return true;
    return false;
}

/**
 * Get the table name based on the specified userType.
 * @param userType The type of user.
 * @return The table name.
 */
std::string Auction::getTable(const EUserTypes& userType) {
    if (userType == EUserTypes::CARGO_OWNER) {
        return "COAuction";
    } else if (userType == EUserTypes::DRIVER) {
        return "DriverAuction";
    }
    return "";
}

/**
 * Get the current date.
 * @return The current date in format 'dd-mm-yyyy'.
 */
std::string Auction::currentDate() {
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
std::string Auction::currentTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    return buf;
}
