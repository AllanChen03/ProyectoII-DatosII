#include "game.h"
#include "button.h"
#include <QPixmap>
#include "queen.h"
#include <QDebug>
//Esta clase lleva extensión QGraphicsView, para poder mostrar la parte gráfica
Game::Game(QWidget *parent ):QGraphicsView(parent)
{

    //Se crea la escena del juego
    gameScene = new QGraphicsScene();

    //se le asigna un tamaño
    gameScene->setSceneRect(0,0,1400,900);

    serial= new QSerialPort();  //Crea el puerto serial
    serial->setPortName("/dev/ttyUSB0"); //Puerto al cual se va a conectar
    serial->setBaudRate(QSerialPort::Baud9600); //numero de simbolos por segundo
    serial->setParity(QSerialPort::NoParity); //Paridad
    serial->setFlowControl(QSerialPort::NoFlowControl); //Control de Flow
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite); //Abre el servidor puerto Serial, recibe informacion y tambien escribe
    QObject::connect(serial,SIGNAL(readyRead()),this, SLOT(RecibirArreglo())); //Crea la conexion y llama a la funcion para escuchar el puerto Serial


    //Creación de la vista
    setFixedSize(1400,900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBackgroundBrush(brush);
    pieceToMove = NULL;

    //display turn
    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Turno: WHITE");

    //display Check
    check = new QGraphicsTextItem();
    check->setPos(width()/2-100,860);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::red);
    check->setFont(QFont("",18));
    check->setPlainText("CHECK!");
    check->setVisible(false);
    setTurn("WHITE");

}

void Game::drawChessBoard()
{
    chess = new ChessBoard();
     chess->drawBoxes(width()/2-400,50);

}

void Game::displayDeadWhite()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = whiteDead.size(); i<n; i++) {
            if(j == 4){
                k++;
                j = 0;
            }

             whiteDead[i]->setPos(40+SHIFT*j++,100+SHIFT*2*k);
             serial->write("1");

    }
}

void Game::displayDeadBlack()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = blackDead.size(); i<n; i++) {
        if(j == 4){
            k++;
            j = 0;
        }

            blackDead[i]->setPos(1140+SHIFT*j++,100+SHIFT*2*k);
            serial->write("1");
    }
}

void Game::placeInDeadPlace(ChessPiece *piece)
{
    if(piece->getSide() == "WHITE") {
        whiteDead.append(piece);
        displayDeadWhite();
    }
    else{
        blackDead.append(piece);
        displayDeadBlack();
    }
    alivePiece.removeAll(piece);
}

void Game::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}

void Game::removeFromScene(QGraphicsItem *item)
{
    gameScene->removeItem(item);

}

QString Game::getTurn()
{
    return turn;
}

void Game::setTurn(QString value)
{
    turn = value;
}

void Game::changeTurn()
{
    if(getTurn() == "WHITE")
        setTurn("BLACK");
    else
        setTurn("WHITE");
    turnDisplay->setPlainText("Turno: " + getTurn());
}

void Game::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++)
        removeFromScene(listG[i]);

    addToScene(turnDisplay);
    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(70,10);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::white);
    whitePiece->setFont(QFont("",14));
    whitePiece->setPlainText("WHITE PIECE");
    addToScene(whitePiece);
    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();

    blackPiece->setPos(1170,10);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::white);
    blackPiece->setFont(QFont("",14));
    blackPiece->setPlainText("BLACK PIECE");
    addToScene(blackPiece);
    addToScene(check);
    chess->addChessPiece();
}

void Game::RecibirArreglo()
{
    QString arregloSerial;
    QByteArray arreglo;

    qDebug() << "Seleccione la fila de la ficha que quiera mover";
    arreglo=serial->readAll();
    arregloSerial += QString::fromStdString(arreglo.toStdString());
    row =  arregloSerial[0];
    qDebug() << row;
}

void Game::drawDeadHolder(int x, int y,QColor color)
{
    deadHolder = new QGraphicsRectItem(x,y,300,900);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    deadHolder->setBrush(brush);
    addToScene(deadHolder);
}



void Game::displayMainMenu()
{

    //Create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem("Damas");
    QFont titleFont("arial" , 50);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);
    //create Button
    Button * playButton = new Button("Jugar");
    int pxPos = width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 300;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));
    addToScene(playButton);
    listG.append(playButton);
    drawChessBoard();


}

void Game::gameOver()
{
    //removeAll();
    setTurn("WHITE");
    alivePiece.clear();




}

void Game::removeAll(){
    QList<QGraphicsItem*> itemsList = gameScene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          removeFromScene(itemsList[i]);
    }
}
