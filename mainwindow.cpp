#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qdir.h"
#include <fstream>
#include <string>


QListWidgetItem** items;
int dev_size;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    MainWindow::on_Refresh_clicked();
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
    QStringList  devs = get_devices();
    dev_size = devs.size();
    QString siz = QString::number(devs.size());
    items = new QListWidgetItem*[devs.size()];
    for (int i=0; i < dev_size; i++)
    {
        QListWidgetItem *listItem = new QListWidgetItem(devs[i],ui->listWidget);
        items[i] = listItem;
        if (get_dev(devs[i])) {
            listItem->setCheckState(Qt::Checked);
        } else {
            listItem->setCheckState(Qt::Unchecked);
        }
        ui->listWidget->addItem(listItem);
    }

}

void MainWindow::on_Apply_clicked() {
    for (int i=0; i < dev_size; i++) {
        QString item_name = items[i]->text();
        bool checked = items[i]->checkState();
        apply_dev(item_name, checked);
    }
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

