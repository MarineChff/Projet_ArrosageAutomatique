#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T11:35:25
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_ArrosageAutomatique
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calendarday.cpp \
    calendar.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    calendarday.h \
    calendar.h \
    controller.h

FORMS    += mainwindow.ui
