#include "homepage.h"

#include <utility>
#include "ui_homepage.h"
#include "mainwindow.h"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    setUsername();

    // Load current and past orders from DB into list views
    HomePage::loadCurrentOrders();
    HomePage::loadPastOrders();
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::showCorrectPage(EUserTypes userType) {
    if (userType == EUserTypes::ADMIN) {
        ui->Home->setCurrentIndex(0);
    } else if (userType == EUserTypes::CARGO_OWNER) {
        ui->Home->setCurrentIndex(1);
    } else if (userType == EUserTypes::DRIVER) {
        ui->Home->setCurrentIndex(2);
    } else if (userType == EUserTypes::FORWARDER) {
        ui->Home->setCurrentIndex(3);
    } else if (userType == EUserTypes::CONSIGNEE) {
        ui->Home->setCurrentIndex(4);
    } else if (userType == EUserTypes::COURIER) {
        ui->Home->setCurrentIndex(5);
    }
}

void HomePage::setUsername() {
    this->username = Login::getUsername();
}

void HomePage::loadCurrentOrders() {
    currentOrderInfo = Order::getCurrentOrders(username);
    for (const OrderInfo& orderInfo : currentOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | Name: " + orderInfo.name + " | Date: " + orderInfo.date);
        ui->lwConsigneeOrders->addItem(orderInfoString);
    }
}

void HomePage::loadPastOrders() {
    pastOrderInfo = Order::getPastOrders(username);
    for (const OrderInfo& orderInfo : pastOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | Name: " + orderInfo.name + " | Date: " + orderInfo.date);
        ui->lwConsigneePastOrders->addItem(orderInfoString);
    }
}

void HomePage::on_btnCOLogout_clicked()
{
    // Go back to the login page
    auto *w = new MainWindow;
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    this->close();
}

void HomePage::on_btnConsigneeOrdersAddItem_clicked()
{
    new QListWidgetItem(tr("Item X"), ui->lwConsigneeOrders);
    new QListWidgetItem(tr("Item Y"), ui->lwConsigneeOrders);
}

void HomePage::on_lwConsigneeOrders_itemClicked(QListWidgetItem *item)
{
    // Get the order ID from the clicked item
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : currentOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            // Output the order info to the lblConsigneeOrderInfo
            ui->lblConsigneeOrderInfo->setText(QString::fromStdString(
                    "ID: " + orderInfo.id + " | Name: " + orderInfo.name +
                    " | Date: " + orderInfo.date + " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status + " | Price: " + std::to_string(orderInfo.price)));
            break;
        }
    }
}

void HomePage::on_lwConsigneePastOrders_itemClicked(QListWidgetItem *item)
{
    // Get the order ID from the clicked item
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : pastOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            // Output the order info to the lblConsigneeOrderInfo
            ui->lblConsigneePastOrderInfo->setText(QString::fromStdString(
                    "ID: " + orderInfo.id + " | Name: " + orderInfo.name +
                    " | Date: " + orderInfo.date + " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status + " | Price: " + std::to_string(orderInfo.price)));
            break;
        }
    }
}

void HomePage::on_btnConsigneeOrdersNewOrder_clicked()
{

}


