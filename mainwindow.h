#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QsqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <iostream>
#include <QMessageBox>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class User
{
private:
    int num;
    QString uid;
    QString upw;
    QString uname;
    QString phone;
    QChar role;
public:
    User();
    User(int num, QString uid, QString upw, QString uname, QString phone, QChar role);
    void printInfo();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_signin_btn_to_signup_clicked();

    void on_signin_btn_signin_clicked();

    void on_main_btn_signout_clicked();

    void on_main_stack_currentChanged(int arg1);

    void on_signup_btn_back_clicked();

private:
    Ui::MainWindow *ui;
    User login_user;
};

#endif // MAINWINDOW_H
