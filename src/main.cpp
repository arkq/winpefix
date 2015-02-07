// main.cpp
// Copyright (c) 2015 Arkadiusz Bokowy
//
// This file is a part of an WinPEFix.
//
// This projected is licensed under the terms of the MIT license.

#ifdef WIN32

#include "MainWindowWin.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MainWindow window(MAKEINTRESOURCE(1));
	window.useDefaultPosition();
	window.show(nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (window.processMessage(&msg))
			continue;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (INT)msg.wParam;
}

#else

#include <QApplication>
#include "MainWindowQt.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	MainWindow window(app);
	window.show();

	return app.exec();
}

#endif
