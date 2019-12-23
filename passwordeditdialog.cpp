#include "passwordeditdialog.h"
#include "ui_passwordeditdialog.h"

PasswordEditDialog::PasswordEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordEditDialog)
{
    ui->setupUi(this);
    connect(ui->buttonReject,SIGNAL(clicked()),this,SLOT(clear()),Qt::UniqueConnection);
    connect(ui->buttonOk,SIGNAL(clicked()),this,SLOT(checkPassword()),Qt::UniqueConnection);
}

void PasswordEditDialog::getOldPassword(QString password)
{
    oldPassword = password;
}

QString PasswordEditDialog::getNewPassword()
{
    QString newPas = ui->editNewPassword->text();
    ui->editNewPassword->clear();
    ui->editOldPassword->clear();
    return newPas;
}

void PasswordEditDialog::clear()
{
    ui->editNewPassword->clear();
    ui->editOldPassword->clear();
    this->close();
}

void PasswordEditDialog::checkPassword()
{
    if((QString(ui->editNewPassword->text()).isEmpty())||(QString(ui->editOldPassword->text()).isEmpty()))
        QMessageBox::warning(this,"Ошибка","Некоторые поля не были заполнены!",QMessageBox::Ok);
    else
    {
        if(oldPassword != ui->editOldPassword->text())
            QMessageBox::warning(this,"Ошибка","Неверно введен старый пароль!",QMessageBox::Ok);
        else
        {
            emit setPassword();
            this->close();
        }
    }
}

PasswordEditDialog::~PasswordEditDialog()
{
    delete ui;
}
