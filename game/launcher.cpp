#include "launcher.h"
#include "ui_launcher.h"

Launcher::Launcher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Launcher)
{
    ui->setupUi(this);
    this->win_connect = 0;
    this->win_server = 0;
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::closeEvent(QCloseEvent *event)
{
    if (this->win_server)
    {
        this->win_server->close();
        delete this->win_server;
    }
    if (this->win_connect)
    {
        this->win_connect->close();
        delete this->win_connect;
    }
    event->accept();
}

void Launcher::on_button_connect_clicked()
{
    if (this->win_connect)
    {
        this->win_connect->close();
        delete this->win_connect;
    }
    this->win_connect = new MainWindow_connect(this);
    this->win_connect->show();
    connect(this->win_connect, SIGNAL(signal_closed()), this, SLOT(close()));
}

void Launcher::on_button_create_clicked()
{
    if (this->win_server)
    {
        this->win_server->close();
        delete this->win_server;
    }

    this->win_server = new MainWindow_server(this);
    this->win_server->show();

    this->on_button_connect_clicked();

    this->win_connect->getLauncher()->connectToServer("127.0.0.1", "SERVER");
}
