#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mLogInDialog(new LogInDialog(this)),
    mRegistrationDialog(new RegistrationDialog(this)),
    mClinicInfoDialog(new ClinicInfoDialog(this)),
    mEditDialog(new EditDialog(this)),
    mPasswordEditDialog(new PasswordEditDialog(this)),
    mDateDialog(new DateDialog(this)),
    mRemoveDialog(new RemoveDialog(this))
{
    ui->setupUi(this);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    connect(mLogInDialog,SIGNAL(registration()),this,SLOT(openRegistration()),Qt::UniqueConnection);
    connect(mRegistrationDialog,SIGNAL(authorization()),this,SLOT(openAuthorization()),Qt::UniqueConnection);
    connect(mRegistrationDialog,SIGNAL(registrated()),this,SLOT(setAuthorization()),Qt::UniqueConnection);
    connect(mEditDialog,SIGNAL(accountGetted()),this,SLOT(setNewAccount()),Qt::UniqueConnection);
    connect(mPasswordEditDialog,SIGNAL(setPassword()),this,SLOT(setNewPassword()),Qt::UniqueConnection);
    connect(this,SIGNAL(setServices()),this,SLOT(slot_setServices()),Qt::UniqueConnection);
    connect(mDateDialog,SIGNAL(selected()),this,SLOT(getDate()),Qt::UniqueConnection);
    connect(mRemoveDialog,SIGNAL(getted()),this,SLOT(newView()),Qt::UniqueConnection);
    LoadDataBase();
    mLogInDialog->getBase(clinic);
    mRegistrationDialog->getBase(clinic);
    this->hide();
    mLogInDialog->exec();
    this->show();
    createAccount();
    if(currentAccount.GetIdNumber() == Admin_ID)
    {
        ui->buttonEdit->setVisible(false);
        ui->buttonEdit->setEnabled(false);
        ui->buttonAccount->setVisible(false);
        ui->buttonAccount->setEnabled(false);
        ui->buttonService->setVisible(false);
        ui->buttonService->setEnabled(false);
        ui->buttonPasswordEdit->setVisible(false);
        ui->buttonPasswordEdit->setEnabled(false);
        ui->buttomChangePhoto->setVisible(false);
        ui->buttomChangePhoto->setEnabled(false);

    }
    tableView();
}

int const MainWindow::EXIT_CODE_REBOOT = -123456789;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setNewAccount()
{
    UserAccount temp = mEditDialog->setAccount();
    currentAccount = temp;
    ui->labelName->setText(currentAccount.GetName() + " " + currentAccount.GetSurname());
    ui->labelEmail->setText(currentAccount.GetEmail());
    ui->labelPhone->setText(currentAccount.GetPhoneNumber());
    currentPhoto = currentAccount.GetPhotoPath();
    QPixmap pixMap(currentPhoto);
    int h = ui->personalPhoto->height();
    int w = ui->personalPhoto->width();
    ui->personalPhoto->setPixmap(pixMap.scaled(w,h,Qt::KeepAspectRatio));
    on_buttonAccount_clicked();
    QSqlQuery query(clinic);
    query.exec("UPDATE patients SET patientsphoto = '" + currentAccount.GetPhotoPath() +
               "',name = '" + currentAccount.GetName() +
               "',surname = '" + currentAccount.GetSurname() +
               "',email = '" + currentAccount.GetEmail() +
               "',phonenumber = '" + currentAccount.GetPhoneNumber() +
               "' WHERE (id_number = '" + QString::number(currentAccount.GetIdNumber())  + "')");
    query.exec("UPDATE users SET email = '" + currentAccount.GetEmail() +
               "' WHERE (id_users = '" + QString::number(currentAccount.GetIdNumber())  + "')");
}

void MainWindow::setAuthorization()
{
    mLogInDialog->setRegAccount(mRegistrationDialog->getCurrentNumber());
}

void MainWindow::openRegistration()
{
    mRegistrationDialog->exec();
}


void MainWindow::openAuthorization()
{
    mRegistrationDialog->close();
}

void MainWindow::createAccount()
{
    UserAccount temp = mLogInDialog->getAccount();
    currentAccount = temp;
    ui->labelName->setText(currentAccount.GetName() + " " + currentAccount.GetSurname());
    ui->labelEmail->setText(currentAccount.GetEmail());
    ui->labelPhone->setText(currentAccount.GetPhoneNumber());
    currentPhoto = currentAccount.GetPhotoPath();
    QPixmap pixMap(currentPhoto);
    int h = ui->personalPhoto->height();
    int w = ui->personalPhoto->width();
    ui->personalPhoto->setPixmap(pixMap.scaled(w,h,Qt::KeepAspectRatio));
    on_buttonAccount_clicked();
}

