#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T21:28:47
#
#-------------------------------------------------

QT       += core gui

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
    Athlete.cpp

HEADERS  += \
    settings.h \
    Athlete.h \
    MainWindow.h \
    ProfileWindow.h \
    RunningProfile.h \
    RunningTime.h \
    RunningEvent.h

FORMS += \
    MainWindow.ui \
    ProfileWindow.ui
