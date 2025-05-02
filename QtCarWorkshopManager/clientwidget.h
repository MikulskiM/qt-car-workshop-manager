#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include "car.h"

class ClientWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ClientWidget(Car& car, QWidget *parent = nullptr);

signals:
    void showIssues();
    void fixIssues();

private:
    QLabel* carLabel;
    QPushButton* showIssuesButton;
    QPushButton* fixIssuesButton;

    void displayClientInfo(Car& car);
};

#endif // CLIENTWIDGET_H
