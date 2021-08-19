#ifndef PIECES_H
#define PIECES_H

#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class pieces : public QLabel
{
private:
    int status;
public:
    char type;
    int x,y,px,py;
    pieces();
    pieces(QWidget* a,int v):QLabel(a),status(v){}
    pieces(QWidget* a,int v,int _x,int _y,char _c,int _px,int _py):QLabel(a){
        status=v;x=_x;y=_y;type=_c;
        px=_px;py=_py;
    }
    void perish();
    void refresh();
    QString getimage();
    void mousePressEvent(QMouseEvent *ev);
    bool unknown();
    int color();
    int ref();
    bool known();
    bool empty();
    bool canmove();
    void flip();
};
/* type:
 * a dilei         red
 * b gongbing      red
 * c paizhang      red
 * d lianzhang     red
 * e yingzhang     red
 * f tuanzhang     red
 * g lvzhang       red
 * h shizhang      red
 * i junzhang      red
 * j siling        red
 * k zhadan        red
 * l junqi         red
 * m dilei         blue
 * n gongbing      blue
 * o paizhang      blue
 * p lianzhang     blue
 * q yingzhang     blue
 * r tuanzhang     blue
 * s lvzhang       blue
 * t shizhang      blue
 * u junzhang      blue
 * v siling        blue
 * w zhadan        blue
 * x junqi         blue
 * y NULL
 * z
 */
#endif // PIECES_H
