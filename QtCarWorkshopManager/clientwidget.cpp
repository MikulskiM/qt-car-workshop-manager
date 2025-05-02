#include "clientwidget.h"

#include <QHBoxLayout>

ClientWidget::ClientWidget(Car& car, QWidget *parent)
    : QWidget(parent)
{
    displayClientInfo(car);
}

void ClientWidget::displayClientInfo(Car &car)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    carLabel = new QLabel(QString::fromStdString(car.getCarInfo()), this);
    showIssuesButton = new QPushButton("Show issues", this);
    fixIssuesButton = new QPushButton("Fix issues", this);

    layout->addWidget(carLabel);
    layout->addWidget(showIssuesButton);
    layout->addWidget(fixIssuesButton);

    connect(showIssuesButton, &QPushButton::clicked, this, &ClientWidget::showIssues);
    connect(fixIssuesButton, &QPushButton::clicked, this, &ClientWidget::fixIssues);
}
