#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QProcess>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connectBtnSlot();
    void scanWifiSlot();
    void readWifiScanResults();

private:
    Ui::MainWindow *ui;
    QPushButton *connectBtnPtr_ = nullptr;
    QPushButton *rescanBtnPtr_ = nullptr;
    QLabel *statusLabelPtr_ = nullptr;
    QLineEdit *passwordEditPtr_ = nullptr;
    QListWidget *wifiListPtr_ = nullptr;
    QProcess *process_; 
};
#endif // MAINWINDOW_Hs
