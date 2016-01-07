/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *info_status;
    QTabWidget *tab_login;
    QWidget *login;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *data_name;
    QLineEdit *data_pass;
    QPushButton *button_connect;
    QWidget *registration;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *button_disconnect;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(672, 509);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        info_status = new QLabel(centralWidget);
        info_status->setObjectName(QStringLiteral("info_status"));

        horizontalLayout_4->addWidget(info_status);


        verticalLayout->addLayout(horizontalLayout_4);

        tab_login = new QTabWidget(centralWidget);
        tab_login->setObjectName(QStringLiteral("tab_login"));
        login = new QWidget();
        login->setObjectName(QStringLiteral("login"));
        gridLayout_3 = new QGridLayout(login);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label = new QLabel(login);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);


        gridLayout_3->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_2 = new QLabel(login);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_4->addWidget(label_2);

        label_3 = new QLabel(login);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_4->addWidget(label_3);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        data_name = new QLineEdit(login);
        data_name->setObjectName(QStringLiteral("data_name"));

        verticalLayout_5->addWidget(data_name);

        data_pass = new QLineEdit(login);
        data_pass->setObjectName(QStringLiteral("data_pass"));

        verticalLayout_5->addWidget(data_pass);


        horizontalLayout_6->addLayout(verticalLayout_5);


        gridLayout_3->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        button_connect = new QPushButton(login);
        button_connect->setObjectName(QStringLiteral("button_connect"));

        gridLayout_3->addWidget(button_connect, 2, 0, 1, 1);

        tab_login->addTab(login, QString());
        registration = new QWidget();
        registration->setObjectName(QStringLiteral("registration"));
        tab_login->addTab(registration, QString());

        verticalLayout->addWidget(tab_login);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));

        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_2);

        button_disconnect = new QPushButton(centralWidget);
        button_disconnect->setObjectName(QStringLiteral("button_disconnect"));
        button_disconnect->setEnabled(true);

        verticalLayout->addWidget(button_disconnect);


        horizontalLayout_3->addLayout(verticalLayout);


        horizontalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 672, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tab_login->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_4->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201 \321\201\320\265\321\200\320\262\320\265\321\200\320\260:", 0));
        info_status->setText(QApplication::translate("MainWindow", "\320\235\320\265 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275", 0));
        label->setText(QApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\270\321\200\321\203\320\271\321\202\320\265\321\201\321\214 \320\277\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260:", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\233\320\276\320\263\320\270\320\275:", 0));
        label_3->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\276\320\273\321\214:", 0));
        data_name->setText(QApplication::translate("MainWindow", "account", 0));
        data_pass->setText(QApplication::translate("MainWindow", "password", 0));
        button_connect->setText(QApplication::translate("MainWindow", "\320\222\320\276\320\271\321\202\320\270", 0));
        tab_login->setTabText(tab_login->indexOf(login), QApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", 0));
        tab_login->setTabText(tab_login->indexOf(registration), QApplication::translate("MainWindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", 0));
        button_disconnect->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\271\321\202\320\270 \320\270\320\267 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
