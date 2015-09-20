#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T15:22:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartWay
TEMPLATE = app


SOURCES += main.cpp\
        smartway.cpp \
    celula.cpp \
    busca.cpp

HEADERS  += smartway.h \
    celula.h \
    algoritmos_busca.h \
    busca.h

FORMS    += smartway.ui

RESOURCES += \
    smartway.qrc


QMAKE_CXXFLAGS += -std=c++0x
