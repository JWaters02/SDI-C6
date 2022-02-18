#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QListWidget>
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
    void on_btnConsigneeOrdersAddItem_clicked();
    void on_lwConsigneeOrders_itemClicked(QListWidgetItem *item);
    void on_btnConsigneeOrdersNewOrder_clicked();
    void on_lwConsigneePastOrders_itemClicked(QListWidgetItem *item);

private:
    Ui::HomePage *ui;
    std::vector<OrderInfo> currentOrderInfo;
    std::vector<OrderInfo> pastOrderInfo;

    void loadCurrentOrders();
    void loadPastOrders();
};

#endif // HOMEPAGE_H
