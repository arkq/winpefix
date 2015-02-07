// MainWindowQt.h
// Copyright (c) 2015 Arkadiusz Bokowy
//
// This file is a part of an WinPEFix.
//
// This projected is licensed under the terms of the MIT license.

#ifndef MAINWINDOWQT_H
#define MAINWINDOWQT_H

#include <QApplication>
#include <QMainWindow>
#include <QStringList>


namespace Ui {
	class MainWindow;
}


class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QApplication &app, QWidget *parent = 0);
	~MainWindow();

public slots:
	virtual void selectFiles();
	virtual void process();
	virtual void consoleLog(const QString &message);
	virtual void consoleClear();

protected:
	void enableProcessing(bool enabled);
	bool isOverwriteMode();

private:
	Ui::MainWindow *ui;
	QApplication *app;
	QStringList files;

};

#endif  // MAINWINDOWQT_H
