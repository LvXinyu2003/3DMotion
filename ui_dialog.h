/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labTitle;
    QLabel *labIco;
    QWidget *widgetMenu;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnMenu_Min;
    QPushButton *btnMenu_Max;
    QPushButton *btnMenu_Close;
    QWidget *widgetMain;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widgetRight;
    QGridLayout *gridLayout;
    QPushButton *pushButton_clear;
    QLineEdit *lineEdit_voice;
    QPushButton *pushButton_voice_recog;
    QStackedWidget *stackedWidget;
    QWidget *widgetLeft;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *btn_canshu;
    QToolButton *btn_zidong;
    QToolButton *btn_shoudong;
    QToolButton *btn_staff;
    QPushButton *pushButton_act;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_3D;
    QWidget *widget_status;
    QPushButton *pushButton_generate;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(1256, 793);
        QIcon icon;
        icon.addFile(QString::fromUtf8("image/auto.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog->setWindowIcon(icon);
        Dialog->setStyleSheet(QString::fromUtf8("QWidget#widgetMain{\n"
"border-image: url(:/image/background.png);\n"
"}\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);font: 12pt \"\344\273\277\345\256\213\";"));
        Dialog->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetTitle = new QWidget(Dialog);
        widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
        widgetTitle->setSizePolicy(sizePolicy);
        widgetTitle->setMinimumSize(QSize(0, 50));
        widgetTitle->setMaximumSize(QSize(16777215, 50));
        widgetTitle->setStyleSheet(QString::fromUtf8("\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(234, 237, 255, 255), stop:1 rgba(255, 255, 255, 255));QWidget#widgetTitle>QLabel{\n"
"color:#ABD6FF;\n"
"}\n"
"QLabel#labTitle{\n"
"font:14px;\n"
"}\n"
"QLabel#labInfo{\n"
"font:12px;\n"
"}\n"
"QFrame#line{\n"
"color:#ABD6FF;\n"
"}\n"
"QToolButton::menu-indicator{\n"
"image:None;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widgetTitle);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labTitle = new QLabel(widgetTitle);
        labTitle->setObjectName(QString::fromUtf8("labTitle"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labTitle->sizePolicy().hasHeightForWidth());
        labTitle->setSizePolicy(sizePolicy1);
        labTitle->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font.setPointSize(22);
        font.setBold(false);
        font.setItalic(false);
        labTitle->setFont(font);
        labTitle->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"color: rgb(0, 0, 0);\n"
"border-bottom:3px solid #ffffff;font: 22pt \"\344\273\277\345\256\213\";\n"
"border:2px solid #ffffff;\n"
"border-color: rgb(64, 128, 192);"));
        labTitle->setTextFormat(Qt::AutoText);
        labTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labTitle);

        labIco = new QLabel(widgetTitle);
        labIco->setObjectName(QString::fromUtf8("labIco"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labIco->sizePolicy().hasHeightForWidth());
        labIco->setSizePolicy(sizePolicy2);
        labIco->setMinimumSize(QSize(250, 0));
        labIco->setMaximumSize(QSize(200, 16777215));
        labIco->setLayoutDirection(Qt::LeftToRight);
        labIco->setStyleSheet(QString::fromUtf8("image: url(:/image/logo.png);\n"
"border:2px solid #ffffff;\n"
"border-color: rgb(255, 192, 192);"));
        labIco->setScaledContents(false);
        labIco->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labIco);

        widgetMenu = new QWidget(widgetTitle);
        widgetMenu->setObjectName(QString::fromUtf8("widgetMenu"));
        sizePolicy2.setHeightForWidth(widgetMenu->sizePolicy().hasHeightForWidth());
        widgetMenu->setSizePolicy(sizePolicy2);
        widgetMenu->setStyleSheet(QString::fromUtf8("QToolButton,QPushButton{\n"
"border:0px solid #FF0000;\n"
"}\n"
"QToolButton:hover,QPushButton:hover,QToolButton:pressed,QPushButton:pressed{\n"
"background:#067DB8;\n"
"}"));
        horizontalLayout = new QHBoxLayout(widgetMenu);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnMenu_Min = new QPushButton(widgetMenu);
        btnMenu_Min->setObjectName(QString::fromUtf8("btnMenu_Min"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnMenu_Min->sizePolicy().hasHeightForWidth());
        btnMenu_Min->setSizePolicy(sizePolicy3);
        btnMenu_Min->setMinimumSize(QSize(50, 0));
        btnMenu_Min->setMaximumSize(QSize(50, 16777215));
        btnMenu_Min->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Min->setFocusPolicy(Qt::NoFocus);
        btnMenu_Min->setStyleSheet(QString::fromUtf8("border:2px solid #ffffff;\n"
"border-color: rgb(255, 192, 0);\n"
"color: rgb(57, 255, 80);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("image/title_min.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMenu_Min->setIcon(icon1);
        btnMenu_Min->setFlat(true);

        horizontalLayout->addWidget(btnMenu_Min);

        btnMenu_Max = new QPushButton(widgetMenu);
        btnMenu_Max->setObjectName(QString::fromUtf8("btnMenu_Max"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btnMenu_Max->sizePolicy().hasHeightForWidth());
        btnMenu_Max->setSizePolicy(sizePolicy4);
        btnMenu_Max->setMinimumSize(QSize(50, 0));
        btnMenu_Max->setMaximumSize(QSize(35, 16777215));
        btnMenu_Max->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Max->setFocusPolicy(Qt::NoFocus);
        btnMenu_Max->setStyleSheet(QString::fromUtf8("color: rgb(57, 255, 80);\n"
"border:2px solid #ffffff;\n"
"border-color: rgb(0, 192, 255);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("image/title_max.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMenu_Max->setIcon(icon2);
        btnMenu_Max->setFlat(true);

        horizontalLayout->addWidget(btnMenu_Max);

        btnMenu_Close = new QPushButton(widgetMenu);
        btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
        sizePolicy4.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
        btnMenu_Close->setSizePolicy(sizePolicy4);
        btnMenu_Close->setMinimumSize(QSize(50, 0));
        btnMenu_Close->setMaximumSize(QSize(35, 16777215));
        btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Close->setFocusPolicy(Qt::NoFocus);
        btnMenu_Close->setStyleSheet(QString::fromUtf8("border:2px solid #ffffff;\n"
"border-color: rgb(255, 0, 0);\n"
"color: rgb(57, 255, 80);"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("image/title_close.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMenu_Close->setIcon(icon3);
        btnMenu_Close->setFlat(true);

        horizontalLayout->addWidget(btnMenu_Close);


        horizontalLayout_2->addWidget(widgetMenu);


        verticalLayout->addWidget(widgetTitle);

        widgetMain = new QWidget(Dialog);
        widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
        widgetMain->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(widgetMain);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        widgetRight = new QWidget(widgetMain);
        widgetRight->setObjectName(QString::fromUtf8("widgetRight"));
        widgetRight->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(widgetRight);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_clear = new QPushButton(widgetRight);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setMinimumSize(QSize(0, 50));
        pushButton_clear->setStyleSheet(QString::fromUtf8("color: rgb(0, 0 0);\n"
"font: 9pt \"\344\273\277\345\256\213\";"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("image/clearall.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_clear->setIcon(icon4);

        gridLayout->addWidget(pushButton_clear, 1, 2, 1, 1);

        lineEdit_voice = new QLineEdit(widgetRight);
        lineEdit_voice->setObjectName(QString::fromUtf8("lineEdit_voice"));
        lineEdit_voice->setMinimumSize(QSize(0, 40));
        lineEdit_voice->setStyleSheet(QString::fromUtf8("background-color: rgb(185, 185, 185);"));

        gridLayout->addWidget(lineEdit_voice, 1, 3, 1, 1);

        pushButton_voice_recog = new QPushButton(widgetRight);
        pushButton_voice_recog->setObjectName(QString::fromUtf8("pushButton_voice_recog"));
        pushButton_voice_recog->setMinimumSize(QSize(0, 50));
        pushButton_voice_recog->setStyleSheet(QString::fromUtf8("color: rgb(0, 0 0);\n"
"font: 9pt \"\344\273\277\345\256\213\";"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("image/voice.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_voice_recog->setIcon(icon5);

        gridLayout->addWidget(pushButton_voice_recog, 1, 1, 1, 1);

        stackedWidget = new QStackedWidget(widgetRight);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setMinimumSize(QSize(470, 600));
        stackedWidget->setMaximumSize(QSize(16777215, 16777215));
        stackedWidget->setStyleSheet(QString::fromUtf8("font: 10pt \"\344\273\277\345\256\213\";"));

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        widgetLeft = new QWidget(widgetRight);
        widgetLeft->setObjectName(QString::fromUtf8("widgetLeft"));
        widgetLeft->setMinimumSize(QSize(100, 0));
        widgetLeft->setMaximumSize(QSize(16777215, 16777215));
        widgetLeft->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"font:13px;\n"
"color:#ABD6FF;\n"
"border-style:solid;\n"
"border-width:0px 0px 1px 0px;\n"
"border-color:rgba(171,214,255,30);\n"
"padding:8px;\n"
"}\n"
"QToolButton:hover,QToolButton:presse{\n"
"background:#067DB8;\n"
"}\n"
"QToolButton:checked{\n"
"color:#FFFFFF;\n"
"border-style:solid;\n"
"border-width:0px 4px 0px 0px;\n"
"border-color:#00B7DE;\n"
"padding:8px 4px 8px 8px;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #00326B,stop:1 #00346D);\n"
"}"));
        horizontalLayout_4 = new QHBoxLayout(widgetLeft);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        btn_canshu = new QToolButton(widgetLeft);
        btn_canshu->setObjectName(QString::fromUtf8("btn_canshu"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(btn_canshu->sizePolicy().hasHeightForWidth());
        btn_canshu->setSizePolicy(sizePolicy5);
        btn_canshu->setStyleSheet(QString::fromUtf8("color: rgb(255,255,255);\n"
"font: 12pt \"\344\273\277\345\256\213\";"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("image/para.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_canshu->setIcon(icon6);
        btn_canshu->setIconSize(QSize(50, 50));
        btn_canshu->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_4->addWidget(btn_canshu);

        btn_zidong = new QToolButton(widgetLeft);
        btn_zidong->setObjectName(QString::fromUtf8("btn_zidong"));
        sizePolicy5.setHeightForWidth(btn_zidong->sizePolicy().hasHeightForWidth());
        btn_zidong->setSizePolicy(sizePolicy5);
        btn_zidong->setStyleSheet(QString::fromUtf8("color: rgb(255, 255,255);\n"
"font: 12pt \"\344\273\277\345\256\213\";"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("image/auto.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_zidong->setIcon(icon7);
        btn_zidong->setIconSize(QSize(50, 50));
        btn_zidong->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_4->addWidget(btn_zidong);

        btn_shoudong = new QToolButton(widgetLeft);
        btn_shoudong->setObjectName(QString::fromUtf8("btn_shoudong"));
        sizePolicy5.setHeightForWidth(btn_shoudong->sizePolicy().hasHeightForWidth());
        btn_shoudong->setSizePolicy(sizePolicy5);
        btn_shoudong->setStyleSheet(QString::fromUtf8("color: rgb(255, 255,255);\n"
"font: 12pt \"\344\273\277\345\256\213\";"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("image/manual.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_shoudong->setIcon(icon8);
        btn_shoudong->setIconSize(QSize(50, 50));
        btn_shoudong->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_4->addWidget(btn_shoudong);

        btn_staff = new QToolButton(widgetLeft);
        btn_staff->setObjectName(QString::fromUtf8("btn_staff"));
        sizePolicy5.setHeightForWidth(btn_staff->sizePolicy().hasHeightForWidth());
        btn_staff->setSizePolicy(sizePolicy5);
        btn_staff->setStyleSheet(QString::fromUtf8("color: rgb(255, 255,255);\n"
"font: 12pt \"\344\273\277\345\256\213\";"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("image/staff.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_staff->setIcon(icon9);
        btn_staff->setIconSize(QSize(50, 50));
        btn_staff->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_4->addWidget(btn_staff);


        gridLayout->addWidget(widgetLeft, 1, 0, 1, 1);

        pushButton_act = new QPushButton(widgetRight);
        pushButton_act->setObjectName(QString::fromUtf8("pushButton_act"));
        pushButton_act->setMinimumSize(QSize(0, 60));
        pushButton_act->setStyleSheet(QString::fromUtf8("color: rgb(0, 0 0);\n"
"font: 9pt \"\344\273\277\345\256\213\";"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("image/make.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_act->setIcon(icon10);

        gridLayout->addWidget(pushButton_act, 1, 4, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_3D = new QWidget(widgetRight);
        widget_3D->setObjectName(QString::fromUtf8("widget_3D"));
        widget_3D->setMinimumSize(QSize(600, 500));
        widget_3D->setStyleSheet(QString::fromUtf8("background-color: rgb(27, 27, 27);"));

        verticalLayout_3->addWidget(widget_3D);

        widget_status = new QWidget(widgetRight);
        widget_status->setObjectName(QString::fromUtf8("widget_status"));
        widget_status->setMaximumSize(QSize(16777215, 110));
        widget_status->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);font: 10pt \"\344\273\277\345\256\213\";\n"
"\n"
""));

        verticalLayout_3->addWidget(widget_status);


        gridLayout->addLayout(verticalLayout_3, 0, 1, 1, 4);

        pushButton_generate = new QPushButton(widgetRight);
        pushButton_generate->setObjectName(QString::fromUtf8("pushButton_generate"));

        gridLayout->addWidget(pushButton_generate, 2, 4, 1, 1);


        horizontalLayout_3->addWidget(widgetRight);


        verticalLayout->addWidget(widgetMain);


        retranslateUi(Dialog);

        stackedWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        labTitle->setText(QCoreApplication::translate("Dialog", "\350\277\220\345\212\250\346\216\247\345\210\266\345\231\250\344\270\212\344\275\215\346\234\272", nullptr));
        labIco->setText(QString());
#if QT_CONFIG(tooltip)
        btnMenu_Min->setToolTip(QCoreApplication::translate("Dialog", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        btnMenu_Min->setText(QString());
#if QT_CONFIG(tooltip)
        btnMenu_Max->setToolTip(QCoreApplication::translate("Dialog", "\346\234\200\345\244\247\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        btnMenu_Max->setText(QString());
#if QT_CONFIG(tooltip)
        btnMenu_Close->setToolTip(QCoreApplication::translate("Dialog", "\345\205\263\351\227\255", nullptr));
#endif // QT_CONFIG(tooltip)
        btnMenu_Close->setText(QString());
        pushButton_clear->setText(QCoreApplication::translate("Dialog", "\346\270\205\351\231\244", nullptr));
        pushButton_voice_recog->setText(QCoreApplication::translate("Dialog", "\350\257\255\351\237\263\350\257\206\345\210\253", nullptr));
        btn_canshu->setText(QCoreApplication::translate("Dialog", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        btn_zidong->setText(QCoreApplication::translate("Dialog", "\350\207\252\345\212\250\346\250\241\345\274\217", nullptr));
        btn_shoudong->setText(QCoreApplication::translate("Dialog", "\346\211\213\345\212\250\346\250\241\345\274\217", nullptr));
        btn_staff->setText(QCoreApplication::translate("Dialog", "\345\210\266\344\275\234\344\272\272\345\221\230", nullptr));
        pushButton_act->setText(QCoreApplication::translate("Dialog", "\346\211\247\350\241\214", nullptr));
        pushButton_generate->setText(QCoreApplication::translate("Dialog", "\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
