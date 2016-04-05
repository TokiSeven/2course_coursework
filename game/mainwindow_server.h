#ifndef MAINWINDOW_SERVER_H
#define MAINWINDOW_SERVER_H

#include <QMainWindow>
#include <QDateTime>
#include <QUdpSocket>
#include <QTimer>
#include "server.h"

namespace Ui {
class MainWindow_server;
}

class MainWindow_server : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_server(QWidget *parent = 0);
    ~MainWindow_server();

private:
    Ui::MainWindow_server *ui;
    Server *server;

signals:
    void update_gui();

private slots:
    void update();//update GUI
    void on_button_stop_server_clicked();//stop server
    void on_button_start_server_clicked();//start server
    void on_pushButton_clicked();//clear info
    void server_started();//when server is start
    void server_stopped();//when server is stop
    void server_error();//when server has error
};

#endif // MAINWINDOW_SERVER_H
