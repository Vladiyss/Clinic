#include "registrationdialog.h"
#include "ui_registrationdialog.h"

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::getBase(QSqlDatabase base)
{
    this->base = base;
}

void RegistrationDialog::on_buttonEnter_clicked()
{
    emit authorization();
}

uint RegistrationDialog::getCurrentNumber()
{
    return currentNumber;
}

void RegistrationDialog::on_buttonRegistration_clicked()
{
    if(QString(ui->editName->text()).isEmpty()||QString(ui->editSurname->text()).isEmpty()
            ||QString(ui->editPhoneNumber->text()).isEmpty()
            ||QString(ui->editEmail->text()).isEmpty()||QString(ui->editPassword->text()).isEmpty()
            ||QString(ui->editCheckPassword->text()).isEmpty())
    {
        QMessageBox::warning(this,"Ошибка!","Вы не заполнили некоторые поля!",QMessageBox::Ok);
    }

    else
        if(ui->editPassword->text() != ui->editCheckPassword->text())
        {
            QMessageBox::warning(this,"Ошибка!","Пароли не совпадают",QMessageBox::Ok);
        }
        else
        {
            bool indicator = false;
            QSqlQuery mQuery = QSqlQuery(base);
            currentNumber = 1;
            mQuery.exec("SELECT * FROM users");
            while(mQuery.next())
            {
                currentNumber++;
                if(mQuery.value(2).toString() == ui->editEmail->text())
                    indicator = true;
            }
            if(indicator)
                QMessageBox::warning(this,"Ошибка!","Пользователь с таким email уже существует!",QMessageBox::Ok);
            else
            {
                mQuery.clear();
                mQuery.prepare("INSERT INTO patients (id_number,name,surname,phonenumber,email)"
                               " VALUES (?,?,?,?,?)");
                mQuery.addBindValue(currentNumber);
                mQuery.addBindValue(ui->editName->text());
                mQuery.addBindValue(ui->editSurname->text());
                mQuery.addBindValue(ui->editPhoneNumber->text());
                mQuery.addBindValue(ui->editEmail->text());
                mQuery.exec();
                mQuery.prepare("INSERT INTO users (id_users, password, email) VALUES (?,?,?)");
                mQuery.addBindValue(currentNumber);
                mQuery.addBindValue(ui->editPassword->text());
                mQuery.addBindValue(ui->editEmail->text());
                mQuery.exec();
                mQuery.clear();
                ui->editName->clear();
                ui->editEmail->clear();
                ui->editSurname->clear();
                ui->editPassword->clear();
                ui->editPhoneNumber->clear();
                ui->editCheckPassword->clear();
                emit registrated();
                this->close();
            }
        }
}
