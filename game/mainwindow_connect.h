#ifndef MAINWINDOW_CONNECT_H
#define MAINWINDOW_CONNECT_H

#include <QMainWindow>
#include "launcher_connect.h"

namespace Ui {
class MainWindow_connect;
}

class MainWindow_connect : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_connect(QWidget *parent = 0);
    ~MainWindow_connect();
    Launcher_connect *getLauncher()const{return this->launch;}

signals:
    void signal_closed();

private:
    Ui::MainWindow_connect *ui;
    Launcher_connect *launch;

private slots:
    //network
    void answerTrue();
    void answerFalse();
    void serverTimeout();
    //void closeEvent(QCloseEvent *);
    void slot_game_close();

    //GUI
    void on_button_connect_clicked();
};

#endif // MAINWINDOW_CONNECT_H
