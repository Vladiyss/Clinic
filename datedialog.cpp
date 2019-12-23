#include "datedialog.h"
#include "ui_datedialog.h"

DateDialog::DateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateDialog)
{
    ui->setupUi(this);
    ui->calendarWidget->setMinimumDate(QDate::currentDate());
}

QDate DateDialog::getDate()
{
    return currentDate;
}

DateDialog::~DateDialog()
{
    delete ui;
}

void DateDialog::on_buttonEnter_clicked()
{
    currentDate = ui->calendarWidget->selectedDate();
    if((currentDate.toString("ddd") == "Сб")||(currentDate.toString("ddd") == "Вс"))
    {
        QMessageBox::warning(this,"Ошибка","Вы выбрали выходной! Выберите, пожалуйста, другой день недели.",QMessageBox::Ok);
    }
    else
    {
        emit selected();
        this->close();
    }
}
