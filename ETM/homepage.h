#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QListWidget>
#include <sstream>
#include "Users/UserUtils.h"
#include "Application/Order.h"
#include "Application/Auction.h"

namespace Ui {
class HomePage;
}

class HomePage : public QWidget {
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();
    std::string username = ""; // Use this to get data from DB

    void setUsername(std::string _username);
    void showCorrectPage(EUserTypes userType);

private slots:
    void on_btnCOLogout_clicked();
    void on_lwConsigneeOrders_itemClicked(QListWidgetItem *item);
    void on_btnConsigneeOrdersNewOrder_clicked();
    void on_lwConsigneePastOrders_itemClicked(QListWidgetItem *item);
    void on_btnConsigneeOrdersRefresh_clicked();
    void on_btnFOrdersRefresh_clicked();
    void on_lwFOrders_itemClicked(QListWidgetItem *item);
    void on_btnFOrdersTakeOrder_clicked();
    void on_lwFTakenOrders_itemClicked(QListWidgetItem *item);
    void on_btnCOOrdersRefresh_clicked();
    void on_btnCOOrdersTakeOrder_clicked();
    void on_lwCOTakenOrders_itemClicked(QListWidgetItem *item);
    void on_lwCOOrders_itemClicked(QListWidgetItem *item);
    void on_btnCOBidsRefresh_clicked();
    void on_btnCOBidsCopyOrderPrice_clicked();
    void on_lwCOTakenOrdersBids_itemClicked(QListWidgetItem *item);
    void on_btnCOBidsCreate_clicked();
    void on_btnCOEndRunningAuction_clicked();
    void on_lwCORunningAuctions_itemClicked(QListWidgetItem *item);
    void on_btnDriverBiddingRefresh_clicked();
    void on_btnDriverBid_clicked();
    void on_lwDriverOngoingAuctions_itemClicked(QListWidgetItem *item);
    void on_btnCORefreshRunningAuction_clicked();
    void on_lwDriverWonAuctions_itemClicked(QListWidgetItem *item);

private:
    Ui::HomePage *ui;
    std::vector<OrderInfo> currentOrderInfo;
    std::vector<OrderInfo> pastOrderInfo;
    std::vector<OrderInfo> allCurrentOrderInfo;
    std::vector<OrderInfo> fTakenOrdersInfo;
    std::vector<OrderInfo> COTakenOrderInfo;
    std::vector<OrderInfo> COFOrderInfo;
    std::vector<COAuctionInfo> coAuctionInfo;
    std::vector<COAuctionInfo> driverOngoingAuctionInfo;
    std::vector<COAuctionInfo> driverWonAuctionInfo;
    std::vector<DriverAuctionInfo> driverRunningAuctionInfo;
    std::vector<OrderInfo> driverTakenOrderInfo;
    std::string selectedOrderID;
    double selectedOrderPrice;
    std::string selectedRunningAuctionID;
    std::string selectedRunningAuctionBidder;
    std::string selectedRunningOrderID;
    std::string selectedOngoingAuctionID;

    void loadConsigneeCurrentOrders();
    void loadConsigneePastOrders();
    void loadAllCurrentOrders();
    void loadFTakenOrders();
    void loadCOFOrders();
    void loadCOTakenOrders();
    void loadCOAuctions();
    void loadDriverOngoingAuctions();
    void loadDriverWonAuctions();
    void loadDriverTakenOrders();
    void loadDriverRunningAuctions();

    template <typename T>
    std::string to_string_with_precision(const T in, const int n = 2) {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << in;
        return out.str();
    }
};

#endif // HOMEPAGE_H
