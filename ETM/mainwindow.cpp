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

void MainWindow::setInvalidLoginFeedback(const std::string type) {
    ui->lblLoginIncorrect->setText(QString::fromStdString("Incorrect " + type + "!"));
}

void MainWindow::setInvalidSignupFeedback() {
    ui->lblSignupIncorrect->setText(QString::fromStdString("Please fill all fields!"));
}

void MainWindow::setInvalidDriversSignupFeedback() {
    ui->lblDriversSignupIncorrect->setText(QString::fromStdString("Please fill all fields!"));
}

void MainWindow::on_btnLoginSignup_clicked() {
    ui->swLoginPages->setCurrentIndex(PAGES.SIGNUP);
}

void MainWindow::on_btnLogin_clicked() {
    submittedLoginInfo.username = ui->txtLoginUsername->text().toStdString();
    // Hash password right as it comes through so no plaintext bytes are in memory
    submittedLoginInfo.password = BCrypt::generateHash(ui->txtLoginPassword->text().toStdString());
}

void MainWindow::on_btnSignup_clicked() {
    // TODO: Move all this checking to UserUtils
    // Check passwords do not match
    if (BCrypt::generateHash(ui->txtSignupPassword->text().toStdString())
            != BCrypt::generateHash(ui->txtSignupConfirmPassword->text().toStdString())) {
        ui->lblSignupIncorrect->setText(QString::fromStdString("Passwords do not match!"));
    } else {

    }

    // Check which user type is selected
    if (ui->rbCargoOwner->isChecked()) {
        ui->swLoginPages->setCurrentIndex(PAGES.LOGIN);
    }
    if (ui->rbDriver->isChecked()) {
        ui->swLoginPages->setCurrentIndex(PAGES.SIGNUPDRIVER);
    }
    if (ui->rbTransportationCompany->isChecked()) {
        ui->swLoginPages->setCurrentIndex(PAGES.SIGNUPTCOMPANY);
    }

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

