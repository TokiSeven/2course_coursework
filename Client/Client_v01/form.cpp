#include "form.h"

Form::Form(QString player_name, QWidget* parent) : QGLWidget(parent)
{
    this->p_port = 1235;
    this->s_port = 1236;

    pl = new Player(QHostAddress::LocalHost, player_name);

    soc = new QUdpSocket;
    soc->bind(this->p_port);

    m_width = 500;
    m_height = 500;

    connect(soc, SIGNAL(readyRead()), this, SLOT(readMessage()));
}
//----------------------------------
//----------OPENGL-----------(BEGIN)
//----------------------------------
void Form::keyPressEvent(QKeyEvent *key)
{
    float speed = 0.5;
    switch(key->key())
    {
    case Qt::Key_Up:
        pl->setY(pl->getY() - speed);
        break;
    case Qt::Key_Down:
        pl->setY(pl->getY() + speed);
        break;
    case Qt::Key_Left:
        pl->setX(pl->getX() - speed);
        break;
    case Qt::Key_Right:
        pl->setX(pl->getX() + speed);
        break;
    }
    send(1);
    updateGL();
    qDebug() << "x:" << pl->getX() << " | y:" << pl->getY();
}

void Form::mouseMoveEvent(QMouseEvent *me)
{
    qDebug() << "MOUSE X:" << me->x() << " | Y:" << me->y();
    qDebug() << "ANGLE:" << pl->getAngle();

    float x = me->x() - pl->getX();
    float y = me->y() - pl->getY();

    float d = sqrt(x*x + y*y);

    float tmp = y / d;

    if (tmp > 1.) tmp = 1.;
    if (tmp < -1.) tmp = -1.;

    float a = acos(tmp) * 57.2957795131;

    if (x / y < 0) a = 360.0 - a;

    pl->setAngle(a);

    updateGL();
}

void Form::initializeGL()
{
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    glOrtho(-1, m_width-1, m_height-1, -1, 0.0f, 1.0f);
    //    qglClearColor(Qt::white);
}

void Form::resizeGL(int nWidth, int nHeight)
{
    //    glViewport(0, 0, nWidth, nHeight);
}

void Form::paintGL()
{
    //    glClear(GL_COLOR_BUFFER_BIT); // чистим буфер изображения и буфер глубины

    //    geese(pl->getX(), pl->getY(), pl->getWidth(), pl->getHeight()); // Рисуем объект
    //    for (int i = 0; i < players.size(); i++)
    //        geese(players[i]->getX(), players[i]->getY(), players[i]->getWidth(), players[i]->getHeight());
}

void Form::geese(float x, float y, float w, float h)
{
    //    glBegin(GL_POLYGON);
    //    glColor3f(0,0,1);
    //    glVertex2f((x - w)*cos(pl->getAngle()) + (y - h)*sin(pl->getAngle()), (x - w)*sin(pl->getAngle()) - (y - h)*cos(pl->getAngle()));
    //    glVertex2f((x - w)*cos(pl->getAngle()) + (y + h)*sin(pl->getAngle()), (x - w)*sin(pl->getAngle()) - (y + h)*cos(pl->getAngle()));
    //    glVertex2f((x + w)*cos(pl->getAngle()) + (y + h)*sin(pl->getAngle()), (x + w)*sin(pl->getAngle()) - (y + h)*cos(pl->getAngle()));
    //    glVertex2f((x + w)*cos(pl->getAngle()) + (y - h)*sin(pl->getAngle()), (x + w)*sin(pl->getAngle()) - (y - h)*cos(pl->getAngle()));
    //    glEnd();
}
//--------------------------------
//----------OPENGL-----------(END)
//--------------------------------

//-------------------------------------------------------
//----------SEND TO ALL PLAYERS FROM US-----------(BEGIN)
//-------------------------------------------------------
void Form::setServerAddress(const QHostAddress addr)
{
    this->s_address = addr;
}
//-----------------------------------------------------
//----------SEND TO ALL PLAYERS FROM US-----------(END)
//-----------------------------------------------------

//---------------------------------------------
//----------READING DATAGRAMS-----------(BEGIN)
//---------------------------------------------
int Form::searchPlayer(QHostAddress address, QString pl_name)
{
    int j = -1;
    for (int i = 0; i < players.size() && j == -1; i++)
        if (players[i]->getName() == pl_name)
            j = i;
    return j;
}

void Form::readMessage()
{
    QByteArray datagram;
    datagram.resize(soc->pendingDatagramSize());
    QHostAddress *address = new QHostAddress;
    soc->readDatagram(datagram.data(), datagram.size(), address);

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64))
        in >> size;
    else
        return;
    if (in.device()->size() - sizeof(qint64) < size)
        return;

    QString pl_name;
    QString cmd;

    in >> pl_name;
    in >> cmd;

    if (cmd == QString::fromStdString("WHO_IS_HERE") && pl_name == QString::fromStdString("SERVER"))
    {
        send(0);
        return;
    }

    //search id of players, who sent message
    //if he have not in list, they add to this and set id as last
    int j = searchPlayer(*address, pl_name);
    if (j == -1)
    {
        Player *new_pl = new Player(*address, pl_name);
        players.append(new_pl);
        j = players.size() - 1;
    }

    qDebug() << "j:" << j << " | pl_name:" << pl_name << " | cmd:" << cmd;

    //big 'if' for command from player
    if (cmd == "NEW_POSITION")
    {
        float x, y;
        in >> x;
        in >> y;
        players[j]->setX(x);
        players[j]->setY(y);
    }
    else if (cmd == "NEW_ANGLE")
    {
        float angle;
        in >> angle;
        players[j]->setAngle(angle);
    }
    else if (cmd == "NEW_HEALTH")
    {
        int health;
        in >> health;
        players[j]->setHealth(health);
    }
    else if (cmd == "NEW_ARMOR")
    {
        int armor;
        in >> armor;
        players[j]->setArmor(armor);
    }
    //updateGL();
}
//-------------------------------------------
//----------READING DATAGRAMS-----------(END)
//-------------------------------------------
