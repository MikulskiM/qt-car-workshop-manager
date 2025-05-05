#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpServer = new TcpServer(this);
    tcpServer->start();

    QWidget* scrollContent = new QWidget();
    layout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(layout);
    ui->scrollArea->setWidget(scrollContent);
    ui->scrollArea->setWidgetResizable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleNewWorkshop(int takings, QMap<QString, int> issues)
{
    Workshop* workshop = new Workshop();
    workshop->addTakings(takings);

    for (auto issue = issues.begin(); issue != issues.end(); issue++) {
        workshop->addIssue(issue.key().toStdString(), issue.value());
    }

    workshops.push_back(workshop);

    WorkshopWidget* workshopWidget = new WorkshopWidget(*workshop, this);
    layout->addWidget(workshopWidget);
}
