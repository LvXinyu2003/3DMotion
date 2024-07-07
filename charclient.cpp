#include "chatclient.h"
#include <QtWidgets>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ChatClient::ChatClient(QWidget* parent)
    : QWidget(parent)
{
    // 创建UI界面
    m_textEdit = new QTextEdit;
    m_lineEdit = new QLineEdit;
    m_sendButton = new QPushButton(tr("Send"));
    m_layout = new QVBoxLayout;
    m_layout->addWidget(m_textEdit);
    m_layout->addWidget(m_lineEdit);
    m_layout->addWidget(m_sendButton);
    setLayout(m_layout);
    setWindowTitle(tr("Chat Client"));

    // 创建TCP套接字
    m_socket = new QTcpSocket(this);

    // 连接到服务器
    connect(m_socket, &QTcpSocket::connected, this, &ChatClient::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &ChatClient::onDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    m_socket->connectToHost("127.0.0.1", 12345); // 连接到本地服务器

    // 初始化讯飞API
    m_appId = "d790db02";
    m_apiKey = "f43f78b7d6b02cf53ef9231bf351aac8";
    m_apiSecret = "MThlOGZiMmJmNWUzNDI0OWQzMzJhZGU0";
    m_accessToken = "";
    m_expireTime = QDateTime();

    // 获取访问令牌
    getAccessToken();

    // 发送聊天信息
    connect(m_sendButton, &QPushButton::clicked, this, &ChatClient::sendMessage);

    // 处理@机器人事件
    connect(m_textEdit, &QTextEdit::textChanged, this, &ChatClient::onTextChange);
}

void ChatClient::onConnected()
{
    qDebug() << "Connected to server";
}

void ChatClient::onDisconnected()
{
    qDebug() << "Disconnected from server";
}

void ChatClient::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    QString message = QString::fromUtf8(data);
    m_textEdit->append(message);
}

void ChatClient::getAccessToken()
{
    // 构造HTTP请求
    QUrl url("https://openapi.xfyun.cn/v2/token");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QString auth = QString("%1:%2").arg(m_apiKey).arg(m_apiSecret).toUtf8().toBase64();
    request.setRawHeader("Authorization", QString("Basic %1").arg(auth).toUtf8());

    // 发送HTTP请求
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.post(request, QString("grant_type=client_credentials&client_id=%1&client_secret=%2").arg(m_appId).arg(m_apiSecret).toUtf8());
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // 解析HTTP响应
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        m_accessToken = jsonDocument.object().value("access_token").toString();
        int expiresIn = jsonDocument.object().value("expires_in").toInt();
        m_expireTime = QDateTime::currentDateTime().addSecs(expiresIn);
    }
    else
    {
        qDebug() << "Failed to get access token: " << reply->errorString();
    }

    // 释放HTTP响应
    reply->deleteLater();
}

QString ChatClient::getAnswer(const QString& question)
{
    // 检查访问令牌是否过期
    if (QDateTime::currentDateTime() >= m_expireTime)
    {
        getAccessToken();
    }

    // 构造HTTP请求
    QUrl url("https://openai.xfyun.cn/v2/aiui");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_accessToken).toUtf8());

    QJsonObject json;
    json.insert("scene", "main");
    json.insert("userid", "123456");
    json.insert("auth_id", "123456");
    json.insert("text", question);
    QJsonDocument jsonDocument(json);
    QByteArray postData = jsonDocument.toJson(QJsonDocument::Compact);

    // 发送HTTP请求
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.post(request, postData);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // 解析HTTP响应
    QString answer;
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonDocument.object();
        if (jsonObject.contains("data"))
        {
            QJsonObject data = jsonObject.value("data").toObject();
            QJsonArray answerArray = data.value("answer").toArray();
            for (int i = 0; i < answerArray.size(); i++)
            {
                QJsonObject answerObject = answerArray.at(i).toObject();
                if (answerObject.contains("text"))
                {
                    answer += answerObject.value("text").toString() + " ";
                }
            }
        }
    }
    else
    {
        qDebug() << "Failed to get answer: " << reply->errorString();
    }

    // 释放HTTP响应
    reply->deleteLater();

    return answer.trimmed();
}

void ChatClient::onTextChange()
{
    QString text = m_textEdit->toPlainText();
    int index = text.lastIndexOf("@机器人");
    if (index != -1)
    {
        QString question = text.mid(index + 4).trimmed();
        QString answer = getAnswer(question);
        m_textEdit->append(QString("<font color=\"red\">@机器人: %1</font>").arg(answer));
    }
}

void ChatClient::sendMessage()
{
    QString message = m_lineEdit->text();
    if (!message.isEmpty())
    {
        m_socket->write(message.toUtf8());
        m_lineEdit->clear();
    }
}
