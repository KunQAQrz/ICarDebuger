#-------------------------------------------------
#
# Project created by QtCreator 2019-03-11T22:01:16
#
#-------------------------------------------------

QT       += core gui\
            serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICarDebuger
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_LFLAGS += -no-pie

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    SerialSlots.cpp \
    Serial_Communication.cpp \
    SerialUI.cpp \
    Serial.cpp \
    MultipleInputDialog.cpp \
    Config.cpp \
    BluetoothAT_Window.cpp \
    BluetoothAT_Config.cpp \
    ScanSerialTimer.cpp

HEADERS  += \
    Interface.h \
    Serial_Communication.h \
    SerialUI.h \
    Serial.h \
    MultipleInputDialog.h \
    Config.h \
    BluetoothAT_Window.h \
    BluetoothAT_Config.h \
    ScanSerialTimer.h
