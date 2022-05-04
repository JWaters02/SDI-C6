#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QListWidget>
#include <sstream>
#include "Users/UserUtils.h"
#include "Application/Order.h"

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();
    std::string username; // Use this to get data from DB

    void setUsername();
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

private:
    Ui::HomePage *ui;
    std::vector<OrderInfo> currentOrderInfo;
    std::vector<OrderInfo> pastOrderInfo;
    std::vector<OrderInfo> allCurrentOrderInfo;
    std::vector<OrderInfo> fTakenOrdersInfo;
    std::vector<OrderInfo> COTakenOrderInfo;
    std::vector<OrderInfo> COFOrderInfo;
    std::string selectedOrderID;
    double selectedOrderPrice;

    void loadConsigneeCurrentOrders();
    void loadConsigneePastOrders();
    void loadAllCurrentOrders();
    void loadFTakenOrders();
    void loadCOFOrders();
    void loadCOTakenOrders();

    template <typename T>
    std::string to_string_with_precision(const T in, const int n = 2) {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << in;
        return out.str();
    }
};

#endif // HOMEPAGE_H
