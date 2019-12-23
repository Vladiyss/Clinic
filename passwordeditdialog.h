#ifndef PASSWORDEDITDIALOG_H
#define PASSWORDEDITDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class PasswordEditDialog;
}

class PasswordEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordEditDialog(QWidget *parent = nullptr);
    ~PasswordEditDialog();
    void getOldPassword(QString password);
public slots:
    void clear();
    QString getNewPassword();
private slots:
    void checkPassword();
signals:
    void setPassword();
private:

    QString oldPassword;
    Ui::PasswordEditDialog *ui;
};

#endif // PASSWORDEDITDIALOG_H
