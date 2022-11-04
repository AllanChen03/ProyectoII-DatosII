#include "queen.h"
#include "game.h"
extern Game *game;
Queen::Queen(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
}

void Queen::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/White.png"));
    else
        setPixmap(QPixmap(":/images/Black.png"));
}


void Queen::moves()
{

    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

        if(col > 0 && row > 0 && !(game->collection[row-1][col-1]->getChessPieceColor() == team)) {//up left
            location.append(game->collection[row-1][col-1]);
            game->collection[row-1][col-1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col < 7 && row > 0 && !(game->collection[row-1][col+1]->getChessPieceColor() == team)) { // up right
            location.append(game->collection[row-1][col+1]);
            game->collection[row-1][col+1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }

        if(col > 0 && row < 7  && !(game->collection[row+1][col-1]->getChessPieceColor() == team)) {//down left
            location.append(game->collection[row+1][col-1]);
            game->collection[row+1][col-1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col < 7 && row < 7 && !(game->collection[row+1][col+1]->getChessPieceColor() == team)) {//down right
            location.append(game->collection[row+1][col+1]);
            game->collection[row+1][col+1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }

}
