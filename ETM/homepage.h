#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "Users/UserUtils.h"

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

    void showCorrectPage(EUserTypes userType);

private slots:
    void on_btnCOLogout_clicked();

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
