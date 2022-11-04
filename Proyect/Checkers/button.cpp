#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(QString name, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    //Para dibujar el rectangulo
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);

    //Dibuja el texto necesario
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white);

    //Acepta el evento del mouse
    setAcceptHoverEvents(true);
}
//Capturador del mouse y evento
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
    emit clicked();
}
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //cambia el color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);
    }
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //cambia el color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);
    }
}
