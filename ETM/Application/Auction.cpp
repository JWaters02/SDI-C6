#include "Auction.h"

std::vector<COAuctionInfo> Auction::getCORunningAuctions(const std::string& username) {
    std::stringstream query;
    query   << "SELECT * FROM COAuction WHERE username = '"
            << username
            << "' AND auctionStatus = 'Running'";
    std::vector<std::vector<std::string>> runningAuctions = DBHandler::getResult2DVector(query.str());
    return parseAuctionInfo(runningAuctions);
}

std::vector<COAuctionInfo> Auction::parseAuctionInfo(const std::vector<std::vector<std::string>>& auctionInfo) {
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

std::vector<std::string> Auction::getCOAuctionIDs() {
    std::stringstream query;
    query   << "SELECT auctionID FROM COAuction";
    std::vector<std::string> IDs = DBHandler::getResultVector(query.str());
    return IDs;
}

void Auction::makeCOAuction(const std::string& username, const std::string& orderId, const double& startPrice, const double& commission, const int& length) {
    // Get existing auctionIDs
    std::vector<std::string> IDs = getCOAuctionIDs();
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
