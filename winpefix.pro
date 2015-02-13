# winpefix.pro - WinPEFix
# Copyright (c) 2015 Arkadiusz Bokowy

TEMPLATE = app

TARGET = winpefix
VERSION = 1.0

CONFIG += c++11

HEADERS += \
	src/PELinkFix.h \
	src/mswinpe.h

SOURCES += \
	src/PELinkFix.cpp \
	src/main.cpp

unix {
	QMAKE_CXXFLAGS += -std=c++11

	CONFIG += qt
	QT += core gui
	QT += widgets

	HEADERS += src/MainWindowQt.h
	SOURCES += src/MainWindowQt.cpp
	FORMS += ui/MainWindow.ui
}

win32 {
	DEFINES += WIN32
	LIBS += -lcomdlg32 -lshlwapi

	HEADERS += \
		src/MainWindowWin.h \
		src/resource.h
	SOURCES += src/MainWindowWin.cpp
	RC_FILE = ui/MainWindow.rc
}
