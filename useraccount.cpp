#include "useraccount.h"

QString UserAccount::GetName()
{
    return name;
}

QString UserAccount::GetSurname()
{
    return surname;
}

QString UserAccount::GetEmail()
{
    return email;
}

QString UserAccount::GetPhoneNumber()
{
    return phoneNumber;
}

QString UserAccount::GetPhotoPath()
{
    return photo;
}

uint UserAccount::GetIdNumber()
{
    return idNumber;
}

void UserAccount::SetName(QString name)
{
    this->name = name;
}

void UserAccount::SetSurname(QString surname)
{
    this->surname = surname;
}

void UserAccount::SetEmail(QString email)
{
    this->email = email;
}

void UserAccount::SetPhoneNumber(QString phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void UserAccount::SetIdNumber(uint idNumber)
{
    this->idNumber = idNumber;
}

void UserAccount::SetPhotoPath(QString photoPath)
{
    this->photo = photoPath;
}

void UserAccount::operator = (UserAccount &account2)
{
    this->SetName(account2.GetName());
    this->SetEmail(account2.GetEmail());
    this->SetSurname(account2.GetSurname());
    this->SetIdNumber(account2.GetIdNumber());
    this->SetPhotoPath(account2.GetPhotoPath());
    this->SetPhoneNumber(account2.GetPhoneNumber());
}

