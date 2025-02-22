#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    process_ = new QProcess(this);

    connectBtnPtr_ = ui->connectBtn;
    rescanBtnPtr_ = ui->rescanBtn;
    statusLabelPtr_ = ui->statusLabel;
    passwordEditPtr_ = ui->passwordEdit;
    wifiListPtr_ = ui->wifiList;
    
    scanWifiSlot();
    connect(connectBtnPtr_, &QPushButton::clicked, this, &MainWindow::connectBtnSlot);
    connect(process_, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, &MainWindow::readWifiScanResults);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete process_;
}

void MainWindow::scanWifiSlot()
{
    wifiListPtr_->clear();
    process_->start("nmcli", QStringList() << "device" << "wifi" << "list");
}

void MainWindow::connectBtnSlot()
{
    statusLabelPtr_->setText("Connecting.. ");
}

void MainWindow::readWifiScanResults()
{
    if (process_->exitStatus() == QProcess::NormalExit) {
        QString output = process_->readAllStandardOutput();
        QStringList lines = output.split("\n");
        for (const QString &line : lines) {
            if (line.startsWith("*") || line.startsWith("SSID")) {
                continue; 
            }
            QStringList columns = line.simplified().split(" ");
            if (!columns.isEmpty()) {
                QString ssid = columns.at(0);
                wifiListPtr_->addItem(ssid);
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to scan for Wi-Fi networks.");
    }
}
