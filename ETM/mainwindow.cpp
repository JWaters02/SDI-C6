#include "mainwindow.h"
#include "./ui_mainwindow.h"

LoginInfo submittedLoginInfo;
SignupInfo submittedSignupInfo;
DriverSignupInfo submittedDriverSignupInfo;
CargoOwnerSignupInfo submittedCargoOwnerSignupInfo;
CourierSignupInfo submittedCourierSignupInfo;
ForwarderSignupInfo submittedForwarderSignupInfo;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setInvalidLoginFeedback(ErrorTypes errorType) {
    switch (errorType) {
        case ErrorTypes::INVALID_LOGIN:
            ui->lblLoginIncorrect->setText("Username or password is incorrect!");
            break;
        case ErrorTypes::USERNAME_NOT_FOUND:
            ui->lblLoginIncorrect->setText("Username does not exist!");
            break;
        case ErrorTypes::EMPTY_USERNAME:
            ui->lblLoginIncorrect->setText("Invalid username!");
            break;
        case ErrorTypes::NOT_ALL_FIELDS_FILLED:
            ui->lblLoginIncorrect->setText("Please fill both fields!");
            break;
        case ErrorTypes::PASSWORDS_DO_NOT_MATCH:
            ui->lblLoginIncorrect->setText("Incorrect password!");
            break;
        case ErrorTypes::SUCCESS:
            ui->lblLoginIncorrect->setText("");
            break;
        default:
            break;
    }
}

void MainWindow::setInvalidSignupFeedback(ErrorTypes errorType) {
    switch (errorType) {
        case ErrorTypes::USERNAME_ALREADY_EXISTS:
            ui->lblSignupIncorrect->setText("Username taken!");
            break;
        case ErrorTypes::NOT_ALL_FIELDS_FILLED:
            ui->lblSignupIncorrect->setText("Please fill all fields with valid info!");
            break;
        case ErrorTypes::NO_USERTYPE_SELECTED:
            ui->lblSignupIncorrect->setText("Please select a user type!");
            break;
        case ErrorTypes::PASSWORDS_DO_NOT_MATCH:
            ui->lblSignupIncorrect->setText("Passwords do not match!");
            break;
        case ErrorTypes::SUCCESS:
            ui->lblSignupIncorrect->setText("");
            break;
        default:
            break;
    }
}

void MainWindow::setInvalidDriversSignupFeedback() {
    ui->lblDriversSignupIncorrect->setText(QString::fromStdString("Please fill all fields with valid info!"));
}

void MainWindow::setInvalidCargoOwnerSignupFeedback() {
    ui->lblCargoOwnerSignupIncorrect->setText(QString::fromStdString("Please fill all fields with valid info!"));
}

void MainWindow::setInvalidForwarderSignupFeedback() {
    ui->lblForwarderSignupIncorrect->setText(QString::fromStdString("Please fill all fields with valid info!"));
}

void MainWindow::setInvalidCourierSignupFeedback() {
    ui->lblCourierSignupIncorrect->setText(QString::fromStdString("Please fill all fields with valid info!"));
}

void MainWindow::on_btnLogin_clicked() {
    submittedLoginInfo.username = ui->txtLoginUsername->text().toStdString();
    submittedLoginInfo.password = ui->txtLoginPassword->text().toStdString();

    // Check if login info is valid
    if (Login::isValidLogin(getLoginInfo()) != ErrorTypes::SUCCESS) {
        setInvalidLoginFeedback(Login::isValidLogin(getLoginInfo()));
    } else {
        // Go to the next page
        auto *w = new HomePage;
        w->setAttribute(Qt::WA_DeleteOnClose);
        // Query the DB to get the user's type
        EUserTypes userType = Login::getUserType(getLoginInfo());
        if (userType == EUserTypes::NONE) return; // TODO: Probably need to return a DB error since no user type was found

        // Show the correct menu depending on type
        w->showCorrectPage(userType);

        // Close login menu and show main window
        w->show();
        this->close();
    }
}

