// main.cpp
// Copyright (c) 2015 Arkadiusz Bokowy
//
// This file is a part of an WinPEFix.
//
// This projected is licensed under the terms of the MIT license.

#include <QApplication>

#include "MainWindow.h"


int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	MainWindow window(app);
	window.show();

	return app.exec();
}
