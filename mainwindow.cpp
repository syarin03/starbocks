#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <typeinfo>

User::User(int num, QString uid, QString upw, QString uname, QString phone, QChar role)
    : num(num), uid(uid), upw(upw), uname(uname), phone(phone), role(role) {}

User::User() {}

void User::printInfo()
{
    cout << "num: " << this->num << endl;
    cout << "uid: " << this->uid.toStdString() << endl;
    cout << "upw: " << this->upw.toStdString() << endl;
    cout << "name: " << this->uname.toStdString() << endl;
    cout << "phone: " << this->phone.toStdString() << endl;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("10.10.21.116");
    db.setDatabaseName("starbocks");
    db.setUserName("starbocks_admin");
    db.setPassword("admin1234");
    bool ok = db.open();
    cout << "DB Connect: " << ok << endl << endl;

    ui->main_stack->setCurrentWidget(ui->main_stack_signin);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_signin_btn_to_signup_clicked()
{
    ui->main_stack->setCurrentWidget(ui->main_stack_signup);
}


void MainWindow::on_signin_btn_signin_clicked()
{
    QSqlQuery query;
    QString sql;
    QString input_id = ui->signin_input_id->text();
    QString input_pw = ui->signin_input_pw->text();
    sql = "SELECT * FROM member WHERE uid = '" + input_id + "' and upw = '" + input_pw + "';";
    cout << sql.toStdString() << endl << endl;
    query.exec(sql);
//    while (query.next())
    if (query.size() != 0)
    {
        query.next();
        int num = query.value(0).toInt();
        QString uid = query.value(1).toString();
        QString upw = query.value(2).toString();
        QString uname = query.value(3).toString();
        QString phone = query.value(4).toString();
        QChar role = query.value(5).toChar();
        this->login_user = User(num, uid, upw, uname, phone, role);
        this->login_user.printInfo();
        cout << ">> login" << endl << endl;
        ui->main_stack->setCurrentWidget(ui->main_stack_main);
    }
    else
    {
        QMessageBox::warning(this, "경고", "아이디 또는 비밀번호를 확인해주세요");
    }
}


void MainWindow::on_main_btn_signout_clicked()
{
    login_user.printInfo();
    cout << ">> logout" << endl << endl;
    this->login_user = User();
    ui->main_stack->setCurrentWidget(ui->main_stack_signin);
}


void MainWindow::on_main_stack_currentChanged(int arg1)
{
    ui->signin_input_id->clear();
    ui->signin_input_pw->clear();

    ui->signup_input_id->clear();
    ui->signup_input_pw->clear();
    ui->signup_input_pwck->clear();
    ui->signup_input_name->clear();
    ui->signup_input_phone->clear();
}


void MainWindow::on_signup_btn_back_clicked()
{
    ui->main_stack->setCurrentWidget(ui->main_stack_signin);
}

