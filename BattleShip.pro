#-------------------------------------------------
#
# Project created by QtCreator 2010-11-29T22:36:07
#
#-------------------------------------------------

QT       += core gui

TARGET = BattleShip
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp

HEADERS  += \
    mainwindow.h

FORMS    += \
    mainwindow.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xee83b1b6
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
