#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T17:19:24
#
#-------------------------------------------------

QT       += core gui serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    chessbox.cpp \
    chessboard.cpp \
    chesspiece.cpp \
    button.cpp \
    piece.cpp \
    queen.cpp

HEADERS  += \
    game.h \
    chessbox.h \
    chessboard.h \
    chesspiece.h \
    button.h \
    piece.h \
    queen.h

FORMS    +=

RESOURCES += \
    resource.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
