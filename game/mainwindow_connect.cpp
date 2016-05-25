#include "mainwindow_connect.h"
#include "ui_mainwindow_connect.h"
#include <QDebug>
#include <QFile>

MainWindow_connect::MainWindow_connect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_connect)
{
    //qDebug() << QString("MainWindow_connect-->> ") + "Created.";
    ui->setupUi(this);
    this->loadServerIp();
}

MainWindow_connect::~MainWindow_connect()
{
    //qDebug() << QString("MainWindow_connect-->> ") + "~MainWindow_connect()";
    delete ui;
}

void MainWindow_connect::game_closed()
{
    //qDebug() << QString("MainWindow_connect-->> ") + "game_closed";
    ui->label_status->setText(QString::fromStdString("Game closed. You can try again."));
    ui->line_nick->setEnabled(true);
    ui->button_connect->setEnabled(true);
}

void MainWindow_connect::loadServerIp()
{
    //qDebug() << QString("MainWindow_connect-->> ") + "loadServerIp()";
    QFile file("RealmList.txt");

    if (!file.exists())
    {
        //qDebug() << QString("MainWindow_connect-->> ") + "loadServerIp()" + "-->> File does not exist.";
        if (file.open(QIODevice::WriteOnly))
        {
            //qDebug() << QString("MainWindow_connect-->> ") + "loadServerIp()" + "-->> File created.";
            file.write("127.0.0.1");
            this->server_ip = "127.0.0.1";
            file.close();
        }
        else
        {
            //qDebug() << QString("MainWindow_connect-->> ") + "loadServerIp()" + "-->> File does not created.";
            this->server_ip = "127.0.0.1";
        }
    }
    else
    {
        //qDebug() << QString("MainWindow_connect-->> ") + "loadServerIp()" + "-->> File exist.";
        if (file.open(QIODevice::ReadOnly))
        {
            //qDebug() << QString("MainWindow_connect-->> ") + "loadServerIp()" + "-->> File opened.";
            this->server_ip = QString(file.readAll());
            file.close();
        }
        else
        {
            //qDebug() << QString("MainWindow_connect-->> ") + "loadServerIp()" + "-->> File did not open.";
            this->server_ip = "127.0.0.1";
        }
    }
    //qDebug() << QString("MainWindow_connect-->> ") + "loadServerIp()" + "-->> Server ip: " + this->server_ip;
}

void MainWindow_connect::on_button_connect_clicked()
{
    //qDebug() << QString("MainWindow_connect-->> ") + "on_button_connect_clicked()";
    ui->label_status->setText(QString::fromStdString("Connecting..."));
    this->player_name = ui->line_nick->text();
    emit signal_button_connect(this->player_name, this->server_ip);
}

void MainWindow_connect::answerFalse()
{
    //qDebug() << QString("MainWindow_connect-->> ") + "answerFalse()";
    ui->label_status->setText(QString::fromStdString("Some errors. Please write other nickname or ip address of server."));
}

void MainWindow_connect::answerTrue()
{
    //qDebug() << QString("MainWindow_connect-->> ") + "answerTrue()";
    ui->label_status->setText(QString::fromStdString("Starting the game..."));
    ui->line_nick->setEnabled(false);
    ui->button_connect->setEnabled(false);
}

void MainWindow_connect::serverTimeout()
{
    //qDebug() << QString("MainWindow_connect-->> ") + "serverTimeout()";
    ui->label_status->setText(QString::fromStdString("Server don't response. Please, try again or write other server ip."));
}

void MainWindow_connect::slot_game_close()
{
    this->close();
}
