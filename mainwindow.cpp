#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkConfigurationManager(this))
{
    ui->setupUi(this);

    connectBtnPtr_ = ui->connectBtn;
    statusLabelPtr_ = ui->statusLabel;
    passwordEditPtr_ = ui->passwordEdit;
    wifiListPtr_ = ui->wifiList;
    
    scanWifiSlot();
    connect(connectBtnPtr_, &QPushButton::clicked, this, &MainWindow::connectBtnSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::scanWifiSlot()
{
    wifiListPtr_->clear();
    QList<QNetworkConfiguration> configurations = networkManager->allConfigurations();
    for (const QNetworkConfiguration &config : configurations) {
        if (config.bearerType() == QNetworkConfiguration::BearerWLAN) {
            wifiListPtr_->addItem(config.name());
        }
    }
}

void MainWindow::connectBtnSlot()
{
    statusLabelPtr_->setText("Connecting.. ");
}
