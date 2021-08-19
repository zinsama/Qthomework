#include "chessboard.h"
#include "mainwindow.h"
#include <QLabel>
#include <QRect>
#include <QtDebug>
#include <algorithm>
#include <ctime>
#include <queue>
#include <utility>
#include <QMessageBox>

chessboard::chessboard(QWidget*& qw):QFrame(qw){
    in_game=false;
}
bool chessboard::ingame(){
    return in_game;
}
bool chessboard::incamp(int x,int y){
    if((x==2&&y==1)||(x==2&&y==3)||(x==3&&y==2)||(x==4&&y==1)||(x==4&&y==3)||
       (x==7&&y==1)||(x==7&&y==3)||(x==8&&y==2)||(x==9&&y==1)||(x==9&&y==3))
        return true;
    return false;
}
void chessboard::gene_new_chessboard(){
    if(ingame()){
        QMessageBox::information(NULL, "Already in game", "Please wait this game ends!", 
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
    }
    in_game=true;
    //qDebug("!!!!");
    red_mines=blue_mines=3;
    int x[12][5],y[12][5];//wid=60,len=28;
    int line[5]={12,101,191,279,368};
    int row[12]={13,53,97,138,181,224,358,400,443,486,529,571};
    for(int i=0;i<12;i++)
        for(int j=0;j<5;j++){
            x[i][j]=line[j];
            y[i][j]=row[i];
        }
    pieces* p[12][5];
    char ch[60]="aaabbbcccdddeeffgghhijkklmmmnnnooopppqqrrssttuvwwx";
    srand(time(0));
    std::random_shuffle(ch,ch+50);
    int cnt=0;
    for(int i=0;i<12;i++)
        for(int j=0;j<5;j++){
            if(!incamp(i,j))
                p[i][j]=new pieces(this,0,i,j,ch[cnt++],x[i][j],y[i][j]);
            else
                p[i][j]=new pieces(this,2,i,j,'y',x[i][j],y[i][j]);
            p[i][j]->refresh();
            chessman[i][j]=p[i][j];
        }
    return ;
}
bool chessboard::rail_connect(pieces *a, pieces *b){
    bool on_rail[12][6];
    int ax=a->x,ay=a->y,bx=b->x,by=b->y;
    memset(on_rail,false,sizeof(on_rail));
    for(int j=0;j<5;j++){
        on_rail[1][j]=true;
        on_rail[5][j]=true;
        on_rail[6][j]=true;
        on_rail[10][j]=true;
    }
    for(int i=1;i<=10;i++){
        on_rail[i][0]=true;
        on_rail[i][4]=true;
    }
    qDebug()<<"rail_connect:"<<ax<<" "<<ay<<" "<<on_rail[ax][ay]<<"|"<<bx<<" "<<by<<" "<<on_rail[bx][by];
    if(!on_rail[ax][ay]||!on_rail[bx][by])
        return false;
    if(a->type!='b'&&a->type!='n'){
        int nowx=ax,nowy=ay;
        while(on_rail[nowx][nowy]&&!(nowx==5&&nowy==1)&&!(nowx==5&&nowy==3)){
            if(nowx+1==bx&&nowy==by)
                return true;
            if(chessman[nowx+1][nowy]->empty())
                nowx++;
            else break;
        }
        nowx=ax,nowy=ay;
        while(on_rail[nowx][nowy]&&!(nowx==5&&nowy==1)&&!(nowx==5&&nowy==3)){
            if(nowx-1==bx&&nowy==by)
                return true;
            if(chessman[nowx-1][nowy]->empty())
                nowx--;
            else break;
        }
        nowx=ax,nowy=ay;
        while(nowy>=0&&nowy<=4&&on_rail[nowx][nowy]){
            if(nowx==bx&&nowy+1==by)
                return true;
            if(chessman[nowx][nowy+1]->empty())
                nowy++;
            else break;
        }
        nowx=ax,nowy=ay;
        while(nowy>=0&&nowy<=4&&on_rail[nowx][nowy]){
            if(nowx==bx&&nowy-1==by)
                return true;
            if(chessman[nowx][nowy-1]->empty())
                nowy--;
            else break;
        }
    }
    else{
        typedef std::pair<int,int> pii;
        std::queue<pii> q;
        q.push(std::make_pair(ax,ay));
        bool vis[12][5];
        memset(vis,false,sizeof(vis));
        while(!q.empty()){
            pii now=q.front();
            q.pop();
            vis[now.first][now.second]=true;
            int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
            for(int i=0;i<4;i++){
                int tox=now.first+dx[i],toy=now.second+dy[i];
                if(toy>=0&&toy<=4&&!vis[tox][toy]&&on_rail[tox][toy]&&(!(tox==6&&toy==1&&i==2))&&(!(tox==6&&toy==3&&i==2))&&(!(tox==5&&toy==1&&i==3))&&(!(tox==5&&toy==3&&i==3))){
                    if(tox==bx&&toy==by)
                        return true;
                    if(chessman[tox][toy]->empty())
                        q.push(std::make_pair(tox,toy));
                }
            }
        }
    }
    return false;
}
bool chessboard::linked(pieces *a, pieces *b){
    if(a==b)
        return false;
    int ax=a->x,ay=a->y,bx=b->x,by=b->y;
    if(rail_connect(a,b)){
        qDebug()<<"rail_connected";
        return true;
    }
    if(ax==5&&ay==1&&bx==6&&by==1)
        return false;
    if(ax==5&&ay==3&&bx==6&&by==3)
        return false;
    if(ax==6&&ay==1&&bx==5&&by==1)
        return false;
    if(ax==6&&ay==3&&bx==5&&by==3)
        return false;
    int dx[8]={0,0,1,-1,-1,1,-1,1},dy[8]={1,-1,0,0,-1,-1,1,1};
    for(int i=0;i<4;i++)
        if(ax+dx[i]==bx&&ay+dy[i]==by)
            return true;
    int campx[10]={2,2,3,4,4,7,7,8,9,9},campy[10]={1,3,2,1,3,1,3,2,1,3};
    for(int i=0;i<10;i++)
        for(int j=0;j<8;j++){
            if(ax==campx[i]&&ay==campy[i]&&bx==ax+dx[j]&&by==ay+dy[j])
                return true;
            if(bx==campx[i]&&by==campy[i]&&ax==bx+dx[j]&&ay==by+dy[j])
                return true;
        }
    return false;
}
bool chessboard::caneat(pieces *a, pieces *b){
    if(a->canmove()&&a->color()!=b->color()&&b->known()&&(superior(a,b)||carry_flag(a,b)))
        return true;
    return false;
}
bool chessboard::superior(pieces *a, pieces *b){
    if(a->type=='k'||a->type=='w')
        return false;
    if(b->type=='k'||b->type=='w')
        return false;
    if(b->type=='a'&&a->type!='n')
        return false;
    if(b->type=='m'&&a->type!='b')
        return false;
    return (a->ref()>b->ref());
}
bool chessboard::carry_flag(pieces *a, pieces *b){
    if(b->type=='l'&&red_mines==0)
        return true;
    if(b->type=='x'&&blue_mines==0)
        return true;
    return false;
}
bool chessboard::canperish(pieces *a, pieces *b){
    if(!b->known())
        return false;
    if(!(a->canmove())||a->color()==b->color())
        return false;
    if(b->type=='l'||b->type=='x')
        return false;
    if(a->type=='k'||a->type=='w')
        return true;
    if(b->type=='k'||b->type=='w')
        return true;
    if(a->ref()==b->ref())
        return true;
    return false;
}
void chessboard::move(pieces *a, pieces *b){
    std::swap(chessman[a->x][a->y],chessman[b->x][b->y]);
    std::swap(a->px,b->px);
    std::swap(a->py,b->py);
    std::swap(a->x,b->x);
    std::swap(a->y,b->y);
    a->refresh();
    b->refresh();
}
void chessboard::demine(int v){
    if(v==0)
        red_mines--;
    else
        blue_mines--;
}
void chessboard::DealMouseEvent(pieces *p){
    if(last!=nullptr)
        qDebug()<<"p:"<<p->x<<" "<<p->y<<" "<<"last:"<<last->x<<" "<<last->y<<" "<<linked(last,p);
    else
        qDebug()<<"p:"<<p->x<<" "<<p->y<<" "<<"last:"<<"nullptr";
    if(p->unknown())
        p->flip();
    else if(p->known()){
        if(last!=nullptr&&linked(last,p)){
            if(caneat(last,p)&&!incamp(p->x,p->y)){
                p->perish();
                move(last,p);
                last=nullptr;
            }
            else if(canperish(last,p)&&!incamp(p->x,p->y)){
                last->perish();
                p->perish();
            }
            else
                last=p;
        }
        else
            last=p;
    }
    else if(p->empty()){
        if(last!=nullptr){
            if(last->canmove()&&linked(last,p)){
                move(last,p);
                last=nullptr;
            }
        }
    }
    else{
        qDebug()<<"error!!";
    }
}
bool chessboard::checkmovablity(){
    for(int i=0;i<12;i++)
        for(int j=0;j<5;j++){
            if(chessman[i][j]->unknown())
                return true;
            int dx[8]={0,0,1,-1,-1,1,-1,1},dy[8]={1,-1,0,0,-1,-1,1,1};
            for(int k=0;k<8;k++){
                if(chessman[i][j]->known()&&chessman[i][j]->canmove()&&linked(chessman[i][j],chessman[i+dx[k]][j+dy[k]])&&(chessman[i+dx[k]][j+dy[k]]->empty()||canperish(chessman[i][j],chessman[i+dx[k]][j+dy[k]])||caneat(chessman[i][j],chessman[i+dx[k]][j+dy[k]])))
                    return true;
            }
        }
    return false;
}
void chessboard::win(int v){//0:red wins 1:blue wins
    in_game=false;
    for(int i=0;i<12;i++)
        for(int j=0;j<4;j++)
            chessman[i][j]->setVisible(false);
    if(v==0){
        QMessageBox::information(NULL, "Game ends", "Red wins!", 
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else{
        QMessageBox::information(NULL, "Game ends", "Blue wins!", 
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}
/*background-image: url(:/new/image/placeholder_unopenned.png);
background-image: url(:/new/image/empty_camp.png);
 * */
