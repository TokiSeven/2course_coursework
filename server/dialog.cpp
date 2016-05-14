#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    serv = new Server(this);
    serv->socketListen();

    connect(serv, SIGNAL(signal_newPlayer(QString)), this, SLOT(slot_addPlayer(QString)));
    connect(serv, SIGNAL(signal_deletePlayer(QString)), this, SLOT(slot_deletePlayer(QString)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slot_addPlayer(QString name)
{
    QString str = name;
    ui->listWidget->addItem(str);
}

void Dialog::slot_deletePlayer(QString name)
{
    qDebug() << "DIALOG :: " + name;
    QStringList str;
    for (int i = 0; i < serv->getPlayers().size(); str.append(serv->getPlayers()[i++].getName()));
    ui->listWidget->clear();
    ui->listWidget->addItems(str);
}
