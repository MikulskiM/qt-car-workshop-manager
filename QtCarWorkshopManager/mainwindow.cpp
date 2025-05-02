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
    delete ui;
}

void MainWindow::on_buttonGenerateClient_clicked()
{
    clients.push_back(Car());
    clients.back().printDebugInfo();

    Car& car = clients.back();

    ClientWidget* cw = new ClientWidget(car, this);
    connect(cw, &ClientWidget::showIssues, this, []() {
        qDebug() << "Showing car issues!";
    });
    connect(cw, &ClientWidget::fixIssues, this, []() {
        qDebug() << "Fixing car issues!";
    });

    clientLayout->addWidget(cw);
}