void MainWindow::LoadDataBase()
{
    clinic = QSqlDatabase::addDatabase(DriverName, DatabaseConnectionName);
    clinic.setDatabaseName(DatabaseName);
    clinic.setPassword(DatabasePassword);
    clinic.setUserName(DatabaseUseName);
    clinic.setHostName(DatabaseHostName);
    if(!clinic.open())
        QMessageBox::warning(this,"Error","Произошла ошибка подключения базы данных!",QMessageBox::Ok);
}

void MainWindow::setNewPassword()
{
    QString currentPassword = mPasswordEditDialog->getNewPassword();
    QSqlQuery query = QSqlQuery(clinic);
    query.exec("UPDATE users SET password = '" + currentPassword + "' WHERE (id_users = '" +
               QString::number(currentAccount.GetIdNumber())  + "')");
}

void MainWindow::on_buttonClinicInfo_clicked()
{
    mClinicInfoDialog->open();
    mClinicInfoDialog->getDataBase(clinic);
}

void MainWindow::on_buttonAccount_clicked()
{
    ui->accountPages->setCurrentIndex(0);
}

void MainWindow::on_buttonEdit_clicked()
{
    mEditDialog->show();
    mEditDialog->getAccount(currentAccount);
}

void MainWindow::on_buttonPasswordEdit_clicked()
{
    mPasswordEditDialog->show();
    QSqlQuery query = QSqlQuery(clinic);
    query.exec("SELECT * FROM users WHERE id_users = '" + QString::number(currentAccount.GetIdNumber()) + "'");
    query.next();
    mPasswordEditDialog->getOldPassword(query.value(1).toString());
}

void MainWindow::slot_setServices()
{
    QSqlQuery query = QSqlQuery(clinic);
    query.exec("SELECT * FROM departments");
    while(query.next())
    {
        ui->comboBoxDepartment->addItem(query.value(1).toString());
    }
}

void MainWindow::on_buttonService_clicked()
{
    ui->accountPages->setCurrentIndex(1);
    emit setServices();
}

void MainWindow::on_comboBoxDepartment_currentIndexChanged()
{
    QString text = ui->comboBoxDepartment->currentText();
    QSqlQuery query = QSqlQuery(clinic);
    query.exec("SELECT * FROM departments WHERE name = '" + text + "'");
    query.next();
    text = query.value(0).toString();
    query.exec("SELECT * FROM doctors WHERE department = '" + text + "'");
    ui->comboBoxSpecialist->clear();
    while(query.next())
    {
        ui->comboBoxSpecialist->addItem(query.value(3).toString());
    }
}

void MainWindow::getDate()
{
    ui->editDateTime->setText(QDate(mDateDialog->getDate()).toString("dd.MM.yyyy"));
}

void MainWindow::on_buttonDataSelect_clicked()
{
    mDateDialog->show();

}

void MainWindow::on_buttonSetTalon_clicked()
{
    QSqlQuery query = QSqlQuery(clinic);
    query.exec("SELECT * FROM services WHERE name = '" + ui->comboBoxService->currentText() + "'");
    query.next();
    QString service = query.value(0).toString();
    query.exec("SELECT * FROM doctors WHERE name = '" + ui->comboBoxSpecialist->currentText() + "'");
    query.next();
    QString specialist = query.value(0).toString();
    if(QString(ui->editDateTime->text()).isEmpty())
        QMessageBox::warning(this,"Ошибка","Вы не выбрали дату приема!",QMessageBox::Ok);
    else
    {
        query.exec("SELECT * FROM talons WHERE date = '" + ui->editDateTime->text() + "' AND time = '" +
                   QTime(ui->editTime->time()).toString("hh:mm") + "' AND doctor = '" + specialist + "'");
        if(query.next())
        {
            QMessageBox::warning(this,"Ошибка","Уже существует запись на это время",QMessageBox::Ok);
            while(query.next());
        }
        else
        {
            query.prepare("INSERT INTO talons (patient,doctor,service,date,time,talon_number)"
                           " VALUES (?,?,?,?,?,?)");
            query.addBindValue(currentAccount.GetIdNumber());
            query.addBindValue(specialist);
            query.addBindValue(service);
            query.addBindValue(ui->editDateTime->text());
            query.addBindValue(QTime(ui->editTime->time()).toString("hh:mm"));
            query.addBindValue(QString::number(qrand()%5000));
            query.exec();
            QMessageBox::information(this,"Успех","Запись создана",QMessageBox::Ok);
        }
        tableView();
    }

}

