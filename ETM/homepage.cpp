#include "homepage.h"

#include <utility>
#include "ui_homepage.h"
#include "mainwindow.h"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage) {
    ui->setupUi(this);
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
        loadCOTakenOrders();
        loadCOFOrders();
        loadCOAuctions();
        ui->Home->setCurrentIndex(1);
    } else if (userType == EUserTypes::DRIVER) {
        loadDriverOngoingAuctions();
        loadDriverWonAuctions();
        loadDriverRunningAuctions();
        loadDriverTakenOrders();
        ui->Home->setCurrentIndex(2);
    } else if (userType == EUserTypes::FORWARDER) {
        loadAllCurrentOrders();
        loadFTakenOrders();
        ui->Home->setCurrentIndex(3);
    } else if (userType == EUserTypes::CONSIGNEE) {
        loadConsigneeCurrentOrders();
        loadConsigneePastOrders();
        ui->Home->setCurrentIndex(4);
    } else if (userType == EUserTypes::COURIER) {
        loadCourierOngoingAuctions();
        loadCourierWonAuctions();
        ui->Home->setCurrentIndex(5);
    }
}

void HomePage::setUsername(std::string _username) {
    this->username = _username;
}

void HomePage::loadConsigneeCurrentOrders() {
    currentOrderInfo = Order::getCurrentOrders(username);
    for (const OrderInfo& orderInfo : currentOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id +
                " | Name: " + orderInfo.itemName +
                " | Price: £" + to_string_with_precision(orderInfo.unitPrice * orderInfo.quantity));
        ui->lwConsigneeOrders->addItem(orderInfoString);
    }
}

void HomePage::loadConsigneePastOrders() {
    pastOrderInfo = Order::getPastOrders(username);
    for (const OrderInfo& orderInfo : pastOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id +
                " | Name: " + orderInfo.itemName +
                " | Price + Fees: £" + to_string_with_precision(orderInfo.fees + (orderInfo.unitPrice * orderInfo.quantity)));
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

void HomePage::loadDriverOngoingAuctions() {
    driverOngoingAuctionInfo = Auction::getOngoingCOAuctions(EUserTypes::CARGO_OWNER);
    for (const COAuctionInfo& auctionInfo : driverOngoingAuctionInfo) {
        QString auctionInfoString = QString::fromStdString(
                    "Auction ID: " + auctionInfo.auctionId +
                    " | Order ID: " + auctionInfo.orderId +
                    " | Bid Price: £" + to_string_with_precision(auctionInfo.bidPrice));
        ui->lwDriverOngoingAuctions->addItem(auctionInfoString);
    }
}

void HomePage::loadDriverWonAuctions() {
    driverWonAuctionInfo = Auction::getWonCOAuctions(this->username);
    for (const COAuctionInfo& auctionInfo : driverWonAuctionInfo) {
        QString auctionInfoString = QString::fromStdString(
                    "Auction ID: " + auctionInfo.auctionId +
                    " | Order ID: " + auctionInfo.orderId +
                    " | Paid: £" + to_string_with_precision(auctionInfo.bidPrice + auctionInfo.commission));
        ui->lwDriverWonAuctions->addItem(auctionInfoString);
    }
}

void HomePage::loadDriverTakenOrders() {
    driverTakenOrderInfo = Order::getTakenOrders(EUserTypes::DRIVER, this->username);
    for (const OrderInfo& orderInfo : driverTakenOrderInfo) {
        QString orderInfoString = QString::fromStdString(
                "ID: " + orderInfo.id + " | Buyer: " + orderInfo.username + " | Name: " + orderInfo.itemName);
        ui->lwDriverTakenOrders->addItem(orderInfoString);
    }
}

void HomePage::loadDriverRunningAuctions() {
    driverRunningAuctionInfo = Auction::getRunningDriverAuctions(EUserTypes::DRIVER, this->username);
    for (const DriverAuctionInfo& auctionInfo : driverRunningAuctionInfo) {
        QString auctionInfoString = QString::fromStdString(
                    "Auction ID: " + auctionInfo.auctionId +
                    " | Order ID: " + auctionInfo.orderId +
                    " | Bidder: " + auctionInfo.bidder +
                    " | Bid Price: £" + to_string_with_precision(auctionInfo.bidPrice) +
                    " | Commission: £" + to_string_with_precision(auctionInfo.commission) +
                    " | Income: £" + to_string_with_precision(auctionInfo.bidPrice + auctionInfo.commission));
        ui->lwDriverRunningAuctions->addItem(auctionInfoString);
    }
}

void HomePage::loadCourierOngoingAuctions() {
    courierOngoingAuctionInfo = Auction::getOngoingDriverAuctions(EUserTypes::DRIVER);
    for (const DriverAuctionInfo& auctionInfo : courierOngoingAuctionInfo) {
        QString auctionInfoString = QString::fromStdString(
                    "Auction ID: " + auctionInfo.auctionId +
                    " | Order ID: " + auctionInfo.orderId +
                    " | Bid Price: £" + to_string_with_precision(auctionInfo.bidPrice));
        ui->lwCourierOngoingAuctions->addItem(auctionInfoString);
    }
}

void HomePage::loadCourierWonAuctions() {
    courierWonAuctionInfo = Auction::getWonDriverAuctions(this->username);
    for (const DriverAuctionInfo& auctionInfo : courierWonAuctionInfo) {
        QString auctionInfoString = QString::fromStdString(
                    "Auction ID: " + auctionInfo.auctionId +
                    " | Order ID: " + auctionInfo.orderId +
                    " | Paid: £" + to_string_with_precision(auctionInfo.bidPrice + auctionInfo.commission +
                                                            (auctionInfo.costPerMile * auctionInfo.distance)));
        ui->lwCourierWonAuctions->addItem(auctionInfoString);
    }
}


void HomePage::on_lwConsigneeOrders_itemClicked(QListWidgetItem *item) {
    // Get the order ID from the clicked item
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : currentOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            QString orderInfoString = (QString::fromStdString(
                    "ID: " + orderInfo.id +
                    " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date +
                    " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status +
                    " | Total Price: £"  + to_string_with_precision((orderInfo.unitPrice * orderInfo.quantity) + orderInfo.fees)));
            ui->lblConsigneeOrderInfo->setText(orderInfoString);
            break;
        }
    }
}

