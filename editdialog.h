#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <useraccount.h>
#include <QMessageBox>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();
    UserAccount setAccount();
public slots:
    void getAccount(UserAccount current);
    void clear();
    void setNewAccount();
signals:
    void accountGetted();
private:
    UserAccount newUser;
    uint number;
    QString photo;
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
