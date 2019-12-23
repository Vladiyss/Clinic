#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QMessageBox>

namespace Ui {
class DateDialog;
}

class DateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DateDialog(QWidget *parent = nullptr);
    ~DateDialog();
public slots:
    QDate getDate();

private slots:
    void on_buttonEnter_clicked();

signals:
    void selected();
private:
    Ui::DateDialog *ui;
    QDate currentDate;
};

#endif // DATEDIALOG_H
