#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T21:28:47
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MikeysApplication
TEMPLATE = app


SOURCES +=\
    settings.cpp \
    RunningProfile.cpp \
    RunningEvent.cpp \
    RunningTime.cpp \
    ProfileWindow.cpp \
    MainWindow.cpp \
    Main.cpp \
    Athlete.cpp \
    RunnerDatabase.cpp

HEADERS  += \
    settings.h \
    Athlete.h \
    MainWindow.h \
    ProfileWindow.h \
    RunningProfile.h \
    RunningTime.h \
    RunningEvent.h \
    RunnerDatabase.h

FORMS += \
    MainWindow.ui \
    ProfileWindow.ui
