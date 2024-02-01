#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include "ledger.h"
#include "QTableWidget"
#include <QListWidget>
#include<QDir>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,QString n="a");
    ~MainWindow();
    QString name;
    Player* user;
    Ledger* ledger;
    QString usrpath;
    QString ledgerpath;
    QDir dataDir;

    
    void showAssets(QTableWidget* table);
    void showUsers(QListWidget* list);
    void findAndChange(QString filename,QString Asset,int changeValue);
    void showLedger(QTableWidget *table);
    void updateAllInfo();
private slots:
    void on_settingButton_released();

    void on_returnMain_clicked();

    void on_addAsset_clicked();

    void on_tradeButton_clicked();

    void on_returnMain_3_clicked();

    void on_confirmButton_clicked();

    void on_checkButton_clicked();

    void on_pushButton_clicked();

    void on_relogButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
