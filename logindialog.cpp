#include "logindialog.h"
#include "ui_logindialog.h"

LogInDialog::LogInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDialog)
{
    ui->setupUi(this);
}

LogInDialog::~LogInDialog()
{
    delete ui;
}

void LogInDialog::getBase(QSqlDatabase base)
{
    this->base = base;
}

UserAccount LogInDialog::getAccount()
{
    uint idNumber = mQuery.value(0).toUInt();
    mQuery.exec("SELECT * FROM patients WHERE id_number = '" + QString::number(idNumber) + "'");
    mQuery.next();
    return UserAccount(mQuery.value(1).toString(),mQuery.value(2).toString(),
                       mQuery.value(4).toString(),mQuery.value(3).toString(),
                       mQuery.value(0).toUInt(),mQuery.value(5).toString());
}

void LogInDialog::setRegAccount(uint number)
{
    mQuery = QSqlQuery(base);
    mQuery.exec("SELECT * FROM users WHERE id_users = " + QString::number(number));
    mQuery.next();
    ui->editNickname->setText(mQuery.value(2).toString());
    ui->editPassword->setText(mQuery.value(1).toString());
}

void LogInDialog::on_buttonEnter_clicked()
{
    mQuery = QSqlQuery(base);
    mQuery.exec("SELECT * FROM users WHERE email = '" + ui->editNickname->text() +
                "' AND password = '" + ui->editPassword->text() +"'");
    if(!mQuery.next())
    {
        QMessageBox::warning(this,"Ошибка","Неверно введен логин/пароль!",QMessageBox::Ok);
    }
    else
    {
        ui->editNickname->clear();
        ui->editPassword->clear();
        this->close();
    }
}

void LogInDialog::on_buttonRegistration_clicked()
{
    emit registration();

}
