#ifndef AII_MAINWINDOW_H
#define AII_MAINWINDOW_H

#ifndef APPIMAGE_INSTALL_PATH
#define APPIMAGE_INSTALL_PATH ".local/AppImages"
#endif

#ifndef DESKTOP_INSTALL_PATH
#define DESKTOP_INSTALL_PATH ".local/share/applications"
#endif

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QFileDialog>
#include <QCheckBox>
#include <QMessageBox>

class MainWindow: public QMainWindow {
    Q_OBJECT

    struct {
        QPushButton *start;
        QProgressBar *bar;
    } Process;

    struct {
        QLineEdit *name;
        QPushButton *select;
    } File;

    struct {
        QLineEdit *name;
        QLineEdit *type;

        QCheckBox *terminal;
        QLineEdit *icon;
    } Info;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void install();
};


#endif //AII_MAINWINDOW_H