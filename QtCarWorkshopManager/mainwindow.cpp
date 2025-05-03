#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* scrollContent = new QWidget();

    clientLayout = new QVBoxLayout(scrollContent);

    scrollContent->setLayout(clientLayout);

    ui->scrollArea->setWidget(scrollContent);
    ui->scrollArea->setWidgetResizable(true);
}

MainWindow::~MainWindow()
{
    for (Car* car : clients) {
        delete car;
    }
    clients.clear();
    delete ui;
}

void MainWindow::on_buttonGenerateClient_clicked()
{
    Car* car = new Car();
    clients.push_back(car);

    car->printDebugInfo();

    ClientWidget* cw = new ClientWidget(*car, this);

    connect(cw, &ClientWidget::showIssues, this, [this, car]() {
        qDebug().noquote() << "Showing car issues - " << car->getCarRegistrationNumber() << ":";
        if (car->getIssues().empty()) {
            qDebug().noquote() << "ERROR: Car issues empty!";
        }
        for (auto& issue : car->getIssues()) {
            qDebug().noquote() << issue.first << " - " << QString::number(issue.second) << " $";
        }

        QString text;
        for (auto& issue : car->getIssues()) {
            text += QString::fromStdString(issue.first) + " - " + QString::number(issue.second) + " $";
        }

        QMessageBox::information(this, "Car Issues", text);
    });
    connect(cw, &ClientWidget::fixIssues, this, []() {
        qDebug().noquote() << "Fixing car issues!";
    });

    clientLayout->addWidget(cw);
}
