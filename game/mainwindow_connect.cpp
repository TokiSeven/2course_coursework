#include "mainwindow_connect.h"
#include "ui_mainwindow_connect.h"
#include "api.h"

MainWindow_connect::MainWindow_connect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_connect)
{
    ui->setupUi(this);

    this->api = new API(this);


    connect(api->getGameNetwork(), SIGNAL(connected()), this, SLOT(answerTrue()));
    connect(api->getGameNetwork(), SIGNAL(disconnected()), this, SLOT(serverTimeout()));
    connect(api->getGameNetwork(), SIGNAL(nick_incorrect()), this, SLOT(answerFalse()));
}

MainWindow_connect::~MainWindow_connect()
{
    delete ui;
}

void MainWindow_connect::on_button_connect_clicked()
{
    api->getGameNetwork()->connectToServer(ui->line_server_ip->text(), ui->line_nick->text());
    ui->label_status->setText(QString::fromStdString("Connecting..."));
}

void MainWindow_connect::answerFalse()
{
    ui->label_status->setText(QString::fromStdString("Some errors. Please write other nickname or ip address of server."));
}

void MainWindow_connect::answerTrue()
{
    ui->label_status->setText(QString::fromStdString("Starting the game..."));
    ui->line_nick->setEnabled(false);
    ui->line_server_ip->setEnabled(false);
    ui->button_connect->setEnabled(false);
    api->startGame();
    //this->close();
}

void MainWindow_connect::serverTimeout()
{
    ui->label_status->setText(QString::fromStdString("Server don't response. Please, try again or write other server ip."));
}

void MainWindow_connect::slot_game_close()
{
    //this->close();
}
