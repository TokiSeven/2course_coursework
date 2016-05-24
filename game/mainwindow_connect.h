#ifndef MAINWINDOW_CONNECT_H
#define MAINWINDOW_CONNECT_H

#include <QMainWindow>

namespace Ui {
class MainWindow_connect;
}

class MainWindow_connect : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_connect(QWidget *parent = 0);
    ~MainWindow_connect();

public slots:
    void game_closed();

signals:
    void signal_closed();
    void signal_button_connect(QString nick, QString server);

private:
    void loadServerIp();
    QString player_name;
    QString server_ip;
    Ui::MainWindow_connect *ui;

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
