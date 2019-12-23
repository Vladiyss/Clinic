#include "removedialog.h"
#include "ui_removedialog.h"

RemoveDialog::RemoveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(deleteRecord()),Qt::UniqueConnection);
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(clear()),Qt::UniqueConnection);
}


void RemoveDialog::getInfo(QSqlDatabase base,uint id)
{
    this->base = base;
    this->id = id;
}

void RemoveDialog::clear()
{
    ui->editRemove->clear();
}

void RemoveDialog::deleteRecord()
{
    QString text = ui->editRemove->text();
    if(text.isEmpty())
        QMessageBox::warning(this,"Ошибка","Поле не было заполнено!",QMessageBox::Ok);
    else
    {
        QSqlQuery query = QSqlQuery(base);
        if(id != admin_id)
            query.exec("DELETE FROM talons WHERE talon_number = '" + text + "' AND patient = " + QString::number(id));
        else
            query.exec("DELETE FROM talons WHERE talon_number = '" + text + "'");
        ui->editRemove->clear();
        emit getted();
    }
}

RemoveDialog::~RemoveDialog()
{
    delete ui;
}
