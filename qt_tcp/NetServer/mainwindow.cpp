#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QDebug>
#include <QRandomGenerator>
#include <QFileDialog>
#include <QMessageBox>
#include "sendfile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug()<<"当前主线程id: "<<QThread::currentThread();
    ui->port->setText("8989");

    m_server=new MyTcpServer(this);

    connect(m_server,&MyTcpServer::newClient,this,[=](qintptr socket){
        //处理子线程相关动作
        QThread *subThread =new QThread;
        SendFile *worker=new SendFile(socket);   //不能指定父对象
        worker->moveToThread(subThread);
        connect(this,&MainWindow::start,worker,&SendFile::working);

        connect(worker,&SendFile::done,this,[=](){
            qDebug()<<"销毁子线程和对象资源";
            subThread->quit();
            subThread->wait();
            subThread->deleteLater();
            worker->deleteLater();
        });

        connect(worker,&SendFile::text,this,[=](QByteArray msg){
            QVector<QColor> colors={
                Qt::red,Qt::green,Qt::black,Qt::blue,Qt::darkRed,Qt::cyan,Qt::magenta
            };
            int index=QRandomGenerator::global()->bounded(colors.size());
            ui->msg->setTextColor(colors.at(index));
            ui->msg->append(msg);
        });

        subThread->start();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    unsigned port=ui->port->text().toUShort();
    m_server->listen(QHostAddress::Any,port);
}


void MainWindow::on_selectFile_clicked()
{
    QString path=QFileDialog::getOpenFileName(this);
    if(!path.isEmpty())
    {
        ui->path->setText(path);
    }
}


void MainWindow::on_send_clicked()
{
    // 得到文件路径
    if(ui->path->text().isEmpty())
    {
        QMessageBox::information(this,"提示","要发送的文件不能为空!");
        return;
    }
    emit start(ui->path->text());
}

