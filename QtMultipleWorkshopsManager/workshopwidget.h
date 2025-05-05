#ifndef WORKSHOPWIDGET_H
#define WORKSHOPWIDGET_H

#include <QObject>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>

#include "workshop.h"

class WorkshopWidget : public QFrame
{
    Q_OBJECT
public:
    WorkshopWidget(Workshop& workshop, QWidget* parent = nullptr);

private:
    QLabel* label;
};

#endif // WORKSHOPWIDGET_H
