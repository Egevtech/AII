#include "mainwindow.h"

#include <stdlib.h>
#include <QDir>
#include <QString>

struct DesktopData {
    QString name;
    QString type;
    QString exec;
};

int install_file(QString, QString);
int create_desktop_file(QString, DesktopData);

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
        .terminal = new QCheckBox("Run in terminal", this),
        .icon = new QLineEdit(this)
    };

    this->setWindowTitle("Install AppImage");

    this->File.select->setEnabled(false);

    this->Process.start->setText("Install");
    this->File.select->setText("...");

    this->File.name->setPlaceholderText("Path to .AppImage");

    this->Info.name->setPlaceholderText("Application name");
    this->Info.type->setPlaceholderText("Application type");
    this->Info.icon->setPlaceholderText("Path to icon");

    this->File.name->setGeometry(10, 10, 300, 30);
    this->File.select->setGeometry(320, 10, 30, 30);

    this->Info.name->setGeometry( 10, 50, 200, 30);
    this->Info.type->setGeometry( 220, 50, 130, 30);
    this->Info.icon->setGeometry( 10, 90, 200, 30);
    this->Info.terminal->setGeometry( 220, 90, 130, 30);

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

    if ( install_file(this->File.name->text(), QDir::homePath()+"/.local/AppImages/") == EXIT_FAILURE ||
         create_desktop_file(QDir::homePath()+"/.local/share/applications/"+this->Info.name->text()+".desktop", {
             .name = this->Info.name->text(),
             .type = this->Info.type->text(),
             .exec = QDir::homePath() + "/.local/AppImages/"+QFileInfo(this->File.name->text()).fileName(),
         } ) == EXIT_FAILURE ) {
            QMessageBox::warning(NULL, "Operation result", "Installation finished with errors");
            return;
         }
}

int install_file(QString target, QString dest) {
    if (!QDir(dest).exists()) 
        if (!QDir(QDir::homePath()).mkdir(dest)) {
            QMessageBox::warning(NULL, "Installation error", "Error opening destination directory");
            return EXIT_FAILURE;
        }

    if (!QFile::copy(target, dest+QFileInfo(target).fileName())) {
        QMessageBox::warning(NULL, "Installations error", "Error occured while copying file\nMaybe, file already exists");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int create_desktop_file(QString path, DesktopData dt) {

    QFile desktop_file(path);
    if (!desktop_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(NULL, "Configuration error", "Cannot create .desktop file");
        return EXIT_FAILURE;
    }

    QTextStream out(&desktop_file);
    out << "[Desktop Entry]\n"
        << "Name=" << dt.name << "\n"
        << "Exec=" << dt.exec << "\n"
        << "Type=" << dt.type << "\n";

    qDebug() << "Desktop file... ok";
    
    return EXIT_SUCCESS;
}
