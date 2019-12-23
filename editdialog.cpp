#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(clear()),Qt::UniqueConnection);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(setNewAccount()),Qt::UniqueConnection);
}

void EditDialog::getAccount(UserAccount current)
{
    number = current.GetIdNumber();
    ui->editName->setText(current.GetName());
    ui->editEmail->setText(current.GetEmail());
    ui->editSurname->setText(current.GetSurname());
    ui->editPhoneNumber->setText(current.GetPhoneNumber());
    photo = current.GetPhotoPath();
}

void EditDialog::clear()
{
    ui->editName->clear();
    ui->editEmail->clear();
    ui->editSurname->clear();
    ui->editPhoneNumber->clear();
}

void EditDialog::setNewAccount()
{
    if(QString(ui->editName->text()).isEmpty()||QString(ui->editSurname->text()).isEmpty()
            ||QString(ui->editEmail->text()).isEmpty()
            ||QString(ui->editPhoneNumber->text()).isEmpty())
        QMessageBox::warning(this,"Ошибка!","Некоторые поля не были заполнены!",QMessageBox::Ok);
    else
    {
        UserAccount temp =  UserAccount(ui->editName->text(),ui->editSurname->text(),
                            ui->editEmail->text(),ui->editPhoneNumber->text(),number,photo);
        newUser = temp;
        emit accountGetted();
    }
}

UserAccount EditDialog::setAccount()
{
    return newUser;
}

EditDialog::~EditDialog()
{
    delete ui;
}
