#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
#include<map>
#include<vector>
using std::vector;
using std::map;


//forward declaration ! ! !
class Ledger;

extern int ID_Gen;

class Player
{
private:
    QString ID;//3位id
    QString name;
    QString password;
    map<QString,int> assets; //资产<币种, 金额>


public:
    Player();
    Player(QString name, QString password,vector<QString> typeAsset, vector<long> balances);
    Player(QString name, QString password);

    // 数据存放在文件中，程序运行时从文件中读取并创建对象。
    Player(QString filename);

    ~Player(){};


    void startTrade(Player* other,int amount,Ledger& ledger);
    bool confirmTrade(Player* starter);
    void showInfo();
    void logAsset(QString type,int money);

    QString getName(){return name;}
    map<QString,int> getAssets(){return assets;}
    void changeAsset(QString asset, int amount);


    void logToFile(QString filename);
};

QString getIDStr(int ID_Gen);

#endif
