#include "piece.h"
#include <QDebug>
#include "game.h"
extern Game *game;

Piece::Piece(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
}

void Piece::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/White.png"));
    else
        setPixmap(QPixmap(":/images/Black.png"));
}


void Piece::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    //For upper Left

    if(this->getSide() == "WHITE")  {
        if(col >= 0 && row > 0 && game->collection[row-1][col-1]->getChessPieceColor() == "BLACK") { //Left
            if(row-1 >= 0 && col-1 >= 0) {
                location.append(game->collection[row-1][col-1]);
                boxSetting(location.last());


            }



        }

        if(col <= 7 && row > 0 && game->collection[row-1][col+1]->getChessPieceColor() == "BLACK") { //Right
            if(row-1 >= 0 && col+1 <= 7) {
                location.append(game->collection[row-1][col+1]);
                boxSetting(location.last());
            }
        }

        if(row> 0 && col >= 0 && (!game->collection[row-1][col-1]->getHasChessPiece())) { //Left
            if (row-1 >= 0 && col-1 >= 0){
                location.append(game->collection[row-1][col-1]);
                boxSetting(location.last());

            }

        }
        if(row> 0 && col >= 0  &&(!game->collection[row-1][col+1]->getHasChessPiece())) { //Right
            if (row-1 >= 0 && col+1 <= 7){
                location.append(game->collection[row-1][col+1]);
                boxSetting(location.last());
            }
        }
        if (row == 0)
        {
            if(col >= 0 && row < 7 && game->collection[row+1][col-1]->getChessPieceColor() == "BLACK") {//left
                if(row+1 <= 7 && col-1 >= 0) {
                    location.append(game->collection[row+1][col-1]);
                    boxSetting(location.last());
                }
            }
            if(col <= 7 && row < 7 && game->collection[row+1][col+1]->getChessPieceColor() == "BLACK") {//right
                if(row+1 <= 7 && col+1 <= 7 ) {
                    location.append(game->collection[row+1][col+1]);
                    boxSetting(location.last());
                }

            }

            if(row<7 && col >= 0 && (!game->collection[row+1][col-1]->getHasChessPiece())) {  //Left
                if (row+1 <= 7 && col-1 >= 0){
                    location.append(game->collection[row+1][col-1]);
                    boxSetting(location.last());

                }
            }
            if(row < 7 && col <= 7 && (!game->collection[row+1][col+1]->getHasChessPiece())) {  //Right
                if (row+1 <= 7 && col+1 <= 7){
                    location.append(game->collection[row+1][col+1]);
                    boxSetting(location.last());

                }


            }

        }

    }
    else{

        if(col >= 0 && row < 7 && game->collection[row+1][col-1]->getChessPieceColor() == "WHITE") {//left
            if(row+1 <= 7 && col-1 >= 0) {
                location.append(game->collection[row+1][col-1]);
                boxSetting(location.last());
            }
        }
        if(col <= 7 && row < 7 && game->collection[row+1][col+1]->getChessPieceColor() == "WHITE") {//right
            if(row+1 <= 7 && col+1 <= 7 ) {
                location.append(game->collection[row+1][col+1]);
                boxSetting(location.last());
            }

        }

        if(row<7 && col >= 0 && (!game->collection[row+1][col-1]->getHasChessPiece())) {  //Left
            if (row+1 <= 7 && col-1 >= 0){
                location.append(game->collection[row+1][col-1]);
                boxSetting(location.last());

            }
        }
        if(row < 7 && col <= 7 && (!game->collection[row+1][col+1]->getHasChessPiece())) {  //Right
            if (row+1 <= 7 && col+1 <= 7){
                location.append(game->collection[row+1][col+1]);
                boxSetting(location.last());

            }


        }
        if (row == 7)
        {
            if(col >= 0 && row > 0 && game->collection[row-1][col-1]->getChessPieceColor() == "WHITE") { //Left
                if(row-1 >= 0 && col-1 >= 0) {
                    location.append(game->collection[row-1][col-1]);
                    boxSetting(location.last());


                }



            }

            if(col <= 7 && row > 0 && game->collection[row-1][col+1]->getChessPieceColor() == "WHITE") { //Right
                if(row-1 >= 0 && col+1 <= 7) {
                    location.append(game->collection[row-1][col+1]);
                    boxSetting(location.last());
                }
            }

            if(row> 0 && col >= 0 && (!game->collection[row-1][col-1]->getHasChessPiece())) { //Left
                if (row-1 >= 0 && col-1 >= 0){
                    location.append(game->collection[row-1][col-1]);
                    boxSetting(location.last());

                }

            }
            if(row> 0 && col >= 0  &&(!game->collection[row-1][col+1]->getHasChessPiece())) { //Right
                if (row-1 >= 0 && col+1 <= 7){
                    location.append(game->collection[row-1][col+1]);
                    boxSetting(location.last());
                }
            }
        }

    }

}
