#include "pieces.h"
#include "chessboard.h"
#include <qmessagebox.h>
#include <QMouseEvent>
pieces::pieces()
{

}
int pieces::color(){
    if(type>='a'&&type<='l')
        return 0;
    else if(type>='m'&&type<='x')
        return 1;
    return -1;
}
int pieces::ref(){
    if(type>='a'&&type<='l')
        return type-'a';
    else if(type>='m'&&type<='x')
        return type-'m';
    return -1;
}
bool pieces::canmove(){
    if(type=='a'||type=='l'||type=='m'||type=='x')
        return false;
    return true;
}
void pieces::refresh(){
    if(status==0){
        setGeometry(QRect(px,py,60,28));
        setStyleSheet(QString("image: url(:/new/image/placeholder_unopenned.png);"));
        setScaledContents(true);
        setVisible(true);
    }
    else if(status==1){
        setGeometry(QRect(px,py,60,28));
        setStyleSheet(QString(getimage()));
        setScaledContents(true);
        setVisible(true);
    }
    else if(status==2){
        setStyleSheet(QString(""));
        setGeometry(QRect(px,py,60,28));
        setVisible(true);
    }
    else{
        setVisible(false);
    }
}
QString pieces::getimage(){
    if(type=='a')return QString("image: url(:/new/image/dilei_red.png);");
    if(type=='b')return QString("image: url(:/new/image/gongbing_red.png);");
    if(type=='c')return QString("image: url(:/new/image/paizhang_red.png);");
    if(type=='d')return QString("image: url(:/new/image/lianzhang_red.png);");
    if(type=='e')return QString("image: url(:/new/image/yingzhang_red.png);");
    if(type=='f')return QString("image: url(:/new/image/tuanzhang_red.png);");
    if(type=='g')return QString("image: url(:/new/image/lvzhang_red.png);");
    if(type=='h')return QString("image: url(:/new/image/shizhang_red.png);");
    if(type=='i')return QString("image: url(:/new/image/junzhang_red.png);");
    if(type=='j')return QString("image: url(:/new/image/siling_red.png);");
    if(type=='k')return QString("image: url(:/new/image/bomb_red.png);");
    if(type=='l')return QString("image: url(:/new/image/flag_red.png);");
    if(type=='m')return QString("image: url(:/new/image/dilei_blue.png);");
    if(type=='n')return QString("image: url(:/new/image/gongbing_blue.png);");
    if(type=='o')return QString("image: url(:/new/image/paizhang_blue.png);");
    if(type=='p')return QString("image: url(:/new/image/lianzhang_blue.png);");
    if(type=='q')return QString("image: url(:/new/image/yingzhang_blue.png);");
    if(type=='r')return QString("image: url(:/new/image/tuanzhang_blue.png);");
    if(type=='s')return QString("image: url(:/new/image/lvzhang_blue.png);");
    if(type=='t')return QString("image: url(:/new/image/shizhang_blue.png);");
    if(type=='u')return QString("image: url(:/new/image/junzhang_blue.png);");
    if(type=='v')return QString("image: url(:/new/image/siling_blue.png);");
    if(type=='w')return QString("image: url(:/new/image/bomb_blue.png);");
    if(type=='x')return QString("image: url(:/new/image/flag_blue.png);");
    return "";
}
bool pieces::unknown(){
    return (status==0);
}
bool pieces::known(){
    return (status==1);
}
bool pieces::empty(){
    return (status==2);
}
void pieces::flip(){
    status=1;
    refresh();
}
void pieces::perish(){
    if(type=='a')
        static_cast<chessboard*>(parent())->demine(0);
    else if(type=='m')
        static_cast<chessboard*>(parent())->demine(1);
    status=2;
    refresh();
    if(type=='l')
        static_cast<chessboard*>(parent())->win(1);
    else if(type=='x')
        static_cast<chessboard*>(parent())->win(0);
}
void pieces::mousePressEvent(QMouseEvent *ev){
    if(ev->button()==Qt::LeftButton)
        static_cast<chessboard*>(parent())->DealMouseEvent(this);
}
//QMessageBox::information(NULL,"单击","单击了我",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
