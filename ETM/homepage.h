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

private:
    Ui::HomePage *ui;
    std::vector<OrderInfo> currentOrderInfo;
    std::vector<OrderInfo> pastOrderInfo;
    std::vector<OrderInfo> allCurrentOrderInfo;
    std::vector<OrderInfo> fTakenOrdersInfo;

    void loadCurrentOrders();
    void loadPastOrders();
    void loadAllCurrentOrders();
    void loadFTakenOrders();

    template <typename T>
    std::string to_string_with_precision(const T in, const int n = 2) {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << in;
        return out.str();
    }
};

#endif // HOMEPAGE_H
