#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "server.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void slot_addPlayer(QString name);
    void slot_deletePlayer(QString name);

private:
    Server *serv;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
