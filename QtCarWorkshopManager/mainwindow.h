#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMessageBox>
#include <vector>
#include <fstream>
#include <QFile>
#include <QPdfWriter>
#include <QPainter>

#include "Car.h"
#include "clientwidget.h"
#include "workshop.h"

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

private slots:
    void on_buttonGenerateClient_clicked();
    void on_buttonGeneratePdfReport_clicked();

private:
    Ui::MainWindow *ui;
    vector<Car*> clients;
    QVBoxLayout* clientLayout;
    Workshop workshop;
};
#endif // MAINWINDOW_H
