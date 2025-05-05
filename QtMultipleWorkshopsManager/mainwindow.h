#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "workshop.h"
#include "workshopwidget.h"
#include "tcpserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void handleNewWorkshop(QString city, QString address, int takings, QMap<QString, int> issues);

private:
    Ui::MainWindow *ui;

    TcpServer* tcpServer;
    QVBoxLayout* layout;
    vector<Workshop*> workshops;
    vector<WorkshopWidget*> workshopWidgets;
};
#endif // MAINWINDOW_H
