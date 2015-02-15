// MainWindowWin.h
// Copyright (c) 2015 Arkadiusz Bokowy
//
// This file is a part of an WinPEFix.
//
// This projected is licensed under the terms of the MIT license.

#ifndef MAINWINDOWWIN_H
#define MAINWINDOWWIN_H

#include <string>
#include <vector>

#include <windows.h>

#include "resource.h"

using std::wstring;
using std::vector;


#define debug(M, ...) do { TCHAR b[128]; \
		wsprintf(b, TEXT("DEBUG: %s:%d: " M TEXT("\r\n")), __FILE__, __LINE__, ##__VA_ARGS__); \
		OutputDebugString(b); } while(0)


template <class T>
class Dialog {
public:
	static INT_PTR CALLBACK dialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		T *pThis = NULL;

		if (uMsg == WM_INITDIALOG) {
			pThis = (T *)lParam;
			pThis->hDlg = hDlg;
			SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)pThis);
		}
		else
			pThis = (T *)GetWindowLongPtr(hDlg, GWLP_USERDATA);

		if (pThis)
			return pThis->handleMessage(uMsg, wParam, lParam);
		return DefWindowProc(hDlg, uMsg, wParam, lParam);
	}

	Dialog() : hDlg(NULL) { }
	~Dialog() { DestroyWindow(hDlg); }

	BOOL create(LPCTSTR lpTemplateName, HWND hWndParent = NULL) {
		hDlg = CreateDialogParam(GetModuleHandle(NULL), lpTemplateName,
				hWndParent, T::dialogProc, (LPARAM)this);
		return hDlg ? TRUE : FALSE;
	}

	BOOL processMessage(LPMSG lpMsg) {
		return IsDialogMessage(hDlg, lpMsg);
	}

	/* It seems, that there is no other way to place dialog window in the
	 * system default location, than creating temporary invisible window
	 * and then fetching its position. */
	BOOL useDefaultPosition() {

		WNDCLASS wc = { 0 };
		WINDOWPLACEMENT wp = { 0 };

		wc.lpfnWndProc = DefWindowProc;
		wc.lpszClassName = TEXT("defaultPosition");
		wp.length = sizeof(WINDOWPLACEMENT);

		RegisterClass(&wc);
		HWND hWnd = CreateWindow(wc.lpszClassName, NULL, WS_OVERLAPPED,
				CW_USEDEFAULT, CW_USEDEFAULT, 350, 150, NULL, NULL, NULL, NULL);
		GetWindowPlacement(hWnd, &wp);
		DestroyWindow(hWnd);
		UnregisterClass(wc.lpszClassName, NULL);

		return SetWindowPos(hDlg, 0, wp.rcNormalPosition.left, wp.rcNormalPosition.top,
				0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	HICON setIcon(HICON hIcon) {
		return (HICON)SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	}

	BOOL show(INT nCmdShow) {
		return ShowWindow(hDlg, nCmdShow);
	}

	HWND dialog() const { return hDlg; }

protected:
	virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

private:
	HWND hDlg;

};


class MainWindow : public Dialog<MainWindow> {
public:
	MainWindow(LPCTSTR lpTemplateName);

	LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	VOID selectFiles();
	VOID process();
	VOID consoleLog(LPCTSTR message);
	VOID consoleClear();

protected:
	VOID maintainLayout(INT width, INT height);
	VOID enableProcessing(BOOL enabled);

private:
	INT prevWidth, prevHeight;
	vector<wstring> files;

	HWND hWndSelectButon;
	HWND hWndProcessButton;
	HWND hWndEditbox;

};

#endif  // MAINWINDOWWIN_H
