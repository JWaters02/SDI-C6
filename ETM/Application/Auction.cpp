#include "Auction.h"

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

std::vector<COAuctionInfo> Auction::getRunningAuctions(const EUserTypes& userType, const std::string& username) {
    std::stringstream query;
    query   << "SELECT * FROM "
            << getTable(userType)
            << " WHERE username = '"
            << username
            << "' AND auctionStatus = 'Running'";
    return parseCOAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

std::vector<COAuctionInfo> Auction::getOngoingCOAuctions(const EUserTypes& userType) {
    std::stringstream query;
    query   << "SELECT * FROM "
            << getTable(userType)
            << " WHERE auctionStatus = 'Running'";
    return parseCOAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

std::vector<DriverAuctionInfo> Auction::getRunningDriverAuctions(const EUserTypes& userType, const std::string& username) {
    std::stringstream query;
    query   << "SELECT * FROM "
            << getTable(userType)
            << " WHERE username = '"
            << username
            << "' AND auctionStatus = 'Running'";
    return parseDriverAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

std::vector<COAuctionInfo> Auction::getWonCOAuctions(const std::string& username) {
    std::stringstream query;
    query   << "SELECT * FROM COAuction WHERE auctionBidder = '"
            << username
            << "' AND auctionStatus = 'Finished'";
    return parseCOAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

std::vector<DriverAuctionInfo> Auction::getOngoingDriverAuctions(const EUserTypes& userType) {
    std::stringstream query;
    query   << "SELECT * FROM "
            << getTable(userType)
            << " WHERE auctionStatus = 'Running'";
    return parseDriverAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

std::vector<DriverAuctionInfo> Auction::getWonDriverAuctions(const std::string& username) {
    std::stringstream query;
    query   << "SELECT * FROM DriverAuction WHERE auctionBidder = '"
            << username
            << "' AND auctionStatus = 'Finished'";
    return parseDriverAuctionInfo(DBHandler::getResult2DVector(query.str()));
}

std::vector<std::string> Auction::getAuctionIDs(const EUserTypes& userType) {
    std::stringstream query;
    query   << "SELECT auctionID FROM "
            << getTable(userType);
    std::vector<std::string> IDs = DBHandler::getResultVector(query.str());
    return IDs;
}

std::vector<std::string> Auction::getOrderIDs(const EUserTypes& userType) {
    std::stringstream query;
    query   << "SELECT orderID FROM "
            << getTable(userType);
    std::vector<std::string> IDs = DBHandler::getResultVector(query.str());
    return IDs;
}

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

void Auction::endAuction(const EUserTypes& userType, const std::string& auctionID) {
    std::stringstream query;
    query   << "UPDATE "
            << getTable(userType)
            << " SET auctionStatus = 'Finished' WHERE auctionID = '"
            << auctionID
            << "';";
    DBHandler::writeFields(query.str());
}

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

std::string Auction::getTable(const EUserTypes& userType) {
    if (userType == EUserTypes::CARGO_OWNER) {
        return "COAuction";
    } else if (userType == EUserTypes::DRIVER) {
        return "DriverAuction";
    }
    return "";
}

std::string Auction::currentDate() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);
    return buf;
}

std::string Auction::currentTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    return buf;
}
