/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *layout_connect;
    QLabel *label_info_ip;
    QLineEdit *line_server_ip;
    QHBoxLayout *layout_auth;
    QLabel *label_info_nick;
    QLineEdit *line_nick;
    QLabel *label_auth;
    QHBoxLayout *layout_info;
    QLabel *label_info_status;
    QLabel *label_status;
    QPushButton *button_connect;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(369, 274);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        layout_connect = new QHBoxLayout();
        layout_connect->setSpacing(6);
        layout_connect->setObjectName(QStringLiteral("layout_connect"));
        label_info_ip = new QLabel(centralWidget);
        label_info_ip->setObjectName(QStringLiteral("label_info_ip"));

        layout_connect->addWidget(label_info_ip);

        line_server_ip = new QLineEdit(centralWidget);
        line_server_ip->setObjectName(QStringLiteral("line_server_ip"));

        layout_connect->addWidget(line_server_ip);


        verticalLayout->addLayout(layout_connect);

        layout_auth = new QHBoxLayout();
        layout_auth->setSpacing(6);
        layout_auth->setObjectName(QStringLiteral("layout_auth"));
        label_info_nick = new QLabel(centralWidget);
        label_info_nick->setObjectName(QStringLiteral("label_info_nick"));

        layout_auth->addWidget(label_info_nick);

        line_nick = new QLineEdit(centralWidget);
        line_nick->setObjectName(QStringLiteral("line_nick"));

        layout_auth->addWidget(line_nick);

        label_auth = new QLabel(centralWidget);
        label_auth->setObjectName(QStringLiteral("label_auth"));

        layout_auth->addWidget(label_auth);


        verticalLayout->addLayout(layout_auth);

        layout_info = new QHBoxLayout();
        layout_info->setSpacing(6);
        layout_info->setObjectName(QStringLiteral("layout_info"));
        label_info_status = new QLabel(centralWidget);
        label_info_status->setObjectName(QStringLiteral("label_info_status"));

        layout_info->addWidget(label_info_status);

        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QStringLiteral("label_status"));

        layout_info->addWidget(label_status);


        verticalLayout->addLayout(layout_info);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        button_connect = new QPushButton(centralWidget);
        button_connect->setObjectName(QStringLiteral("button_connect"));

        gridLayout_2->addWidget(button_connect, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 369, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_info_ip->setText(QApplication::translate("MainWindow", "Please, write ip of the server:", 0));
        line_server_ip->setText(QApplication::translate("MainWindow", "192.168.199.3", 0));
        label_info_nick->setText(QApplication::translate("MainWindow", "Please, write your nickname:", 0));
        label_auth->setText(QString());
        label_info_status->setText(QApplication::translate("MainWindow", "Status of the server:", 0));
        label_status->setText(QApplication::translate("MainWindow", "Please, push the button \"Connect\"", 0));
        button_connect->setText(QApplication::translate("MainWindow", "Connect and play", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
