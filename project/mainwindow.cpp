#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include<QLineEdit>
#include <QDir>
#include "player.h"
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent,QString n)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->mainpage);
    ui->label->setText("当前用户："+n);
    name=n;
    ui->label_28->setText("当前用户："+n);
    ui->label_27->setText("当前用户："+n);
    QString dataPath = QDir::currentPath()+"/userData";
    QDir dataDir(dataPath);
    this->dataDir=dataDir;
    QString usrfile=n+".txt";

    QString usrpath=dataPath+"/"+usrfile;
    this->usrpath=usrpath;
    if(dataDir.exists(usrfile)){
        qDebug()<<"user file exists";
        this->user=new Player(usrpath);
    }
    else{
        this->user=new Player();
        QFile file(usrpath);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.close();
    }
    //ledger
    this->ledger=new Ledger();
    this->ledger->readFile();

    //show info
    showAssets(ui->tableWidget);
    showUsers(ui->listWidget);
    showLedger(ui->ledgerWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAssets(QTableWidget* table)
{
    table->setRowCount(0);
    int i=0;
    for(std::pair<QString,int> pair: user->getAssets()){
        table->insertRow(i);
        QTableWidgetItem *Item1 = new QTableWidgetItem(pair.first);
        QTableWidgetItem *Item2 = new QTableWidgetItem(QString::number(pair.second));
        table->setItem(i,0,Item1);
        table->setItem(i,1,Item2);
        i++;
    }
}

void MainWindow::showUsers(QListWidget* list){
    list->clear();
    QStringList files = dataDir.entryList(QDir::Files);
    foreach (QString file, files) {
        file.replace(".txt","");
        list->addItem(file);
    }
}

void MainWindow::showLedger(QTableWidget* table){
    table->setRowCount(0);

    for(int i=0;i<this->ledger->getBillsSum();i++){
        table->insertRow(i);
        table->setItem(i,0,new QTableWidgetItem(this->ledger->getBillAt(i).getIssuer()));
        table->setItem(i,1,new QTableWidgetItem(this->ledger->getBillAt(i).getHolder()));
        table->setItem(i,2,new QTableWidgetItem(this->ledger->getBillAt(i).getAsset()));
        table->setItem(i,3,new QTableWidgetItem(QString::number(this->ledger->getBillAt(i).getAmount())));
    }
}

void MainWindow::updateAllInfo(){
    showAssets(ui->tableWidget_2);
    showAssets(ui->tableWidget);
    showAssets(ui->tableWidget_3);
    showUsers(ui->listWidget_2);
    showUsers(ui->listWidget);
}


void MainWindow::on_settingButton_released()
{
    ui->stackedWidget->setCurrentWidget(ui->setpage);
    updateAllInfo();


}


void MainWindow::on_returnMain_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainpage);
    updateAllInfo();
}


void MainWindow::on_addAsset_clicked()
{
    int money=ui->lineEdit_2->text().toInt();
    QString type=ui->lineEdit_3->text();
    this->user->logAsset(type,money);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    showAssets(ui->tableWidget_3);
}


void MainWindow::on_tradeButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->tradepage);
    showAssets(ui->tableWidget_2);
    showUsers(ui->listWidget_2);
    for(int i=0;i<ui->listWidget_2->count();i++){
        QString iname=ui->listWidget_2->item(i)->text();
        ui->comboBox->addItem(iname);
    }
    for(int i=0;i<ui->tableWidget_2->rowCount();i++){
        QString iasset=ui->tableWidget_2->item(i,0)->text();
        ui->comboBox_3->addItem(iasset);
    }

    updateAllInfo();
}


void MainWindow::on_returnMain_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainpage);
    updateAllInfo();
}


void MainWindow::on_confirmButton_clicked()
{
    QString my_asset=ui->comboBox_3->currentText();
    QString to_name=ui->comboBox->currentText();
    QString my_name=this->name;
    int my_amount=ui->lineEdit->text().toInt();
    if(my_amount>=user->getAssets()[my_asset]){
        QMessageBox::critical(this,tr("错误"),tr("余额不足！"));
        return;
    }
    user->getAssets()[my_asset]-=my_amount;
    QString changeUsrpath=dataDir.path()+"/"+to_name+".txt";
    QString myUsrpath=dataDir.path()+"/"+my_name+".txt";
    //change my_name.txt
    findAndChange(myUsrpath,my_asset,-1*my_amount);

    this->user->changeAsset(my_asset,my_amount);

    // 修改to_name 内容
    findAndChange(changeUsrpath,my_asset,my_amount);


    //ledger////////////////////////////////////////////////
    this->ledger->addBill(my_name,to_name,my_asset,my_amount);
    this->ledger->writeBilltoFile(*new Bill(my_name,to_name,my_asset,my_amount));

    showLedger(ui->ledgerWidget);

    updateAllInfo();
}



void MainWindow::findAndChange(QString filename,QString Asset,int changeValue){
    QFile file(filename);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(&file);
    QString fileContent = in.readAll();

    QString searchWord = Asset;
    QStringList lines = fileContent.split('\n');

    for (int i = 0; i < lines.size(); i++) {
        QString line = lines[i];
        QStringList words = line.split('\t');

        if (!words.isEmpty() && words[0] == searchWord) {
            words[1] = QString::number(words[1].toInt() + changeValue); // 将值加上changeValue
            line = words.join('\t');
            lines[i] = line;
            break; // 如果只需要修改第一个匹配的行，可以加上break语句
        }
    }

    // 组装修改后的文件内容
    fileContent = lines.join('\n');

    // 回到文件开头，重新写入修改后的内容
    file.seek(0);
    QTextStream out(&file);
    out << fileContent;
    file.close();
}

void MainWindow::on_checkButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->ledgerpage);
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainpage);
}


void MainWindow::on_relogButton_clicked()
{
    qApp->quit();
    QProcess::startDetached(QCoreApplication::applicationFilePath());

}


void MainWindow::on_exitButton_clicked()
{
    QCoreApplication::quit();
}

