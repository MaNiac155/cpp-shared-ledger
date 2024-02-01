#include "ledger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <QDir>
using std::cout;using std::endl;

//全局变量，实现ID自增
int myBillID=1;

Bill::Bill(){
    billID=myBillID;
    myBillID++;
    issuer="Unknown";
    holder="Unknown";
    asset="DEFAULT";
    amount=0;
    notes="Test.";
}

Bill::Bill(QString iss,QString hol,QString ass,int amo,QString note){
    this->billID=myBillID;
    myBillID++;
    this->issuer=iss;
    this->holder=hol;
    this->asset=ass;
    this->amount=amo;
    this->notes=note;
}


//void Bill::addToFile(QString filename){
//    std::ofstream file;
//    file.open(filename, std::ios::app);
//    if(file.is_open()){
//        file<<billID<<" "<<issuer<<" "<<holder<<" "<<asset<<" "<<amount<<" "<<notes<<endl;
//    }else {
//        std::cerr << "Error opening file." << std::endl;
//    }
//    file.close();
//}

//Ledger::Ledger(QString filename){
//    std::ifstream ifs;
//    ifs.open(filename,std::ios::in);
//    if(ifs.is_open()){
//        QString line;
//        while(std::getline(ifs,line)){
//            std::QStringstream iss(line);
//            QString issuer,holder,asset,note;
//            long amount;
//            iss>>issuer>>holder>>asset>>amount>>note;
//            Bill bill(issuer,holder,asset,amount,note);
//            this->bills.push_back(bill);
//        }
//    }
//    ifs.close();
//}

//void Ledger::showBills(){
//    cout<<"No.\tissuer\tholder\tasset\tamount\tNotes"<<endl;
//    for(Bill bill : bills){
//        bill.showBill();
//    }
//}

void Ledger::addBill(QString& issuer, QString& holder, QString asset,int amount){
    Bill tmp_bill(issuer, holder, asset, amount);
    this->bills.push_back(tmp_bill);

}


Ledger::Ledger(){
    QString filepath=QDir::currentPath()+"/Ledger.txt";

    if (!QFile::exists(filepath)) {  // 判断文件是否存在
        QFile file(filepath);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {  // 若不存在，则创建文件
            file.close();
        } else {
            qDebug()<<"cannot create file";
        }
    }
}
int mutex=1;


void Ledger::readFile(){//把文件中的全部账单读入对象中
    QString filepath=QDir::currentPath()+"/Ledger.txt";
    QFile file(filepath);
    while(mutex==0);
    mutex--;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString issuer,holder;
    QString asset;
    int amount;
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        if(line=='\n') break;
        QStringList list = line.split("\t");
        issuer=list[0];
        holder=list[1];
        asset=list[2];
        amount=list[3].toInt();
        this->addBill(issuer,holder,asset,amount);
    }
    file.close();
    mutex++;

}

void Ledger::writeBilltoFile(Bill bill){//写入一条账单
    QString filepath=QDir::currentPath()+"/Ledger.txt";
    QFile file(filepath);
    while(mutex==0);
    mutex--;
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out<<bill.getIssuer()<<'\t'<<bill.getHolder()<<'\t'<<bill.getAsset()<<'\t'<<bill.getAmount()<<'\n';

    file.close();
    mutex++;
}






QString Ledger::getBillStrAt(int num){
    Bill b=this->bills[num];
    QString s=b.getIssuer()+'\t'+b.getHolder()+'\t'+b.getAsset()+'\t'+QString::number(b.getAmount());
    return s;
}

Bill Ledger::getBillAt(int index){
    return this->bills[index];
}


int Ledger::getBillsSum()
{
    return this->bills.size();
}

