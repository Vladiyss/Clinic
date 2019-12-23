#-------------------------------------------------
#
# Project created by QtCreator 2019-05-20T11:12:33
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseWork
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        clinicinfodialog.cpp \
        datedialog.cpp \
        editdialog.cpp \
        logindialog.cpp \
        main.cpp \
        mainwindow.cpp \
        passwordeditdialog.cpp \
        registrationdialog.cpp \
        removedialog.cpp \
        useraccount.cpp

HEADERS += \
        clinicinfodialog.h \
        datedialog.h \
        editdialog.h \
        logindialog.h \
        mainwindow.h \
        passwordeditdialog.h \
        registrationdialog.h \
        removedialog.h \
        useraccount.h


FORMS += \
        clinicinfodialog.ui \
        datedialog.ui \
        editdialog.ui \
        logindialog.ui \
        mainwindow.ui \
        passwordeditdialog.ui \
        registrationdialog.ui \
        removedialog.ui
RC_ICONS = medecine.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
