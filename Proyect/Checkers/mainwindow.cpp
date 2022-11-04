#include <QtCore/QCoreApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QDebug>
#include <QTextStream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial= new QSerialPort();
    serial->setPortName("/dev/ttyUSB0");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::HardwareControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite);
    QObject::connect(serial,SIGNAL(readyRead()),this, SLOT(RecibirArreglo()));


}

void MainWindow::RecibirArreglo()
{
    QString arregloSerial;
    QString temp;
    QByteArray arreglo;
    QTextStream qtin(arreglo);
    QString line = qtin.readLine();
    temp = "4\r\n";
    arreglo=serial->readAll();
    arregloSerial += QString::fromStdString(arreglo.toStdString());
    cadena  = cadena + arregloSerial;
    ui->plainTextEdit->appendPlainText(cadena);
    qDebug() << cadena;
    if (temp == cadena){
        qDebug() << "True";
    }
    else{
        qDebug() << "False";
    }
    cadena = "";
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
}