void HomePage::on_lwConsigneePastOrders_itemClicked(QListWidgetItem *item) {
    // Get the order ID from the clicked item
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : pastOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            QString orderInfoString = (QString::fromStdString(
                    "ID: " + orderInfo.id +
                    " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date +
                    " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status +
                    " | Total Price: £"  + to_string_with_precision((orderInfo.unitPrice * orderInfo.quantity) + orderInfo.fees)));
            ui->lblConsigneePastOrderInfo->setText(orderInfoString);
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
            QString orderInfoString = (QString::fromStdString(
                    "ID: " + orderInfo.id +
                    " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date +
                    " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status +
                    " | Total Price: £"  + to_string_with_precision((orderInfo.unitPrice * orderInfo.quantity) + orderInfo.fees)));
            ui->lblFOrderInfo->setText(orderInfoString);
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
            QString orderInfoString = (QString::fromStdString(
                    "ID: " + orderInfo.id +
                    " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date +
                    " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status +
                    " | Total Price: £"  + to_string_with_precision((orderInfo.unitPrice * orderInfo.quantity) + orderInfo.fees) +
                    " | Taken Order"));
            ui->lblFTakenOrderInfo->setText(orderInfoString);
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
            QString orderInfoString = (QString::fromStdString(
                    "ID: " + orderInfo.id +
                    " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date +
                    " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status +
                    " | Total Price: £"  + to_string_with_precision((orderInfo.unitPrice * orderInfo.quantity) + orderInfo.fees) +
                    " | Taken Order"));
            ui->lblCOTakenOrderInfo->setText(orderInfoString);
            break;
        }
    }
}

