#ifndef PIECE_H
#define PIECE_H

#include "chesspiece.h"
class Piece:public ChessPiece
{
public:
    Piece(QString team,QGraphicsItem *parent = 0);
    void setImage();

    void moves();

};


#endif // PIECE_H
