#include "dialog_connect_to_server.h"
#include "ui_dialog_connect_to_server.h"
#include <string>
#include <QDebug>
#include <cstdio>

bool ipvalid(const QString& ip){
    char *ch;
    QByteArray qb=ip.toLatin1();
    ch=qb.data();
    int a,b,c,d;
    if(std::sscanf(ch,"%d.%d.%d.%d",&a,&b,&c,&d)!=4)
        return false;
    if(a<1||a>255)
        return false;
    if(b<0||b>255)
        return false;
    if(c<0||c>255)
        return false;
    if(d<0||d>255)
        return false;
    return true;
}

Dialog_Connect_to_Server::Dialog_Connect_to_Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Connect_to_Server)
{
    ui->setupUi(this);
}

Dialog_Connect_to_Server::~Dialog_Connect_to_Server()
{
    delete ui;
}

void Dialog_Connect_to_Server::on_buttonBox_accepted()
{
    QString ip=ui->lineEdit->text();
//    qDebug()<<str;
    if(!ipvalid(ip)){
        Dialog_Connect_to_Server* dialog2 = new Dialog_Connect_to_Server(this);
        dialog2 -> setWindowTitle(QString("Invalid ip. Try again"));
        dialog2 -> show();
        qDebug("invalid ip!");
//        this->rejected();
    }
    else{
//        this->accepted();
    }
}

