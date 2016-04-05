#include "mainwindow_connect.h"
#include "ui_mainwindow_connect.h"

MainWindow_connect::MainWindow_connect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_connect)
{
    ui->setupUi(this);
    launch = new Launcher_connect;

    connect(launch, SIGNAL(connected()), this, SLOT(answerTrue()));
    connect(launch, SIGNAL(disconnected()), this, SLOT(serverTimeout()));
    connect(launch, SIGNAL(nick_incorrect()), this, SLOT(answerFalse()));

    connect(launch, SIGNAL(signal_closed()), this, SLOT(slot_game_close()));

    connect(this, SIGNAL(signal_closed()), launch, SLOT(slot_game_close()));
}

MainWindow_connect::~MainWindow_connect()
{
    delete ui;
}

void MainWindow_connect::on_button_connect_clicked()
{
    launch->connectToServer(ui->line_server_ip->text(), ui->line_nick->text());
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
    launch->startGame();
}

void MainWindow_connect::serverTimeout()
{
    ui->label_status->setText(QString::fromStdString("Server don't response. Please, try again or write other server ip."));
}

void MainWindow_connect::slot_game_close()
{
    //this->close();
}
