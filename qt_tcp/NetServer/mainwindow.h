#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytcpserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void start(QString name);// 通知子线程开始工作

private slots:
    void on_start_clicked();

    void on_selectFile_clicked();

    void on_send_clicked();

private:
    Ui::MainWindow *ui;
    MyTcpServer* m_server;
};
#endif // MAINWINDOW_H
