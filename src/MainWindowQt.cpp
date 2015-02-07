// MainWindowQt.cpp
// Copyright (c) 2015 Arkadiusz Bokowy
//
// This file is a part of an WinPEFix.
//
// This projected is licensed under the terms of the MIT license.

#include "QFileDialog"

#include "MainWindowQt.h"
#include "ui_MainWindow.h"


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

	for (auto i = files.begin(); i != files.end(); i++)
		consoleLog("Selected file: " + *i);

}

void MainWindow::process() {
	for (auto i = files.begin(); i != files.end(); i++) {
		consoleLog("Processing file: " + *i);

	}
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
	ui->overwriteCheckBox->setEnabled(enabled);
}
