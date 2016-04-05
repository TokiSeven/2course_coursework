#include "launcher.h"
#include "ui_launcher.h"

Launcher::Launcher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Launcher)
{
    ui->setupUi(this);
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::on_button_connect_clicked()
{
    this->win_connect.show();
}

void Launcher::on_button_create_clicked()
{
    this->win_server.show();
}
