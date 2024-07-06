/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QPushButton *pushButton_login;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_5;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_register;
    QPushButton *pushButton_queren_login;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_5;
    QWidget *page_3;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLabel *label_12;
    QLineEdit *lineEdit_8;
    QLabel *label_8;
    QLineEdit *lineEdit_4;
    QLabel *label_9;
    QLineEdit *lineEdit_5;
    QLabel *label_10;
    QLineEdit *lineEdit_6;
    QLabel *label_11;
    QLineEdit *lineEdit_7;
    QPushButton *pushButton_queren;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(522, 320);
        QIcon icon;
        icon.addFile(QString::fromUtf8("image/auto.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(500, 0));
        stackedWidget->setMaximumSize(QSize(500, 300));
        stackedWidget->setStyleSheet(QString::fromUtf8("font: 12pt \"\344\273\277\345\256\213\";\n"
""));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 50, 500, 41));
        label->setMinimumSize(QSize(500, 0));
        label->setMaximumSize(QSize(500, 16777215));
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"04b_21\";\n"
"font: 20pt \"04b_21\";\n"
"color: rgb(0, 0, 0);\n"
"font: 20pt \"\344\273\277\345\256\213\";"));
        label->setAlignment(Qt::AlignCenter);
        pushButton_login = new QPushButton(page);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(160, 150, 171, 61));
        pushButton_login->setStyleSheet(QString::fromUtf8("font: 12pt \"\344\273\277\345\256\213\";\n"
"color: rgb(0, 0, 0);"));
        pushButton_login->setAutoDefault(false);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout_2 = new QHBoxLayout(page_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget_5 = new QWidget(page_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        gridLayout = new QGridLayout(widget_5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(widget_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("font: 12pt \"\344\273\277\345\256\213\";"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        widget = new QWidget(widget_5);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_register = new QPushButton(widget);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setMinimumSize(QSize(0, 40));
        pushButton_register->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);font: 12pt \"\344\273\277\345\256\213\";"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("image/rigester.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_register->setIcon(icon1);

        horizontalLayout_3->addWidget(pushButton_register);

        pushButton_queren_login = new QPushButton(widget);
        pushButton_queren_login->setObjectName(QString::fromUtf8("pushButton_queren_login"));
        pushButton_queren_login->setMinimumSize(QSize(0, 40));
        pushButton_queren_login->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);font: 12pt \"\344\273\277\345\256\213\";"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("image/login.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_queren_login->setIcon(icon2);

        horizontalLayout_3->addWidget(pushButton_queren_login);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 40));
        pushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);font: 12pt \"\344\273\277\345\256\213\";"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("image/out.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon3);

        horizontalLayout_3->addWidget(pushButton);


        gridLayout->addWidget(widget, 7, 1, 1, 1);

        lineEdit_2 = new QLineEdit(widget_5);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 6, 1, 1, 1);

        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(16777215, 76));
        label_3->setStyleSheet(QString::fromUtf8("border-image: url(:/image/cug.png);"));

        gridLayout->addWidget(label_3, 1, 0, 1, 2);

        lineEdit = new QLineEdit(widget_5);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 2, 1, 1, 1);

        label_5 = new QLabel(widget_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 12pt \"\344\273\277\345\256\213\";"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);


        horizontalLayout_2->addWidget(widget_5);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gridLayout_3 = new QGridLayout(page_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_2 = new QLabel(page_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 10pt \"04b_21\";\n"
""));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        lineEdit_3 = new QLineEdit(page_3);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout_3->addWidget(lineEdit_3, 0, 1, 1, 2);

        label_12 = new QLabel(page_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("font: 10pt \"04b_21\";"));

        gridLayout_3->addWidget(label_12, 0, 3, 1, 1);

        lineEdit_8 = new QLineEdit(page_3);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        gridLayout_3->addWidget(lineEdit_8, 0, 5, 1, 1);

        label_8 = new QLabel(page_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("font: 10pt \"04b_21\";"));

        gridLayout_3->addWidget(label_8, 1, 0, 1, 1);

        lineEdit_4 = new QLineEdit(page_3);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout_3->addWidget(lineEdit_4, 1, 2, 1, 1);

        label_9 = new QLabel(page_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("font: 10pt \"04b_21\";"));

        gridLayout_3->addWidget(label_9, 1, 3, 1, 1);

        lineEdit_5 = new QLineEdit(page_3);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        gridLayout_3->addWidget(lineEdit_5, 1, 4, 1, 2);

        label_10 = new QLabel(page_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("font: 10pt \"04b_21\";"));

        gridLayout_3->addWidget(label_10, 2, 0, 1, 2);

        lineEdit_6 = new QLineEdit(page_3);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        gridLayout_3->addWidget(lineEdit_6, 2, 2, 1, 1);

        label_11 = new QLabel(page_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("font: 10pt \"04b_21\";"));

        gridLayout_3->addWidget(label_11, 2, 3, 1, 2);

        lineEdit_7 = new QLineEdit(page_3);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        gridLayout_3->addWidget(lineEdit_7, 2, 5, 1, 1);

        pushButton_queren = new QPushButton(page_3);
        pushButton_queren->setObjectName(QString::fromUtf8("pushButton_queren"));
        pushButton_queren->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"font: 12pt \"04b_21\";"));

        gridLayout_3->addWidget(pushButton_queren, 3, 2, 1, 2);

        stackedWidget->addWidget(page_3);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 522, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\270\211\347\273\264\350\275\250\350\277\271\350\247\204\345\210\222\344\270\216\350\277\220\345\212\250\346\216\247\345\210\266\347\263\273\347\273\237", nullptr));
        pushButton_login->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\347\231\273\351\231\206", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/image/password.png\"/>\345\257\206\347\240\201\357\274\232</p></body></html>", nullptr));
        pushButton_register->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        pushButton_queren_login->setText(QCoreApplication::translate("MainWindow", "\347\241\256\350\256\244", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_3->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Account", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/image/mana.png\"/>\347\224\250\346\210\267\345\220\215\357\274\232</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\255\246\345\217\267", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\247\223\345\220\215", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\346\200\247\345\210\253", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\345\271\264\351\276\204", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\346\211\200\345\234\250\347\263\273", nullptr));
        pushButton_queren->setText(QCoreApplication::translate("MainWindow", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