QStandardItemModel* MainWindow::createmodel(QObject *parent)
{
    QSqlQuery query = QSqlQuery(clinic);
    if(currentAccount.GetIdNumber() != Admin_ID)
        query.exec("SELECT * FROM talons WHERE patient = " + QString::number(currentAccount.GetIdNumber()));
    else
        query.exec("SELECT * FROM talons");
    const int numRows = query.size();
    const int numColumns = 7;
    QStringList Headers = {"Имя/Фамилия","Наименование услуги","Номер талона","Дата","Время","Врач","Кабинет"};
    QStandardItemModel* model = new QStandardItemModel(numRows, numColumns);
    model->setHorizontalHeaderLabels(Headers);
    query.next();
    for (int row = 0; row < numRows; ++row)
    {
        int column = 0;

        QSqlQuery nameQuery = QSqlQuery(clinic);
        nameQuery.exec("SELECT * FROM patients WHERE id_number = " + QString::number(query.value(0).toUInt()));
        nameQuery.next();
        QString text = nameQuery.value(1).toString() + " " + nameQuery.value(2).toString();
        QStandardItem* itemName = new QStandardItem(text);
        model->setItem(row, column, itemName);
        column++;
        QSqlQuery doctorQuery = QSqlQuery(clinic);
        doctorQuery.exec("SELECT * FROM doctors WHERE license_number = '" + query.value(1).toString() + "'");
        doctorQuery.next();
        QSqlQuery serviceQuery = QSqlQuery(clinic);
        serviceQuery.exec("SELECT * FROM services WHERE id_number = '" + query.value(2).toString() + "'");
        serviceQuery.next();
        text = serviceQuery.value(1).toString();
        QStandardItem* itemService = new QStandardItem(text);
        model->setItem(row, column, itemService);
        text = query.value(5).toString();
        column++;
        QStandardItem* itemTalon = new QStandardItem(text);
        model->setItem(row, column, itemTalon);
        column++;
        text = query.value(3).toString();
        QStandardItem* itemDate = new QStandardItem(text);
        model->setItem(row, column, itemDate);
        column++;
        text = query.value(4).toString();
        QStandardItem* itemTime = new QStandardItem(text);
        model->setItem(row, column, itemTime);
        column++;
        text = doctorQuery.value(3).toString();
        QStandardItem* itemDoctor = new QStandardItem(text);
        model->setItem(row, column, itemDoctor);
        column++;
        text = doctorQuery.value(7).toString();
        QStandardItem* itemCabinet = new QStandardItem(text);
        model->setItem(row, column, itemCabinet);
        column++;
        query.next();
    }
    return model;
}

void MainWindow::tableView()
{
    ui->viewTalon->setModel(createmodel(ui->viewTalon));
    ui->viewTalon->setColumnWidth(0,160);
    ui->viewTalon->setColumnWidth(1,200);
    ui->viewTalon->setColumnWidth(2,110);
    ui->viewTalon->setColumnWidth(3,80);
    ui->viewTalon->setColumnWidth(4,60);
    ui->viewTalon->setColumnWidth(5,150);
    ui->viewTalon->setColumnWidth(6,70);
}


void MainWindow::on_buttonRemoveTalon_clicked()
{
    mRemoveDialog->show();
    mRemoveDialog->getInfo(clinic,currentAccount.GetIdNumber());
}

void MainWindow::newView()
{
    tableView();
}

void MainWindow::on_buttonExit_clicked()
{
    qApp->exit( MainWindow::EXIT_CODE_REBOOT );
}

void MainWindow::on_buttomChangePhoto_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this,"Open file",QDir::homePath(),"PNG files (*.png);;All files (*.*)");
    if(FileName != "")
        currentPhoto = FileName;
    QPixmap pixMap(currentPhoto);
    int h = ui->personalPhoto->height();
    int w = ui->personalPhoto->width();
    ui->personalPhoto->setPixmap(pixMap.scaled(w,h,Qt::KeepAspectRatio));
    QSqlQuery query(clinic);
    query.exec("UPDATE patients SET patientsphoto = '" + currentPhoto +
               "' WHERE (id_number = '" + QString::number(currentAccount.GetIdNumber())  + "')");
}

void MainWindow::on_comboBoxSpecialist_currentIndexChanged()
{
    QString text = ui->comboBoxSpecialist->currentText();
    QSqlQuery query = QSqlQuery(clinic);
    query.exec("SELECT * FROM doctors WHERE name = '" + text + "'");
    query.next();
    text = query.value(6).toString();
    QStringList list = text.split(",");
    query.exec("SELECT * FROM services");
    ui->comboBoxService->clear();
    while(query.next())
    {
        for(int i = 0; i < list.size();i++)
        {
            if(query.value(0).toString() == list.at(i))
                ui->comboBoxService->addItem(query.value(1).toString());
        }

    }
}
