#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include "logindialog.h"
#include "registrationdialog.h"
#include "useraccount.h"
#include "clinicinfodialog.h"
#include "editdialog.h"
#include "passwordeditdialog.h"
#include "datedialog.h"
#include "removedialog.h"
#include <QFileDialog>
#include <QStandardItem>

#define DriverName "QMYSQL"
#define DatabaseConnectionName "MySQL80"
#define DatabaseName "clinic"
#define DatabasePassword "2438041"
#define DatabaseUseName "root"
#define DatabaseHostName "localhost"
#define Admin_ID 2

class LogInDialog;
class RegistrationDialog;
class ClinicInfoDialog;
class EditDialog;
class PasswordEditDialog;
class DateDialog;
class RemoveDialog;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static int const EXIT_CODE_REBOOT;
signals:
    void registration();
    void authorization();
    void registrated();
    void setPassword();
    void setServices();
    void selected();
    void getted();
    void accountGetted();

private slots:
    void getDate();
    void openAuthorization();
    void openRegistration();
    void setAuthorization();
    void setNewAccount();
    void setNewPassword();
    void slot_setServices();
    void newView();

    void on_buttonClinicInfo_clicked();
    void on_buttonAccount_clicked();
    void on_buttonEdit_clicked();
    void on_buttonPasswordEdit_clicked();
    void on_buttonService_clicked();
    void on_buttonDataSelect_clicked();
    void on_buttonSetTalon_clicked();
    void on_buttonRemoveTalon_clicked();
    void on_buttonExit_clicked();
    void on_buttomChangePhoto_clicked();

    void on_comboBoxSpecialist_currentIndexChanged();
    void on_comboBoxDepartment_currentIndexChanged();

private:
    QString currentPhoto;
    void tableView();
    QStandardItemModel* createmodel(QObject *parent);
    UserAccount currentAccount;
    void createAccount();
    void LoadDataBase();
    QSqlDatabase clinic;
    Ui::MainWindow *ui;
    LogInDialog *mLogInDialog;
    RegistrationDialog *mRegistrationDialog;
    ClinicInfoDialog *mClinicInfoDialog;
    EditDialog *mEditDialog;
    PasswordEditDialog *mPasswordEditDialog;
    DateDialog *mDateDialog;
    RemoveDialog *mRemoveDialog;
};

#endif // MAINWINDOW_H
