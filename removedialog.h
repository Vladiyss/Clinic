#ifndef REMOVEDIALOG_H
#define REMOVEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>

#define admin_id 2

namespace Ui {
class RemoveDialog;
}

class RemoveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveDialog(QWidget *parent = nullptr);
    ~RemoveDialog();
    void getInfo(QSqlDatabase base,uint id);
signals:
    void getted();
public slots:
        void deleteRecord();
        void clear();
private:
    uint id;
    QSqlDatabase base;
    Ui::RemoveDialog *ui;
};

#endif // REMOVEDIALOG_H
