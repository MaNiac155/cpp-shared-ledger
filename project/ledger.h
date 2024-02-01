#ifndef LEDGER_H
#define LEDGER_H

#include <QString>
#include <vector>
using std::vector;

class Bill{
private:
    int billID;
    QString issuer;//from
    QString holder;//to

    //TODO: assets
    QString asset;
    int amount;


public:

    QString notes;//备注
    Bill();
    Bill(QString iss,QString hol,QString ass,int amo,QString note="");
    ~Bill(){};
    void showBill();
    QString getIssuer(){return issuer;}
    QString getHolder(){return holder;}
    QString getAsset(){return asset;}
    int getAmount(){return amount;}

    QString getNote(){return notes;}
    QString changeNote();//TODO
    void addToFile(QString filename);
};

class Ledger
{
private:
    vector<Bill> bills;

public:
    Ledger();

    // 数据存放在文件中，程序运行时从文件中读取并创建对象。
    Ledger(QString filename);//从文件中读取
    ~Ledger(){};


    void readFile();
    void writeBilltoFile(Bill bill);
    void showBills();
    QString getBillStrAt(int num);
    int getBillsSum();

    void addBill(QString& issuer, QString& holder, QString asset,int amount);
    //TODO
    vector<Bill> findBill(QString& targetName);

    //TODO
    void changeBill();

    void logToFile(QString filename);
    Bill getBillAt(int index);
};


#endif
