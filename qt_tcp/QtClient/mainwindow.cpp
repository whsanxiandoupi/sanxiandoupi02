#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->port->setText("8899");
    ui->ip->setText("127.0.0.1");
    setWindowTitle("客户端");
    ui->disconnect->setDisabled(true);

    // 创建连接的客户端对象
    m_tcp=new QTcpSocket(this);

    connect(m_tcp,&QTcpSocket::readyRead,this,[=](){
        QByteArray data=m_tcp->readAll();
        ui->record->append("服务器发来: "+data);
    });

    connect(m_tcp,&QTcpSocket::disconnected,this,[=](){
        m_tcp->close();
        m_tcp->deleteLater(); //delete
        m_status->setPixmap(QPixmap(":/disconnect.png").scaled(20,20));
         ui->record->append("服务器和客户端断开连接...");
         ui->connect->setDisabled(false);
         ui->disconnect->setEnabled(false);
    });

    connect(m_tcp,&QTcpSocket::connected,this,[=](){
        m_status->setPixmap(QPixmap(":/connect.png").scaled(20,20));
        ui->record->append("连接成功...");
        ui->connect->setDisabled(true);
        ui->disconnect->setEnabled(true);
    });

    // 状态栏
    m_status=new QLabel;
    m_status->setPixmap(QPixmap(":/disconnect.png").scaled(20,20));
    ui->statusbar->addWidget(new QLabel("连接状态: "));
    ui->statusbar->addWidget(m_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sendMsg_clicked()
{
    QString msg=ui->msg->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->record->append("客户端发送: "+msg);
    ui->msg->clear();
}


void MainWindow::on_connect_clicked()
{
    QString ip=ui->ip->text();
    unsigned short port=ui->port->text().toUShort();
    m_tcp->connectToHost(QHostAddress(ip),port);
}


void MainWindow::on_disconnect_clicked()
{
    m_tcp->close();
    ui->connect->setDisabled(false);
    ui->disconnect->setEnabled(false);

}

