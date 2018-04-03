#-------------------------------------------------
#
# Project created by QtCreator 2018-03-30T10:57:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MMU
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        program.cpp \
        mmu.cpp \
        node.cpp

HEADERS  += mainwindow.h \
            program.h \
            mmu.h \
            node.h

FORMS    += mainwindow.ui
