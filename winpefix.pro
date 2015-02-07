# winpefix.pro - WinPEFix
# Copyright (c) 2015 Arkadiusz Bokowy

TEMPLATE = app

TARGET = winpefix
VERSION = 1.0

CONFIG += qt
CONFIG += c++11

QT += core gui
QT += widgets

unix {
	QMAKE_CXXFLAGS += -std=c++11
}

HEADERS += \
	src/MainWindow.h

SOURCES += \
	src/MainWindow.cpp \
	src/main.cpp

FORMS += \
	ui/MainWindow.ui
