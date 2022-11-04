#include "chessboard.h"
#include "chessbox.h"
#include "game.h"
#include "piece.h"
#include <QColor>
extern Game *game;
ChessBoard::ChessBoard()
{
    setUpBlack();
    setUpWhite();
}
void ChessBoard::drawBoxes(int x,int y)
{
    int SHIFT = 100;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            ChessBox *box = new ChessBox();
            game->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            if((i+j)%2==0)
                box->setOriginalColor(QColor(225,178,125,255));
            else
                box->setOriginalColor(QColor(153,70,0,255));
            game->addToScene(box);

        }
    }

}


void ChessBoard::addChessPiece() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            ChessBox *box =game->collection[i][j];
            if(i < 3 &&((i+j)%2!=0)) {
                static int k;
                box->placePiece(black[k]);
                game->alivePiece.append(black[k]);
                game->addToScene(black[k++]);
            }
            if(i > 4 && ((i+j)%2!=0)) {
                static int h;
                box->placePiece(white[h]);
                game->alivePiece.append(white[h]);
                game->addToScene(white[h++]);
            }

        }
    }
}

void ChessBoard::setUpWhite()
{
    ChessPiece *piece;
    for(int i = 0; i < 12; i++) {
        piece = new Piece("WHITE");
        white.append(piece);
    }




}

void ChessBoard::setUpBlack()
{
    ChessPiece *piece;

    for(int i = 0; i < 12 ; i++) {
        piece = new Piece("BLACK");
        black.append(piece);
    }
}

void ChessBoard::setUpQueen()
{
}


