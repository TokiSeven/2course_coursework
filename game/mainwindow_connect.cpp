#include "mainwindow_connect.h"
#include "ui_mainwindow_connect.h"
#include <QDebug>

MainWindow_connect::MainWindow_connect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_connect)
{
    qDebug() << QString("MainWindow_connect-->> ") + "Created.";
    ui->setupUi(this);
}

MainWindow_connect::~MainWindow_connect()
{
    qDebug() << QString("MainWindow_connect-->> ") + "~MainWindow_connect()";
    delete ui;
}

void MainWindow_connect::on_button_connect_clicked()
{
    qDebug() << QString("MainWindow_connect-->> ") + "on_button_connect_clicked()";
    ui->label_status->setText(QString::fromStdString("Connecting..."));
    this->server_ip = ui->line_server_ip->text();
    this->player_name = ui->line_nick->text();
    emit signal_button_connect(this->player_name, this->server_ip);
}

void MainWindow_connect::answerFalse()
{
    qDebug() << QString("MainWindow_connect-->> ") + "answerFalse()";
    ui->label_status->setText(QString::fromStdString("Some errors. Please write other nickname or ip address of server."));
}

void MainWindow_connect::answerTrue()
{
    qDebug() << QString("MainWindow_connect-->> ") + "answerTrue()";
    ui->label_status->setText(QString::fromStdString("Starting the game..."));
    ui->line_nick->setEnabled(false);
    ui->line_server_ip->setEnabled(false);
    ui->button_connect->setEnabled(false);
}

void MainWindow_connect::serverTimeout()
{
    qDebug() << QString("MainWindow_connect-->> ") + "serverTimeout()";
    ui->label_status->setText(QString::fromStdString("Server don't response. Please, try again or write other server ip."));
}

void MainWindow_connect::slot_game_close()
{
    qDebug() << QString("MainWindow_connect-->> ") + "slot_game_close()";
}
