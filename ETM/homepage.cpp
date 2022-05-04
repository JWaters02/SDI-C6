#include "homepage.h"

#include <utility>
#include "ui_homepage.h"
#include "mainwindow.h"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage) {
    ui->setupUi(this);
    setUsername();
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
        HomePage::loadCOTakenOrders();
        HomePage::loadCOFOrders();
        HomePage::loadCOAuctions();
        ui->Home->setCurrentIndex(1);
    } else if (userType == EUserTypes::DRIVER) {
        ui->Home->setCurrentIndex(2);
    } else if (userType == EUserTypes::FORWARDER) {
        HomePage::loadAllCurrentOrders();
        HomePage::loadFTakenOrders();
        ui->Home->setCurrentIndex(3);
    } else if (userType == EUserTypes::CONSIGNEE) {
        HomePage::loadConsigneeCurrentOrders();
        HomePage::loadConsigneePastOrders();
        ui->Home->setCurrentIndex(4);
    } else if (userType == EUserTypes::COURIER) {
        ui->Home->setCurrentIndex(5);
    }
}

void HomePage::setUsername() {
    this->username = Login::getUsername();
}

void HomePage::loadConsigneeCurrentOrders() {
    currentOrderInfo = Order::getCurrentOrders(username);
    for (const OrderInfo& orderInfo : currentOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | Name: " + orderInfo.itemName + " | Date: " + orderInfo.date);
        ui->lwConsigneeOrders->addItem(orderInfoString);
    }
}

void HomePage::loadConsigneePastOrders() {
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
                "ID: " + orderInfo.id + " | Buyer: " + orderInfo.username + " | Name: " + orderInfo.itemName);
        ui->lwFOrders->addItem(orderInfoString);
    }
}

void HomePage::loadFTakenOrders() {
    fTakenOrdersInfo = Order::getTakenOrders(EUserTypes::FORWARDER, this->username);
    for (const OrderInfo& orderInfo : fTakenOrdersInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | Buyer: " + orderInfo.username + " | Name: " + orderInfo.itemName);
        ui->lwFTakenOrders->addItem(orderInfoString);
    }
}

void HomePage::loadCOFOrders() {
    COFOrderInfo = Order::getAllTakenOrders(EUserTypes::FORWARDER);
    for (const OrderInfo& orderInfo : COFOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | Buyer: " + orderInfo.username + " | Name: " + orderInfo.itemName);
        ui->lwCOOrders->addItem(orderInfoString);
    }
}

void HomePage::loadCOTakenOrders() {
    COTakenOrderInfo = Order::getTakenOrders(EUserTypes::CARGO_OWNER, this->username);
    for (const OrderInfo& orderInfo : COTakenOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | Buyer: " + orderInfo.username + " | Name: " + orderInfo.itemName);
        ui->lwCOTakenOrders->addItem(orderInfoString);
        ui->lwCOTakenOrdersBids->addItem(orderInfoString);
    }
}

