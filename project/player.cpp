#include "player.h"
#include "ledger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <QFile>
#include <QTextStream>


using std::cin; using std::cout;
using std::endl;

int ID_Gen=1;
QString getIDStr(int ID_Gene){
    QString IDString=QString::number(ID_Gene);
    ID_Gene++;
    return IDString;
}


Player::Player(){
    this->ID=getIDStr(ID_Gen);
    this->name="Unnamed";
    this->password="123";
}

Player::Player(QString name, QString password,vector<QString> typeAsset, vector<long> balances):
    name(name),password(password){
    this->ID=getIDStr(ID_Gen);
    for(int i=0;i<typeAsset.size();i++){
        assets[typeAsset[i]]=balances[i];
    }
}
Player::Player(QString name,QString password):
    name(name),password(password){
    this->ID=getIDStr(ID_Gen);
}

Player::Player(QString filename){
    QFile file(filename); //将"文件路径"替换为你的文件路径
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split("\t");
        this->logAsset(list[0],list[1].toInt());
    }
    file.close();
}


void Player::logAsset(QString type,int money){

    if(assets.find(type)==assets.end()){
        this->assets[type]=money;
    }
    else{
        this->assets[type]+=money;
    }

}

void Player::changeAsset(QString asset, int amount){
    this->assets[asset]-=amount;
}


