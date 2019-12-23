#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QString>

class UserAccount
{
    QString name;
    QString surname;
    QString email;
    QString phoneNumber;
    uint idNumber;
    QString photo;

public:
    UserAccount(QString name, QString surname, QString email, QString phoneNumber, uint idNumber,QString photo)
    {
        this->name = name;
        this->surname = surname;
        this->email = email;
        this->phoneNumber = phoneNumber;
        this->idNumber = idNumber;
        if(photo.isEmpty())
            this->photo = "G:/3 term/C programs/Coursework/CoursWork/БД/Unknown.png";
        else
            this->photo = photo;
    }
    UserAccount()
    {
        name = "Неизвестно";
        surname = "Неизвестно";
        email = "-";
        phoneNumber = "-";
        idNumber = 0;
        photo = "G:/3 term/C programs/Coursework/CoursWork/БД/Unknown.png";
    }
    void operator = (UserAccount& account2);
    QString GetName();
    QString GetSurname();
    QString GetEmail();
    QString GetPhoneNumber();
    uint GetIdNumber();
    QString GetPhotoPath();
    void SetName(QString name);
    void SetSurname(QString surname);
    void SetEmail(QString email);
    void SetPhoneNumber(QString phoneNumber);
    void SetIdNumber(uint idNumber);
    void SetPhotoPath(QString photoPath);
};

#endif // USERACCOUNT_H
