#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T23:41:02
#
#-------------------------------------------------

QT       += core gui
QT       += webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EyesOn
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CameraThreadClass.cpp

HEADERS  += mainwindow.h \
    CameraThreadClass.h \
    SettingsClass.h

FORMS    += mainwindow.ui
