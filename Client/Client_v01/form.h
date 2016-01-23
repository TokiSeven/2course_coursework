#ifndef FORM_H
#define FORM_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QUdpSocket>
#include "container.h"

class Form : public QGLWidget
{
    Q_OBJECT

public:
    Form(Container *cont, QWidget* parent = 0);

public slots:
    void closeEvent(QCloseEvent *event);
    void slot_game_close();

signals:
    void signal_closed();

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
    Container *cont;
};

#endif // FORM_H
