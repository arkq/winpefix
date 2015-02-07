// MainWindowWin.cpp
// Copyright (c) 2015 Arkadiusz Bokowy
//
// This file is a part of an WinPEFix.
//
// This projected is licensed under the terms of the MIT license.

#include <algorithm>

#include <shlwapi.h>
#include <windowsx.h>

#include "MainWindowWin.h"

using std::sort;
using std::unique;


MainWindow::MainWindow(LPCTSTR lpTemplateName) :
		prevWidth(0),
		prevHeight(0) {

	create(lpTemplateName);

	hWndSelectButon = GetDlgItem(dialog(), IDC_SELECT);
	hWndProcessButton = GetDlgItem(dialog(), IDC_PROCESS);
	hWndCheckbox = GetDlgItem(dialog(), IDC_OVERWRITE);
	hWndEditbox = GetDlgItem(dialog(), IDC_TEXT);

	enableProcessing(FALSE);

}

LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_SELECT:
			selectFiles();
			break;
		case IDC_PROCESS:
			process();
			break;
		}
		break;

	case WM_GETMINMAXINFO: {
		MINMAXINFO *mmi = (MINMAXINFO *)lParam;
		LONG base = GetDialogBaseUnits();
		mmi->ptMinTrackSize.x = MulDiv(150, LOWORD(base), 4);
		mmi->ptMinTrackSize.y = MulDiv(75, HIWORD(base), 8);
		break;
	}

	case WM_SIZE:
		if (wParam == SIZE_RESTORED)
			maintainLayout(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CLOSE:
		DestroyWindow(dialog());
		return TRUE;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return 0;
}

VOID MainWindow::selectFiles() {

	OPENFILENAME ofn = { 0 };
	TCHAR szFileName[MAX_PATH] = TEXT("");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = dialog();
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = sizeof(szFileName);
	ofn.Flags = OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_EXPLORER;

	if (!GetOpenFileName(&ofn))
		return;

	vector<wstring> lfiles;

	LPTSTR lpstr = ofn.lpstrFile + lstrlen(ofn.lpstrFile) + 1;
	if (!*lpstr)
		lfiles.push_back(ofn.lpstrFile);
	else
		for (; *lpstr; lpstr += lstrlen(lpstr) + 1) {
			TCHAR file[MAX_PATH];
			lfiles.push_back(PathCombine(file, ofn.lpstrFile, lpstr));
		}

	files.insert(files.end(), lfiles.begin(), lfiles.end());
	sort(files.begin(), files.end());
	files.erase(unique(files.begin(), files.end()), files.end());

	enableProcessing(TRUE);

	TCHAR message[MAX_PATH];
	for (auto i = lfiles.begin(); i != lfiles.end(); i++) {
		wsprintf(message, TEXT("Selected file: %s"), (*i).c_str());
		consoleLog(message);
	}

}

VOID MainWindow::process() {
	TCHAR message[MAX_PATH];
	for (auto i = files.begin(); i != files.end(); i++) {
		wsprintf(message, TEXT("Processing file: %s"), (*i).c_str());
		consoleLog(message);

	}
}

VOID MainWindow::consoleLog(LPCTSTR message) {

	INT length = GetWindowTextLength(hWndEditbox);
	length += lstrlen(message) + 2 + 1;

	TCHAR *logdata = new TCHAR[length];
	GetWindowText(hWndEditbox, logdata, length);

	lstrcat(logdata, message);
	lstrcat(logdata, TEXT("\r\n"));

	SetWindowText(hWndEditbox, logdata);
	SendMessage(hWndEditbox, EM_LINESCROLL, 0, 100);

	delete[] logdata;
}

VOID MainWindow::consoleClear() {
	SetWindowText(hWndEditbox, NULL);
}

/* Maintain window widgets layout during the resize action. Take in mind,
 * that this method is tightly coupled with the dialog template. */
VOID MainWindow::maintainLayout(INT width, INT height) {

	if (prevWidth && prevHeight) {

		RECT rect;
		POINT pt;

		INT dx = width - prevWidth;
		INT dy = height - prevHeight;

		GetWindowRect(hWndSelectButon, &rect);
		pt.x = rect.left; pt.y = rect.top;
		ScreenToClient(dialog(), &pt);
		SetWindowPos(hWndSelectButon, 0, pt.x + dx, pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetWindowRect(hWndProcessButton, &rect);
		pt.x = rect.left; pt.y = rect.top;
		ScreenToClient(dialog(), &pt);
		SetWindowPos(hWndProcessButton, 0, pt.x + dx, pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetWindowRect(hWndCheckbox, &rect);
		pt.x = rect.left; pt.y = rect.top;
		ScreenToClient(dialog(), &pt);
		SetWindowPos(hWndCheckbox, 0, pt.x + dx, pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetWindowRect(hWndEditbox, &rect);
		pt.x = rect.right - rect.left;
		pt.y = rect.bottom - rect.top;
		SetWindowPos(hWndEditbox, 0, 0, 0, pt.x + dx, pt.y + dy, SWP_NOMOVE | SWP_NOZORDER);
	}

	prevWidth = width;
	prevHeight = height;
}

VOID MainWindow::enableProcessing(BOOL enabled) {
	EnableWindow(hWndProcessButton, enabled);
	EnableWindow(hWndCheckbox, enabled);
}

BOOL MainWindow::isOverwriteMode() {
	return SendMessage(hWndCheckbox, BM_GETCHECK, 0, 0) == BST_CHECKED;
}
