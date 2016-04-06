#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QDialog>
#include "mainwindow_connect.h"
#include <QCloseEvent>

namespace Ui {
class Launcher;
}

class Launcher : public QDialog
{
    Q_OBJECT

public:
    explicit Launcher(QWidget *parent = 0);
    ~Launcher();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void on_button_connect_clicked();

    void on_button_create_clicked();

private:
    Ui::Launcher *ui;
    MainWindow_connect *win_connect;
};

#endif // LAUNCHER_H
