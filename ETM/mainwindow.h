#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bcrypt/BCrypt.hpp"
#include "Application/Login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct LoginPage {
    const int LOGIN = 0;
    const int SIGNUP = 1; // Consignee and admin only need this page
    const int SIGNUPDRIVER = 2;
    const int SIGNUPCARGOOWNER = 3;
    const int SIGNUPFORWARDER = 4;
    const int SIGNUPCOURIER = 5;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setInvalidLoginFeedback();
    void setInvalidSignupFeedback();
    void setInvalidDriversSignupFeedback();
    void setInvalidCargoOwnerSignupFeedback();
    void setInvalidForwarderSignupFeedback();
    void setInvalidCourierSignupFeedback();

    LoginInfo getLoginInfo() { return submittedLoginInfo; }
    SignupInfo getSignupInfo() { return submittedSignupInfo; }
    DriverSignupInfo getDriverSignupInfo() { return submittedDriverSignupInfo; }
    CargoOwnerSignupInfo getCargoOwnerSignupInfo() { return submittedCargoOwnerSignupInfo; }
    CourierSignupInfo getCourierSignupInfo() { return submittedCourierSignupInfo; }
    ForwarderSignupInfo getForwarderSignupInfo() { return submittedForwarderSignupInfo; }

private slots:
    void on_btnLoginSignup_clicked();
    void on_btnLogin_clicked();
    void on_btnSignup_clicked();
    void on_btnDriversSignup_clicked();
    void on_btnSignupBack_clicked();
    void on_btnDriversSignupBack_clicked();
    void on_btnForwarderSignupBack_clicked();
    void on_btnForwarderSignup_clicked();
    void on_btnCourierSignupBack_clicked();
    void on_btnCourierSignup_clicked();
    void on_btnCargoOwnerSignupBack_clicked();
    void on_btnCargoOwnerSignup_clicked();

private:
    Ui::MainWindow *ui;
    const LoginPage PAGES;
    LoginInfo submittedLoginInfo;
    SignupInfo submittedSignupInfo;
    DriverSignupInfo submittedDriverSignupInfo;
    CargoOwnerSignupInfo submittedCargoOwnerSignupInfo;
    CourierSignupInfo submittedCourierSignupInfo;
    ForwarderSignupInfo submittedForwarderSignupInfo;
};
#endif // MAINWINDOW_H
