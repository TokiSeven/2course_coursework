#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void connectToHost();
    void startGame();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *soc;
    quint16 blockSize;

    quint16 s_port;
    QString s_ip;

    QString login;
    QString password;
    bool Auth;

    QFrame *MainFrame;
    Form *gameWindow;

private slots:
    void onSocConnected();
    void onSocDisconnected();
    void onSocReadyRead();
    void onSocDisplayError(QAbstractSocket::SocketError);
    void on_button_connect_clicked();
    void on_button_disconnect_clicked();
    void on_data_name_textChanged(const QString &arg1);
};

#endif // MAINWINDOW_H
