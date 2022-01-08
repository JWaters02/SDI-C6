#include "mainwindow.h"

#include <QApplication>
#include <pqxx/pqxx>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    try {
        pqxx::connection c("dbname=etm user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
        pqxx::work txn{c};
        pqxx::result r{txn.exec("SELECT first_name, age FROM Users")};
        for (auto row: r) {
            std::cout
                    << row["first_name"].c_str()
                    << "'s age is "
                    << row[1].as<int>()
                    << "."
                    << std::endl;
        }
        txn.commit();
    } catch (pqxx::sql_error const &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        std::cerr << "Query was: " << e.what() << std::endl;
        return 2;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return a.exec();
}
