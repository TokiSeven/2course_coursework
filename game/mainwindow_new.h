#ifndef MAINWINDOW_NEW_H
#define MAINWINDOW_NEW_H

#include <QMainWindow>

namespace Ui {
class MainWindow_new;
}

class MainWindow_new : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_new(QWidget *parent = 0);
    ~MainWindow_new();

private:
    Ui::MainWindow_new *ui;
};

#endif // MAINWINDOW_NEW_H
