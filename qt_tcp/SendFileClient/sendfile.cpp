#include "sendfile.h"

#include <QFile>
#include <QFileInfo>
#include <QHostAddress>
#include <QDebug>
#include <QThread>

SendFile::SendFile(QObject *parent)
    : QObject{parent}
{

}

void SendFile::connectServer(unsigned short port, QString ip)
{
    qDebug()<<"客户端子线程: "<<QThread::currentThread();
    m_tcp=new QTcpSocket;
    m_tcp->connectToHost(QHostAddress(ip),port);

    connect(m_tcp,&QTcpSocket::connected,this,&SendFile::connectOk);
    connect(m_tcp,&QTcpSocket::disconnected,this,[=](){
        m_tcp->close();
        m_tcp->deleteLater();
        emit gameover();
    });
}

void SendFile::sendFile(QString path)
{
    QFile file(path);
    QFileInfo info(path);
    int fileSize=info.size();
    file.open(QFile::ReadOnly);

    while(!file.atEnd()){
        static int num=0;
        if(num==0){
            m_tcp->write((char*)&fileSize,4);
        }
        QByteArray line= file.readLine();
        num+=line.size();
        int percent =(num*100/fileSize);

        emit curPercent(percent);

        m_tcp->write(line);
    }
}
