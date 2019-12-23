#include "clinicinfodialog.h"
#include "ui_clinicinfodialog.h"

ClinicInfoDialog::ClinicInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClinicInfoDialog)
{
    ui->setupUi(this);
    QPixmap pixMap = QPixmap("G:/3 term/C programs/Coursework/CoursWork/БД/Clinic.png");
    int width = ui->clinicPic->width();
    int height = ui->clinicPic->height();
    ui->clinicPic->setPixmap(pixMap.scaled(width,height,Qt::KeepAspectRatio));
    ui->plainEditInfo->setPlainText("Больница Принстон-Плейнсборо – это некоммерческая организация,"
                                    "работающая на благотворительные средства,"
                                    "которая является филиалом медицинского университета,"
                                    "отвечающая за практику студентов-медиков, интернов. \n\n"
                                    "Больница включает в себя несколько отделений, лекционный зал,"
                                    "лаборатории, в которых можно сделать любые анализы."
                                    "А также бесплатную поликлинику, где каждый житель штата Нью-Джерси"
                                    "может получить бесплатное лечение при наличии"
                                    "страховки.");

}

void ClinicInfoDialog::getDataBase(QSqlDatabase base)
{
    this->base = base;
    QSqlQuery query = QSqlQuery(base);
    query.exec("SELECT * FROM doctors");
    while(query.next())
    {
        ui->doctorSelect->addItem(query.value(3).toString() + "(" + query.value(4).toString() + ")");
    }
}

ClinicInfoDialog::~ClinicInfoDialog()
{
    delete ui;
}

void ClinicInfoDialog::on_doctorSelect_currentIndexChanged()
{
    QSqlQuery query = QSqlQuery(base);
    QString text = ui->doctorSelect->currentText();
    text = text.left(text.indexOf("("));
    query.exec("SELECT * FROM doctors WHERE name = '" + text + "'");
    if(query.next())
    {
        QPixmap pixMap(query.value(1).toString());
        int width = ui->doctorPhoto->width();
        int height = ui->doctorPhoto->height();
        ui->doctorPhoto->setPixmap(pixMap.scaled(width,height,Qt::KeepAspectRatio));
        QString text =  query.value(2).toString();
        text.replace("|","\n");
        ui->editDoctorDescription->setPlainText(text);
    }
}
