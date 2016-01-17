#include "form.h"

Form::Form(Container *cont, QWidget* parent) : QGLWidget(parent)
{
    this->cont = cont;

    m_width = 500;
    m_height = 500;
}

//----------------------------------
//----------OPENGL-----------(BEGIN)
//----------------------------------
void Form::keyPressEvent(QKeyEvent *key)
{
    Player *pl = cont->getPlayer_current();
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
    updateGL();
}

void Form::mouseMoveEvent(QMouseEvent *me)
{
    Player *pl = cont->getPlayer_current();
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
{/*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, m_width-1, m_height-1, -1, 0.0f, 1.0f);
    qglClearColor(Qt::white);*/
}

void Form::resizeGL(int nWidth, int nHeight)
{/*
    glViewport(0, 0, nWidth, nHeight);*/
}

void Form::paintGL()
{/*
    Player *pl = cont->getPlayer_current();
    QList<Player*> players = cont->getPlayer_all();
    glClear(GL_COLOR_BUFFER_BIT); // чистим буфер изображения и буфер глубины

    geese(pl->getX(), pl->getY(), pl->getWidth(), pl->getHeight()); // Рисуем объект
    for (int i = 0; i < players.size(); i++)
        geese(players[i]->getX(), players[i]->getY(), players[i]->getWidth(), players[i]->getHeight());*/
}

void Form::geese(float x, float y, float w, float h)
{/*
    Player *pl = cont->getPlayer_current();
    glBegin(GL_POLYGON);
    glColor3f(0,0,1);
    glVertex2f((x - w)*cos(pl->getAngle()) + (y - h)*sin(pl->getAngle()), (x - w)*sin(pl->getAngle()) - (y - h)*cos(pl->getAngle()));
    glVertex2f((x - w)*cos(pl->getAngle()) + (y + h)*sin(pl->getAngle()), (x - w)*sin(pl->getAngle()) - (y + h)*cos(pl->getAngle()));
    glVertex2f((x + w)*cos(pl->getAngle()) + (y + h)*sin(pl->getAngle()), (x + w)*sin(pl->getAngle()) - (y + h)*cos(pl->getAngle()));
    glVertex2f((x + w)*cos(pl->getAngle()) + (y - h)*sin(pl->getAngle()), (x + w)*sin(pl->getAngle()) - (y - h)*cos(pl->getAngle()));
    glEnd();*/
}
//--------------------------------
//----------OPENGL-----------(END)
//--------------------------------
