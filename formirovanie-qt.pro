#-------------------------------------------------
#
# Project created by QtCreator 2013-10-28T14:12:23
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = formirovanie-qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    database.cpp \
    functions.cpp \
    sleepinglist.cpp \
    addbody.cpp \
    editcommand.cpp

HEADERS  += mainwindow.h \
    settings.h \
    database.h \
    functions.h \
    sleepinglist.h \
    addbody.h \
    editcommand.h

FORMS    += mainwindow.ui \
    sleepinglist.ui \
    addbody.ui \
    editcommand.ui

RESOURCES += \
    icons.qrc

OTHER_FILES += \
    sets.ini

DEFINES += _DEBUG