void MainWindow::on_btnSignup_clicked() {
    submittedSignupInfo.username = ui->txtSignupUsername->text().toStdString();
    submittedSignupInfo.password = ui->txtSignupPassword->text().toStdString(); // We don't want to hash it yet
    submittedSignupInfo.firstName = ui->txtSignupFirstName->text().toStdString();
    submittedSignupInfo.lastName = ui->txtSignupLastName->text().toStdString();
    submittedSignupInfo.age = ui->txtSignupAge->text().toInt();
    submittedSignupInfo.email = ui->txtSignupEmail->text().toStdString();
    submittedSignupInfo.phone = ui->txtSignupMobile->text().toStdString();
    submittedSignupInfo.homeAddress = ui->txtSignupHomeAddress->text().toStdString();
    submittedSignupInfo.homeCity = ui->txtSignupHomeCity->text().toStdString();

    // Check passwords do not match
    if (ui->txtSignupPassword->text().toStdString() != ui->txtSignupConfirmPassword->text().toStdString()) {
        ui->lblSignupIncorrect->setText(QString::fromStdString("Passwords do not match!"));
    // Validate signup info is all valid
    } else if (Login::isValidSignup(getSignupInfo()) != ErrorTypes::SUCCESS) {
        setInvalidSignupFeedback(Login::isValidSignup(getSignupInfo()));
    } else {
        // Check which user type is selected
        if (ui->rbCargoOwner->isChecked()) {
            submittedSignupInfo.type = UserType.CargoOwner;
            ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP_CARGO_OWNER);
        } else if (ui->rbDriver->isChecked()) {
            submittedSignupInfo.type = UserType.Driver;
            ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP_DRIVER);
        } else if (ui->rbForwarder->isChecked()) {
            submittedSignupInfo.type = UserType.Forwarder;
            ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP_FORWARDER);
        } else if (ui->rbCourier->isChecked()) {
            submittedSignupInfo.type = UserType.Courier;
            ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP_COURIER);
        } else if (ui->rbAdmin->isChecked()) {
            submittedSignupInfo.type = UserType.Admin;
            Login::storeSignupDetails(getSignupInfo());
            ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
        } else if (ui->rbConsignee->isChecked()) {
            submittedSignupInfo.type = UserType.Consignee;
            Login::storeSignupDetails(getSignupInfo());
            ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
        } else {
            setInvalidSignupFeedback(ErrorTypes::NO_USERTYPE_SELECTED);
        }
    }
}

void MainWindow::on_btnLoginSignup_clicked() {
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnSignupBack_clicked() {
    ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
}

void MainWindow::on_btnDriversSignup_clicked() {
    submittedDriverSignupInfo.NINumber = ui->txtDriversSignupNI->text().toInt();
    submittedDriverSignupInfo.lorryType = ui->txtDriversSignupLorry->text().toStdString();
    submittedDriverSignupInfo.companyCity = ui->txtDriversSignupCompanyCity->text().toStdString();
    submittedDriverSignupInfo.companyAddress = ui->txtDriversSignupCompanyAddress->text().toStdString();

    if (!Login::isValidDriverSignup(getDriverSignupInfo())) {
        setInvalidDriversSignupFeedback();
    } else {
        Login::storeSignupDetails(getSignupInfo());
        Login::storeDriverSignupDetails(getSignupInfo(), getDriverSignupInfo());
        ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
    }
}

void MainWindow::on_btnDriversSignupBack_clicked() {
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnForwarderSignupBack_clicked() {
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnForwarderSignup_clicked() {
    submittedForwarderSignupInfo.companyCity = ui->txtForwarderSignupCompanyCity->text().toStdString();
    submittedForwarderSignupInfo.companyName = ui->txtForwarderSignupCompanyName->text().toStdString();
    submittedForwarderSignupInfo.companyPhone = ui->txtForwarderSignupCompanyTelephone->text().toStdString();
    submittedForwarderSignupInfo.companyAddress = ui->txtForwarderSignupCompanyAddress->text().toStdString();

    if (!Login::isValidForwarderSignup(getForwarderSignupInfo())) {
        setInvalidForwarderSignupFeedback();
    } else {
        Login::storeSignupDetails(getSignupInfo());
        Login::storeForwarderSignupDetails(getSignupInfo(), getForwarderSignupInfo());
        ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
    }
}

void MainWindow::on_btnCourierSignupBack_clicked() {
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnCourierSignup_clicked() {
    submittedCourierSignupInfo.companyCity = ui->txtCourierSignupCompanyCity->text().toStdString();
    submittedCourierSignupInfo.companyName = ui->txtCourierSignupCompanyName->text().toStdString();
    submittedCourierSignupInfo.companyPhone = ui->txtCourierSignupCompanyTelephone->text().toStdString();
    submittedCourierSignupInfo.companyAddress = ui->txtCourierSignupCompanyAddress->text().toStdString();

    if (!Login::isValidCourierSignup(getCourierSignupInfo())) {
        setInvalidCourierSignupFeedback();
    } else {
        Login::storeSignupDetails(getSignupInfo());
        Login::storeCourierSignupDetails(getSignupInfo(), getCourierSignupInfo());
        ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
    }
}

void MainWindow::on_btnCargoOwnerSignupBack_clicked() {
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnCargoOwnerSignup_clicked() {
    submittedCargoOwnerSignupInfo.goodsCategory = ui->txtCargoOwnerSignupCategory->text().toStdString();

    if (!Login::isValidCargoOwnerSignup(getCargoOwnerSignupInfo())) {
        setInvalidCargoOwnerSignupFeedback();
    } else {
        Login::storeSignupDetails(getSignupInfo());
        Login::storeCargoOwnerSignupDetails(getSignupInfo(), getCargoOwnerSignupInfo());
        ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
    }
}
