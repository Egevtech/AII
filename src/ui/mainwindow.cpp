#include "mainwindow.h"

#include <stdlib.h>
#include <QDir>
#include <QString>

int install_file(QString, QString);

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent) {
    this->Process = {
        .start = new QPushButton("Install", this),
        .bar = new QProgressBar(this),
    };

    this->File = {
        .name = new QLineEdit(this),
        .select = new QPushButton(this),
    };

    this->Info = {
        .name = new QLineEdit(this),
        .type = new QLineEdit(this),
    };

    this->Process.start->setText("Install");
    this->File.select->setText("...");

    this->File.name->setPlaceholderText("Path to .AppImage");
    this->Info.name->setPlaceholderText("Application name");
    this->Info.type->setPlaceholderText("Application type");

    this->File.name->setGeometry(10, 10, 300, 30);
    this->File.select->setGeometry(320, 10, 30, 30);

    this->Info.name->setGeometry( 10, 50, 200, 30);
    this->Info.type->setGeometry( 220, 50, 130, 30);

    this->Process.bar->setGeometry(10, 130, 280, 30);
    this->Process.start->setGeometry(290, 130, 60, 30);

    this->Process.bar->setValue(0);

    connect(this->Process.start, &QPushButton::clicked, this, &MainWindow::install);

    this->setFixedSize(360, 170);
}

void MainWindow::install(void) {
    if (!QFile::exists(this->File.name->text())) {
        QMessageBox::warning(this, "Install error", "Appimage file not found.");
        return;
    }

    if (this->Info.type->text().isEmpty()) {
        QMessageBox::warning(this, "Install error", "Application type is empty");
        return;
    }

    if (this->Info.name->text().isEmpty()) {
        QMessageBox::warning(this, "Install error", "Application name is empty");
        return;
    }

    install_file(this->File.name->text(), QDir::homePath()+"/.local/AppImages/");
}

int install_file(QString target, QString dest) {
    if (!QDir(dest).exists()) 
        if (!QDir(QDir::homePath()).mkdir(dest)) {
            QMessageBox::warning(NULL, "Installation error", "Error opening destination directory");
            return EXIT_FAILURE;
        }

    if (!QFile::copy(target, dest+QFileInfo(target).fileName())) {
        QMessageBox::warning(NULL, "Installations error", "Error occured while copying file");
        return EXIT_FAILURE;
    }

    else qDebug() << "Install... ok";
    return EXIT_SUCCESS;
}