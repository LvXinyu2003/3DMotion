#include "dialog.h"
#include "LogHandler.h"
#include <QApplication>
#include <QDebug>
#include <QTime>
#include <QPushButton>
#include"mainwindow.h"
#include "chatclient.h"

int main(int argc, char *argv[])
{
    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();

    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();

#if (QT_VERSION >= QT_VERSION_CHECK(5,9,0))//适应高pdi
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);


    // 添加字体文件,图标
    int fontId = QFontDatabase::addApplicationFont(":/fontawesome-webfont.ttf");
    qDebug()<<fontId;
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    QFile styleFile(":/qss/mystyle.qss");
    if(styleFile.open(QIODevice::ReadOnly))
    {
        QString setStyleSheet(styleFile.readAll());
        a.setStyleSheet(setStyleSheet);
        styleFile.close();
    }
    // [[1]] 安装消息处理函数
    LogHandler::Get().installMessageHandler();

    // [[2]] 输出测试，查看是否写入到文件
    qDebug() << "Hello";
    qDebug() << "当前时间是: " << QTime::currentTime().toString("hh:mm:ss");
    qInfo() << QString("God bless you!");

    // [[3]] 取消安装自定义消息处理，然后启用
    LogHandler::Get().uninstallMessageHandler();
    qDebug() << "........"; // 不写入日志
    LogHandler::Get().installMessageHandler();


    // [[4]] 程序结束时释放 LogHandler 的资源，例如刷新并关闭日志文件
    LogHandler::Get().uninstallMessageHandler();

    ChatClient client;
    client.show();

    MainWindow mw;
    Dialog w;
    mw.show();
    QObject::connect(&w,SIGNAL(qwmianwindshow()),&mw,SLOT(receivelogin()));//test界面发送的信号关联到mainwindow界面的槽
    QObject::connect(&mw,SIGNAL(testshow()),&w,SLOT(receiveshow()));//mainwindow界面发送的信号关联到test界面的槽
    return a.exec();
}


