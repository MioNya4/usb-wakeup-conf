#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_stateChanged(int arg1);

private slots:

    void on_Refresh_clicked();

    void on_Apply_clicked();

    void on_actionquit_triggered();

    void on_actionenable_all_triggered();

    void on_actiondisable_all_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
