#include "mainwindow.h"
#include "database.h"
#include <QApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    qDebug() << QSqlDatabase::drivers();
    cout << "test" << endl;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("10.10.21.116");
    db.setDatabaseName("starbocks");
    db.setUserName("starbocks_admin");
    db.setPassword("admin1234");
    bool ok = db.open();
    cout << ok << endl;
    QSqlQuery query;
    QString sql;
    sql = "SELECT * FROM member";
    query.exec(sql);
    while (query.next())
    {
        int num = query.value(0).toInt();
        cout << num << endl;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
