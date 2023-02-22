#ifndef RECVFILE_H
#define RECVFILE_H

#include <QObject>
#include <QTcpSocket>

class RecvFile : public QObject
{
    Q_OBJECT
public:
    explicit RecvFile(QObject *parent = nullptr);

    //连接服务器
    void connectServer(QString ip,unsigned short port);

    void dealData();

signals:
    void connectOk();
    void message(QByteArray msg);
    void gameOver();

private:
    QTcpSocket* m_tcp;
};

#endif // RECVFILE_H
