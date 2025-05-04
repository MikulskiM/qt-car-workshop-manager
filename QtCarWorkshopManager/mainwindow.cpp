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
            text += QString::fromStdString(issue.first) + " - " + QString::number(issue.second) + " $\n";
        }

        QMessageBox::information(this, "Car Issues", text);
    });

    connect(cw, &ClientWidget::fixIssues, this, [this, car, cw]() {
        qDebug().noquote() << "Fixing car issues - " << car->getCarRegistrationNumber() << ":";
        if (car->getIssues().empty()) {
            qDebug().noquote() << "ERROR: Car issues empty!";
        }

        int totalCost = 0;
        for (auto& issue : car->getIssues()) {
            totalCost += issue.second;
        }

        QMessageBox fixBox;
        fixBox.setWindowTitle("Fix Car Issues");
        fixBox.setText(QString("Total cost to fix car issues = %1 $").arg(totalCost));

        QPushButton* paidButton = fixBox.addButton(QString("Paid %1 $").arg(totalCost), QMessageBox::AcceptRole);
        QPushButton* exitButton = fixBox.addButton(QString("Exit"), QMessageBox::RejectRole);

        fixBox.exec();

        if (fixBox.clickedButton() == paidButton) {
            qDebug() << "Client paid $" << totalCost;
            car->clearIssues();

            auto fixedCar = std::find(clients.begin(), clients.end(), car);
            if (fixedCar != clients.end()) {
                delete *fixedCar;
                clients.erase(fixedCar);
            }

            clientLayout->removeWidget(cw);
            cw->deleteLater();
        }
        else {
            qDebug() << "User canceled payment";
        }
    });

    clientLayout->addWidget(cw);
}
