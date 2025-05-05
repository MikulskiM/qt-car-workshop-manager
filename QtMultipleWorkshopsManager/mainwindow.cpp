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

void MainWindow::handleNewWorkshop(QString city, QString address, int takings, QMap<QString, int> issues)
{
    for (int i = 0; i < workshops.size(); i++) {
        Workshop* w = workshops[i];
        if (QString::fromStdString(w->getCity()) == city &&
            QString::fromStdString(w->getAddress()) == address) {

            w->addTakings(takings);
            for (auto it = issues.begin(); it != issues.end(); it++) {
                w->addIssue(it.key().toStdString(), it.value());
            }

            if (i < workshopWidgets.size() && workshopWidgets[i]) {
                qDebug() << "Updating widget at index" << i
                         << "for workshop at" << QString::fromStdString(w->getCity())
                         << QString::fromStdString(w->getAddress());

                workshopWidgets[i]->updateInfo();
            }
            else {
                qDebug() << "ERROR: Workshop found but no matching widget at index" << i;
            }
            return;
        }
    }

    Workshop* workshop = new Workshop();
    workshop->addTakings(takings);
    workshop->setCity(city.toStdString());
    workshop->setAddress(address.toStdString());

    for (auto issue = issues.begin(); issue != issues.end(); issue++) {
        workshop->addIssue(issue.key().toStdString(), issue.value());
    }

    workshops.push_back(workshop);

    WorkshopWidget* workshopWidget = new WorkshopWidget(*workshop, this);
    workshopWidgets.push_back(workshopWidget);
    layout->addWidget(workshopWidget);

}

