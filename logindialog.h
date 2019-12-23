#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include "useraccount.h"

namespace Ui {
class LogInDialog;
}

class LogInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDialog(QWidget *parent = nullptr);
    ~LogInDialog();
    UserAccount getAccount();
    void setRegAccount(uint number);
private slots:
    void on_buttonEnter_clicked();
    void on_buttonRegistration_clicked();
signals:
    void registration();
    void registrated();
    void enter();
public slots:
    void getBase(QSqlDatabase base);
private:  
    QSqlQuery mQuery;
    QSqlDatabase base;
    Ui::LogInDialog *ui;
};

#endif // LOGINDIALOG_H
