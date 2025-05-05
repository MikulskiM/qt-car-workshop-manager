#include "workshopwidget.h"

WorkshopWidget::WorkshopWidget(Workshop& workshop, QWidget* parent)
    : QFrame(parent), workshop(workshop)
{
    this->setStyleSheet(
        "border: 1px solid #888;"
        "border-radius: 5px;"
        "background-color: #e5e5e5;"
        );

    QVBoxLayout* layout = new QVBoxLayout(this);

    QString text;
    text += "Workshop: " +
            QString::fromStdString(workshop.getCity()) + " " +
            QString::fromStdString(workshop.getAddress()) + "\n";
    text += "Takings: " + QString::number(workshop.getTakings()) + " $\n";

    QMap<QString, int> counted;
    QMap<QString, int> totalCost;

    for (auto& issue : workshop.getIssues()) {
        QString name = QString::fromStdString(issue.first);
        counted[name] += 1;
        totalCost[name] += issue.second;
    }

    for (auto it = counted.begin(); it != counted.end(); ++it) {
        QString name = it.key();
        text += QString::number(it.value()) + "x " + name +
                " - " + QString::number(totalCost[name]) + " $\n";
    }

    label = new QLabel(text, this);
    layout->addWidget(label);
}

void WorkshopWidget::updateInfo()
{
    QString text;
    text += "Workshop: " + QString::fromStdString(workshop.getCity()) + " " + QString::fromStdString(workshop.getAddress()) + "\n";
    text += "Takings: " + QString::number(workshop.getTakings()) + " $\n";

    QMap<QString, int> counted;
    QMap<QString, int> totalCost;

    for (auto& issue : workshop.getIssues()) {
        counted[QString::fromStdString(issue.first)] += 1;
        totalCost[QString::fromStdString(issue.first)] += issue.second;
    }

    for (auto issue = counted.begin(); issue != counted.end(); issue++) {
        text += QString::number(issue.value()) + "x " + issue.key() + " - " + QString::number(totalCost[issue.key()]) + " $\n";
    }

    label->setText(text);
}
