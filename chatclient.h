#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDateTime>

class ChatClient : public QWidget
{
    Q_OBJECT

public:
    explicit ChatClient(QWidget* parent = nullptr);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onTextChange();
    void sendMessage();
    void getAccessToken();
    QString getAnswer(const QString& question);

public:
    QTextEdit* m_textEdit;
    QLineEdit* m_lineEdit;
    QPushButton* m_sendButton;
    QVBoxLayout* m_layout;
    QTcpSocket* m_socket;

    // 讯飞API相关信息
    QString m_appId;
    QString m_apiKey;
    QString m_apiSecret;
    QString m_accessToken;
    QDateTime m_expireTime;
};

#endif // CHATCLIENT_H
