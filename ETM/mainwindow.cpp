#include "mainwindow.h"
#include "./ui_mainwindow.h"

LoginInfo submittedLoginInfo;
SignupInfo submittedSignupInfo;
DriverSignupInfo submittedDriverSignupInfo;

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
    }

}

void MainWindow::on_btnSignup_clicked() {
    submittedSignupInfo.username = ui->txtSignupUsername->text().toStdString();
    submittedSignupInfo.password = BCrypt::generateHash(ui->txtSignupPassword->text().toStdString());
    submittedSignupInfo.firstName = ui->txtSignupFirstName->text().toStdString();
    submittedSignupInfo.lastName = ui->txtSignupLastName->text().toStdString();
    submittedSignupInfo.email = ui->txtSignupEmail->text().toStdString();
    submittedSignupInfo.phone = ui->txtSignupMobile->text().toStdString();
    submittedSignupInfo.home_address = ui->txtSignupHomeAddress->text().toStdString();
    submittedSignupInfo.home_city = ui->txtSignupHomeCity->text().toStdString();
    submittedSignupInfo.business_address = ui->txtSignupBusinessAddress->text().toStdString();
    submittedSignupInfo.business_city = ui->txtSignupBusinessCity->text().toStdString();
    submittedSignupInfo.country = ui->txtSignupCountry->text().toStdString();

    // Check passwords do not match
    if ((ui->txtSignupPassword->text().toStdString()) !=
        (ui->txtSignupConfirmPassword->text().toStdString())) {
        ui->lblSignupIncorrect->setText(QString::fromStdString("Passwords do not match!"));
    } else if (!Login::validateSignup(getSignupInfo())) {
        setInvalidSignupFeedback();
    } else {
        // Check which user type is selected
        if (ui->rbCargoOwner->isChecked()) {
            ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
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
        }
        else {
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
    ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
}

void MainWindow::on_btnDriversSignupBack_clicked() {
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnForwarderSignupBack_clicked()
{
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnForwarderSignup_clicked()
{
    ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
}

void MainWindow::on_btnCourierSignupBack_clicked()
{
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnCourierSignup_clicked()
{
    ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
}
