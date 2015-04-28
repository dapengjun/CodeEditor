#-------------------------------------------------
#
# Project created by QtCreator 2015-04-18T11:56:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CEFile.cpp \
    CETextEdit.cpp

HEADERS  += mainwindow.h \
    CEFile.h \
    CETextEdit.h

FORMS    += mainwindow.ui

RESOURCES += \
    myResources.qrc
