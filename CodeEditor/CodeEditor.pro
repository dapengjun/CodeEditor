#-------------------------------------------------
#
# Project created by QtCreator 2015-04-18T11:56:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeEditor
TEMPLATE = app

INCLUDEPATH += $$PWD/common

SOURCES += main.cpp\
        mainwindow.cpp \
    CETextEdit.cpp \
    common/CEFile.cpp

HEADERS  += mainwindow.h \
    CETextEdit.h \
    common/CEFile.h

FORMS    += mainwindow.ui

RESOURCES += \
    myResources.qrc
