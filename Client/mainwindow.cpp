#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    launch = new Launcher;

    connect(launch, SIGNAL(connected()), this, SLOT(answerTrue()));
    connect(launch, SIGNAL(disconnected()), this, SLOT(serverTimeout()));
    connect(launch, SIGNAL(nick_incorrect()), this, SLOT(answerFalse()));

    connect(launch, SIGNAL(signal_closed()), this, SLOT(slot_game_close()));

    connect(this, SIGNAL(signal_closed()), launch, SLOT(slot_game_close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_connect_clicked()
{
    launch->connectToServer(ui->line_server_ip->text(), ui->line_nick->text());
    ui->label_status->setText(QString::fromStdString("Connecting..."));
}

void MainWindow::answerFalse()
{
    ui->label_status->setText(QString::fromStdString("Some errors. Please write other nickname or ip address of server."));
}

void MainWindow::answerTrue()
{
    ui->label_status->setText(QString::fromStdString("Starting the game..."));
    ui->line_nick->setEnabled(false);
    ui->line_server_ip->setEnabled(false);
    ui->button_connect->setEnabled(false);
    launch->startGame();
}

void MainWindow::serverTimeout()
{
    ui->label_status->setText(QString::fromStdString("Server don't response. Please, try again or write other server ip."));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit signal_closed();
    event->accept();
}

void MainWindow::slot_game_close()
{
    //this->close();
}
