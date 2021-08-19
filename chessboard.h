#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "pieces.h"
#include <QFrame>

class chessboard : public QFrame
{
private:
    pieces* chessman[12][5];
    pieces* last=nullptr;
    int red_mines,blue_mines;
    bool in_game;
public slots:
    void gene_new_chessboard();
public:
    chessboard();
    chessboard(QWidget*& qw);
    bool incamp(int x,int y);
    bool ingame();
    bool linked(pieces* a,pieces* b);
    bool caneat(pieces* a,pieces* b);
    bool rail_connect(pieces* a,pieces* b);
    bool superior(pieces* a,pieces* b);
    bool carry_flag(pieces* a,pieces* b);
    bool canperish(pieces* a,pieces* b);
    void move(pieces* a,pieces* b);
    void DealMouseEvent(pieces* p);
    void demine(int v);
    void win(int v);
    bool checkmovablity();
};

#endif // CHESSBOARD_H
/* line pixel:12 101 191 279 368
 * row pixel:13 53 97 138 181 224 358 400 443 486 529 571
 * background_label:(0,0) 440x616
 * wid:60 len:28
*/
