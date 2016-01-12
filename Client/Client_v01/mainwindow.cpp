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

void MainWindow::startGame()
{
    gameWindow = new Form(this->login);
    gameWindow->setWindowTitle("GameWindow");
    gameWindow->setGeometry(100,100,500,500); // Смещение и положение окна
    gameWindow->setServerAddress(QHostAddress(this->s_ip));
    gameWindow->show();
}
