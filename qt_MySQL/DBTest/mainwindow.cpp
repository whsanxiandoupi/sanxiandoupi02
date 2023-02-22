#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QSqlDatabase db = QSqlDatabase::addDatabase("");
    QStringList list =QSqlDatabase::drivers();
    qDebug()<<list;

}

MainWindow::~MainWindow()
{
    delete ui;
}

