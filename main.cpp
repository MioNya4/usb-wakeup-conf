#include "mainwindow.h"


#include <QApplication>
#include <QLabel>
#include <QListWidget>
#include <QDir>
#include <QMessageBox>
#include <iostream>
#include <QDir>
#include <iostream>

bool help, apply, version;
bool config_read();


int main(int argc, char *argv[])
{
    for (int _i=0; _i<argc; _i++) {
        if (!strcmp(argv[_i], "-h") or !strcmp(argv[_i], "--help")) {
            std::cout << "usb_wakeup_tool is a tool for configuring\
 different usb devices like mices or keyboards to be able to wake up the computer or not.\
-h or --help to show this help and exit\n\
-v or --version to show version and exit\n\
-a or --apply to just apply the config and exit";
            return 0;
        } else if (!strcmp(argv[_i], "-v") or !strcmp(argv[_i], "--version")) {
            std::cout << "usb_wakeup_tool v0.2";
            return 0;
        } else if (!strcmp(argv[_i], "-a") or !strcmp(argv[_i], "--apply")) {

            config_read();
            return 0;
        }
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

