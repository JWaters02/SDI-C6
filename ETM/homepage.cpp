#include "homepage.h"

#include <utility>
#include "ui_homepage.h"
#include "mainwindow.h"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage) {
    ui->setupUi(this);
    setUsername();

    // Load current and past orders from DB into list views
    HomePage::loadCurrentOrders();
    HomePage::loadPastOrders();
    HomePage::loadAllCurrentOrders();
    HomePage::loadFTakenOrders();
}

HomePage::~HomePage() {
    delete ui;
}

void HomePage::on_btnCOLogout_clicked() {
    // Go back to the login page
    auto *w = new MainWindow;
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    this->close();
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
                "ID: " + orderInfo.id + " | Name: " + orderInfo.itemName + " | Date: " + orderInfo.date);
        ui->lwConsigneeOrders->addItem(orderInfoString);
    }
}

void HomePage::loadPastOrders() {
    pastOrderInfo = Order::getPastOrders(username);
    for (const OrderInfo& orderInfo : pastOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | Name: " + orderInfo.itemName + " | Date: " + orderInfo.date);
        ui->lwConsigneePastOrders->addItem(orderInfoString);
    }
}

void HomePage::loadAllCurrentOrders() {
    allCurrentOrderInfo = Order::getAllCurrentOrders();
    for (const OrderInfo& orderInfo : allCurrentOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | User: " + orderInfo.username + " | Name: " + orderInfo.itemName);
        ui->lwFOrders->addItem(orderInfoString);
    }
}

void HomePage::loadFTakenOrders() {
    fTakenOrdersInfo = Order::getTakenOrders(EUserTypes::FORWARDER, this->username);
    for (const OrderInfo& orderInfo : fTakenOrdersInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | User: " + orderInfo.username + " | Name: " + orderInfo.itemName);
        ui->lwFTakenOrders->addItem(orderInfoString);
    }
}

void HomePage::on_lwConsigneeOrders_itemClicked(QListWidgetItem *item) {
    // Get the order ID from the clicked item
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : currentOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            ui->lblConsigneeOrderInfo->setText(QString::fromStdString(
                    "ID: " + orderInfo.id + " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date + " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status + " | Total Price: " +
                    to_string_with_precision(orderInfo.unitPrice * orderInfo.quantity)));
            break;
        }
    }
}

void HomePage::on_lwConsigneePastOrders_itemClicked(QListWidgetItem *item) {
    // Get the order ID from the clicked item
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : pastOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            ui->lblConsigneePastOrderInfo->setText(QString::fromStdString(
                    "ID: " + orderInfo.id + " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date + " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status + " | Total Price: "  +
                    to_string_with_precision(orderInfo.unitPrice * orderInfo.quantity)));
            break;
        }
    }
}

void HomePage::on_btnConsigneeOrdersNewOrder_clicked() {
    if (ui->txtConsigneeOrderItemName->text().isEmpty()) {
        ui->lblConsigneeOrderItemInfo->setText("Invalid item name!");
    } else {
        Order::makeOrder(this->username, ui->txtConsigneeOrderItemName->text().toStdString(),
                         ui->sbxConsigneeOrderQuantity->value(), ui->dsbxConsigneeOrderPrice->value());
        ui->lblConsigneeOrderItemInfo->setText("Placed order!");
    }
}

void HomePage::on_btnConsigneeOrdersRefresh_clicked() {
    ui->lblConsigneeOrderItemInfo->clear();
    ui->lwConsigneeOrders->clear();
    ui->lwConsigneePastOrders->clear();
    loadPastOrders();
    loadCurrentOrders();
}


void HomePage::on_btnFOrdersRefresh_clicked() {
    ui->lblFOrderInfo->clear();
    ui->lblFTakenOrderInfo->clear();
    ui->lwFTakenOrders->clear();
    ui->lwFOrders->clear();
    loadAllCurrentOrders();
    loadFTakenOrders();
}

void HomePage::on_lwFOrders_itemClicked(QListWidgetItem *item) {
    // Get the order ID from the clicked item
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : allCurrentOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            ui->lblFOrderInfo->setText(QString::fromStdString(
                    "ID: " + orderInfo.id + " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date + " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status + " | Total Price: "  +
                    to_string_with_precision(orderInfo.unitPrice * orderInfo.quantity)));
            this->selectedOrderID = orderInfo.id;
            break;
        }
    }
}

void HomePage::on_btnFOrdersTakeOrder_clicked() {
    // Take the clicked order in current orders and put it into taken orders
    if (ui->lwFOrders->selectedItems().empty()) {
        ui->lblFTakenOrderInfo->setText("No selected order item!");
    } else if (ui->lwFOrders->selectedItems().length() > 1) {
        ui->lblFTakenOrderInfo->setText("Please only select 1 order item!");
    } else {
        // Change the forwarder in the table to current
        Order::takeOrder(EUserTypes::FORWARDER, this->username, this->selectedOrderID);

        ui->lblFTakenOrderInfo->setText("Taken item!");
        ui->lwFTakenOrders->clear();
        loadFTakenOrders();
    }
}


void HomePage::on_lwFTakenOrders_itemClicked(QListWidgetItem *item) {
    // Get the order ID from the clicked item
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : fTakenOrdersInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            ui->lblFTakenOrderInfo->setText(QString::fromStdString(
                    "ID: " + orderInfo.id + " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date + " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status + " | Total Price: "  +
                    to_string_with_precision(orderInfo.unitPrice * orderInfo.quantity) +
                    " | Taken Order"));
            break;
        }
    }
}

