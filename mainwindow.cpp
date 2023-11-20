#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qdir.h"
#include <fstream>
#include <string>
#include <QApplication>
#include <QLabel>
#include <QListWidget>
#include <QDir>
#include <QMessageBox>
#include <iostream>



QListWidgetItem** items;
QStringList devs;
int dev_size;
void apply_dev(QString name, bool checked);
bool config_read();
QString home = QDir::homePath();
bool not_auto_daemon_switch = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QMainWindow::setGeometry(0,0,240,380);
    MainWindow::on_Refresh_clicked();
    if (! config_read()) {
        QMessageBox::warning(this, "warning",\
                             "Could not read config file at ~/.config/usb_wakeup.conf\n"
                                              " Ok if running first time");
    }
    MainWindow::on_Refresh_clicked();
    MainWindow::on_Apply_clicked();
}


bool if_daemon_running() {
    //todo implement actual check for process of /usr/bin/usb_wakeup_daemon.sh
    return false;
}


//QString get_pretty_name(int vendor, int product) {
//    not implemented | todo
//}

MainWindow::~MainWindow() {
    delete ui;
}

QStringList get_devices() {
    QDir directory("/sys/bus/usb/devices/");
    QStringList dirs = directory.entryList(QStringList() << "*", QDir::Dirs);
    QStringList devs;
    foreach(QString i, dirs) {
        if (i != "." and i != ".." and !(i.contains(":"))) {
            devs.append(i);
        }
    }
    return devs;
}

bool get_dev(QString name) {
    std::ifstream dev;
    QString path ="/sys/bus/usb/devices/" + name + "/power/wakeup";
    dev.open(path.toStdString());
    std::string status; dev >> status;
    dev.close();
    if (status == "enabled") {
        return true;
    } else {
        return false;
    }
}

QString get_dev_ids(QString name) {
    std::ifstream productID;
    std::ifstream vendorID;
    QString prodpath ="/sys/bus/usb/devices/" + name + "/idProduct";
    QString vendpath ="/sys/bus/usb/devices/" + name + "/idVendor";
    productID.open(prodpath.toStdString());
    std::string prod;
    productID >> prod;
    vendorID.open(vendpath.toStdString());
    std::string vend;
    vendorID >> vend;
    QString device =   QString::fromStdString(vend)
                     + ":" + QString::fromStdString(prod)
                     + "  ( " + name + " )";
    return device;
}






void apply_dev(QString name, bool checked) {
    std::ofstream dev;
    QString path ="/sys/bus/usb/devices/" + name + "/power/wakeup";
    dev.open(path.toStdString());
    if (checked) {
        dev << "enabled";
    } else {
        dev << "disabled";
    }
    dev.close();
}

void MainWindow::on_Refresh_clicked() {
    for (int i=0; i<dev_size; i++) {
        delete(items[i]);
    }
    delete(items);
    devs = get_devices();
    dev_size = devs.size();
    QString siz = QString::number(devs.size());
    items = new QListWidgetItem*[devs.size()];
    for (int i=0; i < dev_size; i++)
    {
        QString namei = get_dev_ids(devs[i]);
        QListWidgetItem *listItem = new QListWidgetItem(namei,ui->listWidget);
        items[i] = listItem;
        if (get_dev(devs[i])) {
            listItem->setCheckState(Qt::Checked);
        } else {
            listItem->setCheckState(Qt::Unchecked);
        }
        ui->listWidget->addItem(listItem);
    }
    not_auto_daemon_switch = 0;
    if (if_daemon_running()) {
        ui->checkBox->setCheckState(Qt::Checked);
    } else {
        ui->checkBox->setCheckState(Qt::Unchecked);
    }
    not_auto_daemon_switch = 1;
}

void config_write() {
    std::ofstream conf;
    QString path = home + "/.config/usb_wakeup.conf";
    conf.open(path.toStdString());
    for (int j=0; j<dev_size; j++) {
        std::string devvend = get_dev_ids(devs[j]).mid(0,4).toStdString();
        std::string devprod = get_dev_ids(devs[j]).mid(5,4).toStdString();
        conf << devvend << ":" << devprod;
        if (items[j]->checkState() == Qt::Checked) {
            conf << "1";
        } else {
            conf << "0";
        }
        conf << "\n";
    }
    conf << "\n";
}


void MainWindow::on_Apply_clicked() {
    for (int i=0; i < dev_size; i++) {
        QString item_name = devs[i];
        bool checked = items[i]->checkState();
        apply_dev(item_name, checked);
    }
    config_write();
}

void MainWindow::on_actionquit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionenable_all_triggered()
{
    for (int i=0; i < dev_size; i++) {
        items[i]->setCheckState(Qt::Checked);
    }
}


void MainWindow::on_actiondisable_all_triggered()
{
    for (int i=0; i < dev_size; i++) {
        items[i]->setCheckState(Qt::Unchecked);
    }
}

bool config_read() {
    devs = get_devices();
    dev_size = devs.size();
    std::ifstream conf;
    QString path = home + "/.config/usb_wakeup.conf";
    conf.open(path.toStdString());
    std::string data1;
    while (conf >> data1) {
        //std::cout << "  checking " << data1 << "\n";
        QString data = QString::fromStdString(data1);
        for (int j=0; j < dev_size; j++) {
            QString devvend = get_dev_ids(devs[j]).mid(0,4);
            QString devprod = get_dev_ids(devs[j]).mid(5,4);
            //std::cout << "  with " << devprod.toStdString() << " " << devvend.toStdString() << "\n";
            if (data.mid(5,4)==devprod and data.mid(0,4)==devvend) {
                //std::cout << "applying dev " << data.mid(5,4).toStdString() << " as " << devprod.toStdString() << " with " << data.mid(9,1).toStdString() << " \n";
                if (data.mid(9,1).toStdString() == "0") {
                    apply_dev(devs[j], 0);
                } else {
                    apply_dev(devs[j], 1);
                }
            }
        }
    }
    return 1;
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (not_auto_daemon_switch and arg1 == 2) {
        //checked, todo run daemon
        QMessageBox::warning(this, "warning",\
                             "running/stopping daemon is not implemented yet");
    } else if (not_auto_daemon_switch and arg1 == 0) {
        //unchecked, todo stop daemon
        QMessageBox::warning(this, "warning",\
                             "running/stopping daemon is not implemented yet");
    }
}


