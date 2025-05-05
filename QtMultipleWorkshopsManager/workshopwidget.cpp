#include "workshopwidget.h"

WorkshopWidget::WorkshopWidget(Workshop& workshop, QWidget* parent)
    : QFrame(parent)
{
    this->setStyleSheet(
        "border: 1px solid #888;"
        "border-radius: 5px;"
        "background-color: #e5e5e5;"
        );

    QVBoxLayout* layout = new QVBoxLayout(this);

    QString text = "Takings: " + QString::number(workshop.getTakings()) + " $\n";
    for (auto& issue : workshop.getIssues()) {
        text += QString::fromStdString(issue.first) + ": " + QString::number(issue.second) + " $\n";
    }

    label = new QLabel(text, this);
    layout->addWidget(label);
}
