#-------------------------------------------------
#
# Project created by QtCreator 2018-01-02T11:04:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TodoForPc
TEMPLATE = app

include(qtsingleapplication/src/qtsingleapplication.pri)

VERSION = 1.0.0.2 # major.minor.patch.build
RC_ICONS = todo_list.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    configmanager.cpp \
    datamanager.cpp \
    global.cpp

HEADERS  += widget.h \
    compileconfig.h \
    configmanager.h \
    datamanager.h \
    global.h \
    json.hpp

FORMS    += widget.ui

RESOURCES += \
    res.qrc
