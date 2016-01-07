#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    soc = new QTcpSocket;
    connect(soc, SIGNAL(readyRead()), this, SLOT(onSocReadyRead()));
    connect(soc, SIGNAL(connected()), this, SLOT(onSocConnected()));
    connect(soc, SIGNAL(disconnected()), this, SLOT(onSocDisconnected()));
    connect(soc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocDisplayError(QAbstractSocket::SocketError)));

    s_port = (quint16)1234;
    s_ip = "192.168.199.3";//"25.107.188.21";//hamachi
    //s_ip = "95.84.146.28";//my real ip

    blockSize = 0;

    connectToHost();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToHost()
{
    soc->connectToHost(s_ip, s_port);
    ui->info_status->setText("Connecting...");
}

void MainWindow::startGame()
{
    gameWindow = new Form(this->login);
    gameWindow->setWindowTitle("GameWindow");
    gameWindow->setGeometry(100,100,500,500); // Смещение и положение окна
    gameWindow->setServerAddress(QHostAddress(this->s_ip));
    gameWindow->show();
}

void MainWindow::on_button_connect_clicked()
{
    if (!soc->isOpen())
        connectToHost();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << QString::fromUtf8("AUTH") << ui->data_name->text() << ui->data_pass->text();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    soc->write(block);

    ui->info_status->setText("Waiting answer from server...");
}

void MainWindow::onSocConnected()
{
    ui->info_status->setText("Online");
}

void MainWindow::onSocReadyRead()
{
    QDataStream in(soc);
    if (!blockSize)
    {
        if (soc->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }
    if (soc->bytesAvailable() < blockSize)
        return;
    else
        blockSize = 0;

    QString command;
    in >> command;

    if (command == "ANSWER")
    {
        QString info;
        in >> info;

        if (info == "YES")
        {
            ui->info_status->setText("Log in!");
            ui->data_name->setEnabled(false);
            ui->data_pass->setEnabled(false);
            ui->button_connect->setEnabled(false);
            startGame();
        }
        if (info == "NO")
            ui->info_status->setText("Log out!");
    }
}

void MainWindow::onSocDisconnected()
{
    ui->info_status->setText("Disconnected.");
    ui->button_connect->setEnabled(true);
    ui->data_name->setEnabled(true);
    ui->data_pass->setEnabled(true);
}

void MainWindow::onSocDisplayError(QAbstractSocket::SocketError)
{
    ui->info_status->setText("Error.");
}

void MainWindow::on_button_disconnect_clicked()
{
    soc->disconnectFromHost();
    delete soc;
    if (gameWindow->isWindow())
        delete gameWindow;
    MainWindow::close();
}

void MainWindow::on_data_name_textChanged(const QString &arg1)
{
    this->login = arg1;
}
