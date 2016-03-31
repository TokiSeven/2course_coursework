#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new Server();

    connect(this, SIGNAL(update_gui()), this, SLOT(update()));
    connect(server, SIGNAL(started()), this, SLOT(server_started()));
    connect(server, SIGNAL(stoped()), this, SLOT(server_stopped()));
    connect(server, SIGNAL(error()), this, SLOT(server_error()));
    connect(server, SIGNAL(update()), this, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_stop_server_clicked()
{
    server->stop();
}

void MainWindow::on_button_start_server_clicked()
{
    server->start();
}

void MainWindow::update()
{
    ui->list_player->clear();
    if (server->getServerStatus())
    {
        for (int i = 0; i < server->getPlayers().size(); i++)
        {
            QString name = QString::fromStdString("Name: ") + server->getPlayers()[i]->getName();
            QString ip = QString::fromStdString(", Ip: ") + server->getPlayers()[i]->getIp().toString();
            QString port = QString::fromStdString(", Port: ") + QString::number(server->getPlayerPort());
            ui->list_player->addItem(name + ip + port);
        }
    }
    else
    {
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->list_debug->clear();
    emit update_gui();
}

void MainWindow::server_started()
{
    ui->button_start_server->setEnabled(false);
    ui->button_stop_server->setEnabled(true);
    ui->list_debug->addItem("Server is started.");
    emit update_gui();
}

void MainWindow::server_stopped()
{
    ui->button_start_server->setEnabled(true);
    ui->button_stop_server->setEnabled(false);
    ui->list_debug->addItem("Server is stopped.");
    emit update_gui();
}

void MainWindow::server_error()
{
    ui->list_debug->addItem("Some errors in server. Please restart them.");
    emit update_gui();
}
