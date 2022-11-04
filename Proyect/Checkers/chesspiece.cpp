#include "chesspiece.h"
#include "game.h"
#include <QDebug>
#include "queen.h"

extern Game *game;
ChessPiece::ChessPiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
}

//Click del mouse
void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deseleccionar
    if(this == game->pieceToMove){
        game->pieceToMove->getCurrentBox()->resetOriginalColor();
        game->pieceToMove->decolor();
        game->pieceToMove = NULL;
       return;
    }
    //Verifica si el turno es igual al color del equipo
    if((!getIsPlaced() )|| ( (game->getTurn() != this->getSide())&& (!game->pieceToMove)) )
        return;
    //Selecciona la pieza
    if(!game->pieceToMove){
        game->pieceToMove = this;
        game->pieceToMove->getCurrentBox()->setColor(Qt::red);
        game->pieceToMove->moves();
    }
    //Consume parte del tablero
    else if(this->getSide() != game->pieceToMove->getSide()){
        this->getCurrentBox()->mousePressEvent(event);
    }


}

//Selecciona la posicion pieza
void ChessPiece::setCurrentBox(ChessBox *box)
{

    currentBox = box;
}

//Obtiene la posicion de la pieza
ChessBox *ChessPiece::getCurrentBox()
{
    return currentBox;
}

//Obtiene el lado, si blanco o negro
QString ChessPiece::getSide()
{
    return side;
}

//Configura el lado
void ChessPiece::setSide( QString value)
{
    side = value;
}

//Obtiene en donde esta posicionado la pieza
bool ChessPiece::getIsPlaced()
{
    return isPlaced;
}

//Funcion para enviar si esta en una posicion
void ChessPiece::setIsPlaced(bool value)
{
    isPlaced = value;

}
//Función de un alista para la posicion de la pieza
QList<ChessBox *> ChessPiece::moveLocation()
{
    return location;
}
void ChessPiece::decolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}

//Función para las caracteristicas de la casilla, ya sean rojo ao azul
bool ChessPiece::boxSetting(ChessBox *box)
{
    if(box->getHasChessPiece()) {
        Queen *q = dynamic_cast<Queen*>(location.last()->currentPiece);
        if(q){
            box->setColor(Qt::blue);
        }
        else
            box->setColor(Qt::red);
        return true;
    }
    else
        location.last()->setColor(Qt::darkRed);
    return false;
}
