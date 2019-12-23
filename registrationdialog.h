#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    ~RegistrationDialog();
    void getBase(QSqlDatabase base);
    uint getCurrentNumber();
signals:
    void authorization();
    void registrated();
private slots:
    void on_buttonEnter_clicked();

    void on_buttonRegistration_clicked();

private:
    uint currentNumber;
    QSqlDatabase base;
    Ui::RegistrationDialog *ui;
};

#endif // REGISTRATIONDIALOG_H
