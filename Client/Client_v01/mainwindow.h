#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "launcher.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Launcher *launch;

private slots:
    //network
    void answerTrue();
    void answerFalse();
    void serverTimeout();

    //GUI
    void on_button_connect_clicked();
};

#endif // MAINWINDOW_H
