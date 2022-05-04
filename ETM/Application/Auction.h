#ifndef ETM_AUCTION_H
#define ETM_AUCTION_H

#include <iostream>
#include <ctime>
#include <QString>
#include "Database/DBHandler.h"
#include "Users/UserUtils.h"

/*
CREATE TABLE IF NOT EXISTS COAuction (
      auctionID varchar(4) NOT NULL,
      orderID varchar(4) NOT NULL,
      username varchar(20) NOT NULL,
      auctionStartPrice double precision NOT NULL,
      auctionBidPrice double precision DEFAULT 0.0,
      auctionCommission double precision NOT NULL,
      auctionStartDate date NOT NULL,
      auctionStartTime time NOT NULL,
      auctionLength integer NOT NULL,
      auctionStatus varchar(20) NOT NULL,
      auctionBidder varchar(20) DEFAULT 'NONE',
      FOREIGN KEY (orderID) REFERENCES OrderGoods(orderID),
      FOREIGN KEY (username) REFERENCES Users(username),
      CONSTRAINT co_auction_pk PRIMARY KEY (auctionID)
);
*/

enum EAuctionStatuses {
    RUNNING,
    FINISHED
};

struct AuctionStatuses {
    std::string Running = "Running";
    std::string Finished = "Finished";
};

struct COAuctionInfo {
    std::string auctionId;
    std::string orderId;
    std::string username;
    double startPrice;
    double bidPrice;
    double commission;
    std::string startDate;
    std::string startTime;
    int length; // In hours
    std::string status;
    std::string bidder;
};

class Auction {
private:
    static std::vector<COAuctionInfo> parseAuctionInfo(const std::vector<std::vector<std::string>>& auctionInfo);
    static std::string getTable(const EUserTypes& userType);
    static std::string currentDate();
    static std::string currentTime();

public:
    static std::vector<COAuctionInfo> getRunningAuctions(const EUserTypes& userType, const std::string& username);
    static void makeCOAuction(const std::string& username, const std::string& orderId, const double& startPrice, const double& commission, const int& length);
    static std::vector<std::string> getAuctionIDs(const EUserTypes& userType);
    static bool hasBidder(const std::string& auctionID);
    static void endAuction(const EUserTypes& userType, const std::string& auctionID);
};


#endif //ETM_AUCTION_H
