#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainform.h"

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

void MainWindow::setInvalidLoginFeedback() {
    ui->lblLoginIncorrect->setText(QString::fromStdString("Username or password is incorrect!"));
}

void MainWindow::setInvalidSignupFeedback() {
    ui->lblSignupIncorrect->setText(QString::fromStdString("Please fill all fields!"));
}

void MainWindow::setInvalidDriversSignupFeedback() {
    ui->lblDriversSignupIncorrect->setText(QString::fromStdString("Please fill all fields!"));
}

void MainWindow::setInvalidCargoOwnerSignupFeedback() {
    ui->lblCargoOwnerSignupIncorrect->setText(QString::fromStdString("Please fill all fields!"));
}

void MainWindow::setInvalidForwarderSignupFeedback() {
    ui->lblForwarderSignupIncorrect->setText(QString::fromStdString("Please fill all fields!"));
}

void MainWindow::setInvalidCourierSignupFeedback() {
    ui->lblCourierSignupIncorrect->setText(QString::fromStdString("Please fill all fields!"));
}

void MainWindow::on_btnLogin_clicked() {
    submittedLoginInfo.username = ui->txtLoginUsername->text().toStdString();
    // Hash password right as it comes through so no plaintext bytes are in memory
    submittedLoginInfo.password = BCrypt::generateHash(ui->txtLoginPassword->text().toStdString());

    // Check if login info is valid
    if (!Login::validateLogin(getLoginInfo())) {
        setInvalidLoginFeedback();
    } else {
        // Go to the next page
        mainform *w = new mainform;
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
        this->close();
    }
}

void MainWindow::on_btnSignup_clicked() {
    submittedSignupInfo.username = ui->txtSignupUsername->text().toStdString();
    submittedSignupInfo.password = BCrypt::generateHash(ui->txtSignupPassword->text().toStdString());
    submittedSignupInfo.firstName = ui->txtSignupFirstName->text().toStdString();
    submittedSignupInfo.lastName = ui->txtSignupLastName->text().toStdString();
    submittedSignupInfo.email = ui->txtSignupEmail->text().toStdString();
    submittedSignupInfo.phone = ui->txtSignupMobile->text().toStdString();
    submittedSignupInfo.homeAddress = ui->txtSignupHomeAddress->text().toStdString();
    submittedSignupInfo.homeCity = ui->txtSignupHomeCity->text().toStdString();

    // Check passwords do not match
    if ((ui->txtSignupPassword->text().toStdString()) !=
        (ui->txtSignupConfirmPassword->text().toStdString())) {
        ui->lblSignupIncorrect->setText(QString::fromStdString("Passwords do not match!"));
    // Validate signup info is all valid
    } else if (!Login::validateSignup(getSignupInfo())) {
        setInvalidSignupFeedback();
    } else {
        // Check which user type is selected
        if (ui->rbCargoOwner->isChecked()) {
            ui->swLoginPages->setCurrentIndex(PAGES.SIGNUPCARGOOWNER);
        } else if (ui->rbDriver->isChecked()) {
            ui->swLoginPages->setCurrentIndex(PAGES.SIGNUPDRIVER);
        } else if (ui->rbForwarder->isChecked()) {
            ui->swLoginPages->setCurrentIndex(PAGES.SIGNUPFORWARDER);
        } else if (ui->rbCourier->isChecked()) {
            ui->swLoginPages->setCurrentIndex(PAGES.SIGNUPCOURIER);
        } else if (ui->rbAdmin->isChecked()) {
            ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
        } else if (ui->rbConsignee->isChecked()) {
            ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
        } else {
            setInvalidSignupFeedback();
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

    if (!Login::validateDriverSignup(getDriverSignupInfo())) {
        setInvalidDriversSignupFeedback();
    } else {
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

    if (!Login::validateForwarderSignup(getForwarderSignupInfo())) {
        setInvalidForwarderSignupFeedback();
    } else {
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

    if (!Login::validateCourierSignup(getCourierSignupInfo())) {
        setInvalidCourierSignupFeedback();
    } else {
        ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
    }
}

void MainWindow::on_btnCargoOwnerSignupBack_clicked() {
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnCargoOwnerSignup_clicked() {
    submittedCargoOwnerSignupInfo.goodsCategory = ui->txtCargoOwnerSignupCategory->text().toStdString();

    if (!Login::validateCargoOwnerSignup(getCargoOwnerSignupInfo())) {
        setInvalidCargoOwnerSignupFeedback();
    } else {
        ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
    }
}
