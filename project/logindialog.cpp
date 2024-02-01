#include "logindialog.h"
#include "./ui_logindialog.h"
#include<QInputDialog>
#include<QMessageBox>
#include <string.h>
#include <fstream>
#include <QFile>
#include <QDir>
#include <QTextStream>

using std::string;

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    _canLog=false;
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

// 创建需要的目录//
    QString basePath = QDir::currentPath();
    QString relaPath1="loginData";
    QDir directory;
    if (directory.mkdir(basePath + "/"+ relaPath1)) {
        qDebug() << "loginData目录创建成功";
    } else {
        qDebug() << "loginData目录创建失败";
    }
    QString relaPath2="userData";
    if (directory.mkdir(basePath +"/"+ relaPath2)) {
        qDebug() << "userData目录创建成功";
    } else {
        qDebug() << "userData目录创建失败";
    }
}

loginDialog::~loginDialog()
{
    delete ui;
}

bool loginDialog::canLog(){
    return _canLog;
}

void loginDialog::on_logButton_released()
{
    /////////////////////////
    QString user_name=ui->nameEdit->text();
    QString pw=ui->passEdit->text();
    QString filepath="loginData/"+user_name+".pwd";
    QFile file(filepath);
    if(!file.exists()){
        QMessageBox::critical(this,tr("错误"),tr("用户名不存在"));
    }
    else{
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString password=in.readAll();

            if(pw==password){
                QMessageBox::information(this,tr("成功"),tr("登录成功"));
                _canLog=true;
                this->name=user_name;
                this->close();
            }
            else{
                QMessageBox::critical(this,tr("错误"),tr("密码错误，登录失败"));
            }
        } else {
            qDebug() << "文件出错";
        }
    }
}


void loginDialog::on_signButton_released()
{
    ui->stackedWidget->setCurrentWidget(ui->signinPage);
}


void loginDialog::on_retnButton_released()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}


void loginDialog::on_signButton_1_released()
{
    QString user_name=ui->nameEdit_2->text();
    QString pw=ui->pwEdit->text();
    QString pw_confirm=ui->pwconEdit->text();
    if(pw_confirm!=pw){
        QMessageBox::critical(this,tr("错误"),tr("两次输入密码不一致"));
    }
    else{
        QString filepath="loginData/"+user_name+".pwd";
        QFile file(filepath);
        if(file.exists()){
            QMessageBox::critical(this,tr("错误"),tr("用户名已存在，请重新输入"));
        }
        else{
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);

                // 写入新文件的内容
                out <<pw;

                file.close();

                qDebug() << "成功创建用户";
                QMessageBox::information(this,tr("成功"),tr("用户创建成功，请登录"));
                ui->stackedWidget->setCurrentWidget(ui->loginPage);
            } else {
                qDebug() << "文件出错";
            }
        }
    }


}

