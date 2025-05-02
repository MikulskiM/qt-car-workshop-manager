#include "clientwidget.h"

#include <QHBoxLayout>

ClientWidget::ClientWidget(Car& car, QWidget *parent)
    : QFrame(parent)
{
    this->setStyleSheet(
        "border: 1px solid #888;"
        "border-radius: 5px;"
        "background-color: #e5e5e5;"
    );

    this->setFixedHeight(80);

    displayClientInfo(car);
}

void ClientWidget::displayClientInfo(Car &car)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    carLabel = new QLabel(QString::fromStdString(car.getCarInfo()), this);
    showIssuesButton = new QPushButton("Show issues", this);
    fixIssuesButton = new QPushButton("Fix issues", this);

    showIssuesButton->setCursor(Qt::PointingHandCursor);
    fixIssuesButton->setCursor(Qt::PointingHandCursor);

    layout->addWidget(carLabel);
    layout->addWidget(showIssuesButton);
    layout->addWidget(fixIssuesButton);

    layout->setContentsMargins(10, 10, 10, 10);
    this->setLayout(layout);

    connect(showIssuesButton, &QPushButton::clicked, this, &ClientWidget::showIssues);
    connect(fixIssuesButton, &QPushButton::clicked, this, &ClientWidget::fixIssues);
}
