#ifndef FORM_H
#define FORM_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QUdpSocket>
#include "player.h"

class Form : public QGLWidget
{
    Q_OBJECT

public:
    Form(QString player_name, QWidget* parent = 0);
    //void getPlayers();//if they are online they do nothing, else they add new player to list

protected:
    //FOR OPENGL
    void initializeGL(); // Метод для инициализирования opengl
    void resizeGL(int nWidth, int nHeight); // Метод вызываемый после каждого изменения размера окна
    void paintGL(); // Метод для вывода изображения на экран
    void geese(float, float, float, float);//рисование квадратика
    //methods
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent *);

private:
    //opengl
    int m_width;
    int m_height;

    //db
    Player *pl;
    QList<Player*> *players;


public slots:
    void readMessage();

};

#endif // FORM_H
