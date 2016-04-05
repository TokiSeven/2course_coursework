#include "mainwindow_new.h"
#include "ui_mainwindow_new.h"

MainWindow_new::MainWindow_new(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_new)
{
    ui->setupUi(this);
}

MainWindow_new::~MainWindow_new()
{
    delete ui;
}
