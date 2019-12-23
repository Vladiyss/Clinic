#ifndef CLINICINFODIALOG_H
#define CLINICINFODIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class ClinicInfoDialog;
}

class ClinicInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClinicInfoDialog(QWidget *parent = nullptr);
    ~ClinicInfoDialog();
    void getDataBase(QSqlDatabase base);
private slots:
    void on_doctorSelect_currentIndexChanged();

private:
    QSqlDatabase base;
    Ui::ClinicInfoDialog *ui;
};

#endif // CLINICINFODIALOG_H
