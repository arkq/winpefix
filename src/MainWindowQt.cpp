// MainWindowQt.cpp
// Copyright (c) 2015 Arkadiusz Bokowy
//
// This file is a part of an WinPEFix.
//
// This projected is licensed under the terms of the MIT license.

#include "MainWindowQt.h"
#include "ui_MainWindow.h"

#include <QFileDialog>


MainWindow::MainWindow(QApplication &app, QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow),
		app(&app) {

	ui->setupUi(this);
	enableProcessing(false);

	connect(ui->selectPushButton, SIGNAL(clicked()), this, SLOT(selectFiles()));
	connect(ui->processPushButton, SIGNAL(clicked()), this, SLOT(process()));

}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::selectFiles() {

	QStringList files = QFileDialog::getOpenFileNames(this, ui->selectPushButton->text());
	if (files.isEmpty())
		return;

	this->files.append(files);
	this->files.removeDuplicates();

	enableProcessing(true);

	consoleLog("Selected files:");
	for (auto i = files.begin(); i != files.end(); i++)
		consoleLog("  - " + *i);

}

void MainWindow::process() {

	consoleLog("Processing...");
	for (auto i = files.begin(); i != files.end(); i++) {
		consoleLog("  - " + *i);

	}

	files.clear();
	enableProcessing(false);
	consoleLog("Done.");

}

void MainWindow::consoleLog(const QString &message) {
	QString log = message.trimmed();
	if (!log.isEmpty())
		ui->plainTextEdit->appendPlainText(log);
}

void MainWindow::consoleClear() {
	ui->plainTextEdit->clear();
}

void MainWindow::enableProcessing(bool enabled) {
	ui->processPushButton->setEnabled(enabled);
}