void HomePage::on_lwCOOrders_itemClicked(QListWidgetItem *item) {
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : COFOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            QString orderInfoString = (QString::fromStdString(
                    "ID: " + orderInfo.id +
                    " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date +
                    " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status +
                    " | Total Price: £"  + to_string_with_precision((orderInfo.unitPrice * orderInfo.quantity) + orderInfo.fees)));
            ui->lblCOOrderInfo->setText(orderInfoString);
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
            QString orderInfoString = (QString::fromStdString(
                    "ID: " + orderInfo.id +
                    " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Date: " + orderInfo.date +
                    " | Time: " + orderInfo.time +
                    " | Status: " + orderInfo.status +
                    " | Total Price: £"  + to_string_with_precision((orderInfo.unitPrice * orderInfo.quantity) + orderInfo.fees) +
                    " | Taken Order"));
            ui->lblCOTakenOrderInfoBids->setText(orderInfoString);
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
            std::vector<std::string> runningAuctionOrders = Auction::getOrderIDs(EUserTypes::CARGO_OWNER);
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

void HomePage::on_btnCORefreshRunningAuction_clicked() {
    ui->lwCORunningAuctions->clear();
    loadCOAuctions();
}

void HomePage::on_btnCOEndRunningAuction_clicked() {
    // Check that an auction is selected
    if (ui->lwCORunningAuctions->selectedItems().empty()) {
        ui->lblCOCreateAuctionInfo->setText("Please select an auction to end!");
    } else {
        // Check that an auction has a bidder
        if (!Auction::hasBidder(EUserTypes::CARGO_OWNER, this->selectedRunningAuctionID)) {
            ui->lblCOCreateAuctionInfo->setText("Auction does not have a bidder yet! Please wait longer!");
        } else {
            // Send order ID to bidder, username needs to be bidder's username
            Order::takeOrder(EUserTypes::DRIVER, this->selectedRunningAuctionBidder, this->selectedRunningOrderID);
            Auction::endAuction(EUserTypes::CARGO_OWNER, this->selectedRunningAuctionID);

            // Increase the total price of the order ID by the income
            double income = 0.0;
            for (const COAuctionInfo& auctionInfo : coAuctionInfo) {
                if (auctionInfo.auctionId == this->selectedRunningAuctionID) {
                    income = auctionInfo.bidPrice + auctionInfo.commission;
                }
            }
            Order::increaseTotalPrice(this->selectedRunningOrderID, income);

            ui->lblCOCreateAuctionInfo->setText("Ended auction and sent order to the bidder!");
            ui->lwCORunningAuctions->clear();
            loadCOAuctions();
        }
    }
}

void HomePage::on_lwCORunningAuctions_itemClicked(QListWidgetItem *item) {
    this->selectedRunningAuctionID = item->text().split(" ")[2].toStdString();
    this->selectedRunningOrderID = item->text().split(" ")[6].toStdString();
    this->selectedRunningAuctionBidder = item->text().split(" ")[9].toStdString();
    ui->lblCOCreateAuctionInfo->clear();
}

void HomePage::on_btnDriverBiddingRefresh_clicked() {
    ui->lwDriverOngoingAuctions->clear();
    ui->lblDriverOngoingAuctionsInfo->clear();
    ui->lwDriverWonAuctions->clear();
    ui->lblDriverWonAuctionsInfo->clear();
    loadDriverOngoingAuctions();
    loadDriverWonAuctions();
}

void HomePage::on_btnDriverBid_clicked() {
    // Check that an auction is selected
    if (ui->lwDriverOngoingAuctions->selectedItems().empty()) {
        ui->lblDriverOngoingAuctionsInfo->setText("Please select an auction to bid on!");
    } else {
        // Get the current bid amount and orderID from selected auctionID
        double currentBid = 0.0;
        std::string orderID;
        for (const COAuctionInfo& auctionInfo : driverOngoingAuctionInfo) {
            if (auctionInfo.auctionId == this->selectedOngoingAuctionID) {
                currentBid = auctionInfo.bidPrice;
                orderID = auctionInfo.auctionId;
            }
        }

        // Add the value from bid increase to bid amount
        double newBid = ui->dsbxDriverBidAmount->value() + currentBid;
        Auction::setBidAmount(EUserTypes::CARGO_OWNER, this->selectedOngoingAuctionID, newBid);

        // Change the bidder name to this.username
        Auction::setBidderName(EUserTypes::CARGO_OWNER, this->selectedOngoingAuctionID, this->username);

        ui->lblDriverOngoingAuctionsInfo->setText("Bid on the selected auction!");
        ui->lwDriverOngoingAuctions->clear();
        loadDriverOngoingAuctions();
    }
}

void HomePage::on_lwDriverOngoingAuctions_itemClicked(QListWidgetItem *item) {
    QString auctionID = item->text().split(" ")[2];
    for (const COAuctionInfo& auctionInfo : driverOngoingAuctionInfo) {
        if (auctionInfo.auctionId == auctionID.toStdString()) {
            QString auctionInfoString = QString::fromStdString(
                        "Auction ID: " + auctionInfo.auctionId +
                        " | Order ID: " + auctionInfo.orderId +
                        " | Bidder: " + auctionInfo.bidder +
                        " | Bid Price: £" + to_string_with_precision(auctionInfo.bidPrice) +
                        " | Commission: £" + to_string_with_precision(auctionInfo.commission));
            ui->lblDriverOngoingAuctionsInfo->setText(auctionInfoString);
            break;
        }
    }
    this->selectedOngoingAuctionID = item->text().split(" ")[2].toStdString();
}

void HomePage::on_lwDriverWonAuctions_itemClicked(QListWidgetItem *item) {
    QString auctionID = item->text().split(" ")[2];
    for (const COAuctionInfo& auctionInfo : driverWonAuctionInfo) {
        if (auctionInfo.auctionId == auctionID.toStdString()) {
            QString auctionInfoString = QString::fromStdString(
                        "Auction ID: " + auctionInfo.auctionId +
                        " | Order ID: " + auctionInfo.orderId +
                        " | Bid Price: £" + to_string_with_precision(auctionInfo.bidPrice) +
                        " | Commission: £" + to_string_with_precision(auctionInfo.commission) +
                        " | Paid: £" + to_string_with_precision(auctionInfo.bidPrice + auctionInfo.commission));
            ui->lblDriverWonAuctionsInfo->setText(auctionInfoString);
            break;
        }
    }
}

void HomePage::on_lwDriverTakenOrders_itemClicked(QListWidgetItem *item) {
    QString orderID = item->text().split(" ")[1];
    for (const OrderInfo& orderInfo : driverTakenOrderInfo) {
        if (orderInfo.id == orderID.toStdString()) {
            QString auctionInfoString = (QString::fromStdString(
                    "ID: " + orderInfo.id +
                    " | User: " + orderInfo.username +
                    " | Name: " + orderInfo.itemName +
                    " | Status: " + orderInfo.status +
                    " | Price: " + to_string_with_precision(orderInfo.unitPrice * orderInfo.quantity) +
                    " | Total Price w/ Fees: " + to_string_with_precision(orderInfo.unitPrice * orderInfo.quantity + orderInfo.fees) +
                    " | Taken Order"));
            ui->lblDriverAuctionInfo->setText(auctionInfoString);
            this->selectedOrderPrice = orderInfo.unitPrice * orderInfo.quantity;
            this->selectedOrderID = orderInfo.id;
            break;
        }
    }
}

void HomePage::on_btnDriverAuctionsRefresh_clicked() {
    ui->lblDriverAuctionInfo->clear();
    ui->lwDriverTakenOrders->clear();
    loadDriverTakenOrders();
}

void HomePage::on_btnDriverBidsCopyOrderPrice_clicked() {
    if (ui->lwDriverTakenOrders->selectedItems().empty()) {
        ui->lblDriverAuctionInfo->setText("Select an order to copy from!");
    } else {
        ui->dsbxDriverBidsStartingPrice->setValue(this->selectedOrderPrice);
        ui->lblDriverAuctionInfo->setText("Copied price across!");
    }
}


void HomePage::on_btnDriverBidsCreate_clicked() {
    // Check that an order is selected
    if (ui->lwDriverTakenOrders->selectedItems().empty()) {
        ui->lblDriverAuctionInfo->setText("Select an order to create an auction on!");
    } else {
        // Check that starting price is not less than selectedOrderPrice
        if (ui->dsbxDriverBidsStartingPrice->value() < this->selectedOrderPrice) {
            ui->lblDriverAuctionInfo->setText("Your starting price must be more than or equal to the order total price!");
        } else {
            // Check if auction for orderID is already running
            std::vector<std::string> runningAuctionOrders = Auction::getOrderIDs(EUserTypes::DRIVER);
            if (std::count(runningAuctionOrders.begin(), runningAuctionOrders.end(), this->selectedOrderID)) {
                ui->lblDriverAuctionInfo->setText("Order is already in an auction by you or another cargo owner!");
            } else {
                // Create the auction in the DB
                Auction::makeDriverAuction(this->username, this->selectedOrderID, ui->dsbxDriverBidsStartingPrice->value(),
                                     ui->dsbxDriverBidsCommissionPrice->value(), ui->dsbxDriverBidsCostPMile->value(),
                                     ui->dsbxDriverBidsDistance->value(), ui->sbxCOBidsLength->value());
                ui->lblDriverAuctionInfo->setText("Created auction!");

                // Refresh the running auctions
                ui->lwDriverRunningAuctions->clear();
                loadDriverRunningAuctions();
            }
        }
    }
}

void HomePage::on_btnDriverRefreshRunningAuction_clicked() {
    ui->lblDriverAuctionInfo->clear();
    ui->lwDriverRunningAuctions->clear();
    loadDriverRunningAuctions();
}

void HomePage::on_lwDriverRunningAuctions_itemClicked(QListWidgetItem *item) {
    this->selectedRunningAuctionID = item->text().split(" ")[2].toStdString();
    this->selectedRunningOrderID = item->text().split(" ")[6].toStdString();
    this->selectedRunningAuctionBidder = item->text().split(" ")[9].toStdString();
    ui->lblDriverAuctionInfo->clear();
}

void HomePage::on_btnDriverEndRunningAuction_clicked() {
    // Check that an auction is selected
    if (ui->lwDriverRunningAuctions->selectedItems().empty()) {
        ui->lblDriverAuctionInfo->setText("Please select an auction to end!");
    } else {
        // Check that an auction has a bidder
        if (!Auction::hasBidder(EUserTypes::DRIVER, this->selectedRunningAuctionID)) {
            ui->lblDriverAuctionInfo->setText("Auction does not have a bidder yet! Please wait longer!");
        } else {
            // Send order ID to bidder, username needs to be bidder's username
            Order::takeOrder(EUserTypes::COURIER, this->selectedRunningAuctionBidder, this->selectedRunningOrderID);
            Auction::endAuction(EUserTypes::DRIVER, this->selectedRunningAuctionID);

            // Increase the total price of the order ID by the income
            double income = 0.0;
            for (const DriverAuctionInfo& auctionInfo : driverRunningAuctionInfo) {
                if (auctionInfo.auctionId == this->selectedRunningAuctionID) {
                    income = auctionInfo.bidPrice + auctionInfo.commission +
                            (auctionInfo.distance * auctionInfo.costPerMile);
                }
            }
            Order::increaseTotalPrice(this->selectedRunningOrderID, income);

            ui->lblDriverAuctionInfo->setText("Ended auction and sent order to the bidder!");
            ui->lwDriverRunningAuctions->clear();
            loadDriverRunningAuctions();
        }
    }
}

void HomePage::on_btnCourierBiddingRefresh_clicked() {
    ui->lwCourierOngoingAuctions->clear();
    ui->lblCourierOngoingAuctionsInfo->clear();
    ui->lwCourierWonAuctions->clear();
    ui->lblCourierWonAuctionsInfo->clear();
    loadCourierOngoingAuctions();
    loadCourierWonAuctions();
}

void HomePage::on_lwCourierOngoingAuctions_itemClicked(QListWidgetItem *item) {
    QString auctionID = item->text().split(" ")[2];
    for (const DriverAuctionInfo& auctionInfo : courierOngoingAuctionInfo) {
        if (auctionInfo.auctionId == auctionID.toStdString()) {
            QString auctionInfoString = QString::fromStdString(
                        "Auction ID: " + auctionInfo.auctionId +
                        " | Order ID: " + auctionInfo.orderId +
                        " | Bidder: " + auctionInfo.bidder +
                        " | Bid Price: £" + to_string_with_precision(auctionInfo.bidPrice) +
                        " | Commission: £" + to_string_with_precision(auctionInfo.commission) +
                        " | Cost Per Mile: £" + to_string_with_precision(auctionInfo.costPerMile) +
                        " | Distance: " + to_string_with_precision(auctionInfo.distance) + " miles");
            ui->lblCourierOngoingAuctionsInfo->setText(auctionInfoString);
            break;
        }
    }
    this->selectedOngoingAuctionID = item->text().split(" ")[2].toStdString();
}

void HomePage::on_btnCourierBid_clicked() {
    // Check that an auction is selected
    if (ui->lwCourierOngoingAuctions->selectedItems().empty()) {
        ui->lblCourierOngoingAuctionsInfo->setText("Please select an auction to bid on!");
    } else {
        // Get the current bid amount and orderID from selected auctionID
        double currentBid = 0.0;
        std::string orderID;
        for (const DriverAuctionInfo& auctionInfo : courierOngoingAuctionInfo) {
            if (auctionInfo.auctionId == this->selectedOngoingAuctionID) {
                currentBid = auctionInfo.bidPrice;
                orderID = auctionInfo.auctionId;
            }
        }

        // Add the value from bid increase to bid amount
        double newBid = ui->dsbxCourierBidAmount->value() + currentBid;
        Auction::setBidAmount(EUserTypes::DRIVER, this->selectedOngoingAuctionID, newBid);

        // Change the bidder name to this.username
        Auction::setBidderName(EUserTypes::DRIVER, this->selectedOngoingAuctionID, this->username);

        ui->lblCourierOngoingAuctionsInfo->setText("Bid on the selected auction!");
        ui->lwCourierOngoingAuctions->clear();
        loadCourierOngoingAuctions();
    }
}

void HomePage::on_lwCourierWonAuctions_itemClicked(QListWidgetItem *item) {
    QString auctionID = item->text().split(" ")[2];
    for (const DriverAuctionInfo& auctionInfo : courierWonAuctionInfo) {
        if (auctionInfo.auctionId == auctionID.toStdString()) {
            QString auctionInfoString = QString::fromStdString(
                        "Auction ID: " + auctionInfo.auctionId +
                        " | Order ID: " + auctionInfo.orderId +
                        " | Bid Price: £" + to_string_with_precision(auctionInfo.bidPrice) +
                        " | Commission: £" + to_string_with_precision(auctionInfo.commission) +
                        " | Cost Per Mile: £" + to_string_with_precision(auctionInfo.costPerMile) +
                        " | Distance: " + to_string_with_precision(auctionInfo.distance) + " miles" +
                        " | Paid: £" + to_string_with_precision(auctionInfo.bidPrice + auctionInfo.commission +
                                                                (auctionInfo.costPerMile * auctionInfo.distance)));
            ui->lblCourierWonAuctionsInfo->setText(auctionInfoString);
            this->selectedWonOrderID = auctionInfo.orderId;
            break;
        }
    }
}

void HomePage::on_btnCourierDeliverWonOrder_clicked() {
    // Check that a won auction is selected
    if (ui->lwCourierWonAuctions->selectedItems().empty()) {
        ui->lblCourierWonAuctionsInfo->setText("Please select an order to deliver!");
    } else {
        // Update the orderID to delivered
        Order::deliverOrder(this->selectedWonOrderID);
        ui->lblCourierWonAuctionsInfo->setText("Delivered order to customer!");
    }
}

