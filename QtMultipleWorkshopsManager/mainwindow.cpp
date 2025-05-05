#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpServer = new TcpServer();
    tcpServer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
