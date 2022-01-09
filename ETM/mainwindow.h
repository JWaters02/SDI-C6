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
    const int SIGNUP = 1;
    const int SIGNUPDRIVER = 2;
    const int SIGNUPTCOMPANY = 3;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setInvalidLoginFeedback();
    void setInvalidSignupFeedback();
    void setInvalidDriversSignupFeedback();

    LoginInfo getLoginInfo() { return submittedLoginInfo; }
    SignupInfo getSignupInfo() { return submittedSignupInfo; }
    DriverSignupInfo getDriverSignupInfo() { return submittedDriverSignupInfo; }

private slots:
    void on_btnLoginSignup_clicked();
    void on_btnLogin_clicked();
    void on_btnSignup_clicked();
    void on_btnDriversSignup_clicked();
    void on_btnSignupBack_clicked();
    void on_btnDriversSignupBack_clicked();

private:
    Ui::MainWindow *ui;
    const LoginPage PAGES;
    LoginInfo submittedLoginInfo;
    SignupInfo submittedSignupInfo;
    DriverSignupInfo submittedDriverSignupInfo;
};
#endif // MAINWINDOW_H
