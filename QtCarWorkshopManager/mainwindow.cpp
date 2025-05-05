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
        qDebug().noquote() << "\nShowing car issues - " << car->getCarRegistrationNumber() << ":";
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

            std::ofstream file("repair_log.txt", std::ios::app);
            if (file.is_open()) {
                file << "Client: " << car->getCarInfo() << "\n";
                file << "Fixed issues:\n";
                for (auto& issue : car->getIssues()) {
                    file << "- " << issue.first << ": " << issue.second << " $\n";

                    workshop.addIssue(issue.first, issue.second);
                }
                file << "Total paid: " << totalCost << " $\n";
                file << "-------------------------\n";
                file.close();
            }

            workshop.addTakings(totalCost);
            workshop.sendData();

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

void MainWindow::on_buttonGeneratePdfReport_clicked()
{
    QFile file("repair_log.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Could not open repair_log.txt");
        return;
    }

    QTextStream in(&file);
    QMap<QString, QPair<int, int>> repairs;
    int total = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.startsWith("- ")) {
            int sep = line.indexOf(":");
            if (sep == -1) continue;

            QString issue = line.mid(2, sep - 2);
            QString priceStr = line.mid(sep + 1).trimmed();
            priceStr.chop(2);   // delete " $"
            int price = priceStr.toInt();

            auto& entry = repairs[issue];
            entry.first += 1;
            entry.second += price;

            total += price;
        }
    }
    file.close();

    QPdfWriter pdf("report.pdf");
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter p(&pdf);
    if (!p.isActive()) {
        QMessageBox::warning(this, "Painter Error", "Could not start painter");
        return;
    }

    p.setWindow(0, 0, 595, 842);    // A4
    QFont font("Courier");
    font.setPointSize(2);
    p.setFont(font);

    int y = 50;
    int dy = 10;
    int x = 50;

    p.drawText(x, y, "------------------------------------------------------------");
    y += dy;

    for (auto it = repairs.begin(); it != repairs.end(); ++it) {
        QString line = QString("%1 $ | %2x | %3")
        .arg(it.value().second, 6, 10, QChar(' '))
            .arg(it.value().first, 2)
            .arg(it.key());
        p.drawText(x, y, line);
        y += dy;
    }

    p.drawText(x, y, "------------------------------------------------------------");
    y += dy;

    QString totalLine = QString("| TOTAL | %1 $").arg(total);
    p.drawText(x, y, totalLine);
    y += dy;

    p.drawText(x, y, "------------------------------------------------------------");
    p.end();

    QMessageBox::information(this, "Report", "PDF report generated as 'report.pdf'");
}