void HomePage::loadCOAuctions() {
    coAuctionInfo = Auction::getRunningAuctions(EUserTypes::CARGO_OWNER, this->username);
    for (const COAuctionInfo& auctionInfo : coAuctionInfo) {
        QString auctionInfoString = QString::fromStdString(
                    "Auction ID: " + auctionInfo.auctionId +
                    " | Order ID: " + auctionInfo.orderId +
                    " | Bidder: " + auctionInfo.bidder +
                    " | Bid Price: £" + to_string_with_precision(auctionInfo.bidPrice) +
                    " | Commission: £" + to_string_with_precision(auctionInfo.commission) +
                    " | Income: £" + to_string_with_precision(auctionInfo.bidPrice + auctionInfo.commission));
        ui->lwCORunningAuctions->addItem(auctionInfoString);
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
    loadConsigneePastOrders();
    loadConsigneeCurrentOrders();
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

void HomePage::on_btnCOOrdersRefresh_clicked() {
    ui->lwCOOrders->clear();
    ui->lwCOTakenOrders->clear();
    ui->lwCOTakenOrdersBids->clear();
    ui->lblCOTakenOrderInfo->clear();
    ui->lblCOOrderInfo->clear();
    loadCOTakenOrders();
    loadCOFOrders();
}

void HomePage::on_btnCOOrdersTakeOrder_clicked() {
    // Take the clicked order in current orders and put it into taken orders
    if (ui->lwCOOrders->selectedItems().empty()) {
        ui->lblCOTakenOrderInfo->setText("No selected order item!");
    } else if (ui->lwCOOrders->selectedItems().length() > 1) {
        ui->lblCOTakenOrderInfo->setText("Please only select 1 order item!");
    } else {
        // Change the cargoOwner in the table to current
        Order::takeOrder(EUserTypes::CARGO_OWNER, this->username, this->selectedOrderID);
        ui->lblCOTakenOrderInfo->setText("Taken item!");
        ui->lwCOTakenOrders->clear();
        loadCOTakenOrders();
    }
}

void HomePage::on_lwCOTakenOrders_itemClicked(QListWidgetItem *item) {
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : COTakenOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            ui->lblCOTakenOrderInfo->setText(QString::fromStdString(
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

void HomePage::on_lwCOOrders_itemClicked(QListWidgetItem *item) {
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : COFOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            ui->lblCOOrderInfo->setText(QString::fromStdString(
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

void HomePage::on_btnCOBidsRefresh_clicked() {
    ui->lwCOTakenOrdersBids->clear();
    ui->lwCOTakenOrders->clear();
    ui->lblCOTakenOrderInfoBids->clear();
    ui->lblCOCreateAuctionInfo->clear();
    loadCOTakenOrders();
}

void HomePage::on_btnCOBidsCopyOrderPrice_clicked() {
    if (ui->lwCOTakenOrdersBids->selectedItems().empty()) {
        ui->lblCOTakenOrderInfoBids->setText("Select an order to copy from!");
    } else {
        ui->dsbxCOBidsStartingPrice->setValue(this->selectedOrderPrice);
        ui->lblCOTakenOrderInfoBids->setText("Copied price across!");
    }
}

void HomePage::on_lwCOTakenOrdersBids_itemClicked(QListWidgetItem *item) {
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : COTakenOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            ui->lblCOTakenOrderInfoBids->setText(QString::fromStdString(
                    "ID: " + orderInfo.id + " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date + " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status + " | Total Price: "  +
                    to_string_with_precision(orderInfo.unitPrice * orderInfo.quantity) +
                    " | Taken Order"));
            this->selectedOrderPrice = orderInfo.unitPrice * orderInfo.quantity;
            this->selectedOrderID = orderInfo.id;
            break;
        }
    }
}

void HomePage::on_btnCOBidsCreate_clicked() {
    // Check that an order is selected
    if (ui->lwCOTakenOrdersBids->selectedItems().empty()) {
        ui->lblCOCreateAuctionInfo->setText("Select an order to create an auction on!");
    } else {
        // Check that starting price is not less than selectedOrderPrice
        if (ui->dsbxCOBidsStartingPrice->value() < this->selectedOrderPrice) {
            ui->lblCOCreateAuctionInfo->setText("Your starting price must be more than or equal to the order total price!");
        } else {
            // Check if auction for orderID is already running
            // TODO: Maybe this needs to check for username as well?
            std::vector<std::string> runningAuctionOrders = Auction::getAuctionIDs(EUserTypes::CARGO_OWNER);
            // TODO: Possible optimisation: use std::find() instead
            if (std::count(runningAuctionOrders.begin(), runningAuctionOrders.end(), this->selectedOrderID)) {
                ui->lblCOCreateAuctionInfo->setText("Order is already in an auction by you or another cargo owner!");
            } else {
                // Create the auction in the DB
                Auction::makeCOAuction(this->username, this->selectedOrderID, ui->dsbxCOBidsStartingPrice->value(),
                                     ui->dsbxCOBidsCommissionPrice->value(), ui->sbxCOBidsLength->value());
                ui->lblCOCreateAuctionInfo->setText("Created auction!");

                // Refresh the running auctions
                ui->lwCORunningAuctions->clear();
                loadCOAuctions();
            }
        }
    }
}

void HomePage::on_btnCOEndRunningAuction_clicked() {
    // Check that an auction is selected
    if (ui->lwCORunningAuctions->selectedItems().empty()) {
        ui->lblCOCreateAuctionInfo->setText("Please select an auction to end!");
    } else {
        // Check that an auction has a bidder
        if (!Auction::hasBidder(this->selectedRunningAuctionID)) {
            ui->lblCOCreateAuctionInfo->setText("Auction does not have a bidder yet! Please wait longer!");
        } else {
            // Send order ID to bidder
            Order::takeOrder(EUserTypes::DRIVER, this->username, this->selectedOrderID);
            Auction::endAuction(EUserTypes::CARGO_OWNER, this->selectedRunningAuctionID);
            ui->lblCOCreateAuctionInfo->setText("Ended auction and sent order to the bidder!");
            ui->lwCORunningAuctions->clear();
            loadCOAuctions();
        }
    }
}

void HomePage::on_lwCORunningAuctions_itemClicked(QListWidgetItem *item) {
    this->selectedRunningAuctionID = item->text().split(" ")[2].toStdString();
    ui->lblCOCreateAuctionInfo->clear();
}

