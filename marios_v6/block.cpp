#include "block.h"

block::block() {
    setPixmap(QString(":/res/block.png"));
    walkable=true;
    collidable=true;
    setZValue(2);
}

QRectF block::boundingRect()const{
    return QRectF(0,0,16,16);
}

QPainterPath block::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void block::advance(){
    return;
}

void block::solveCollisions(){
    return;
}

QString block::name(){
    return QString("block");
}

void block::hit(Object *what, direction fromDir){
    return;
}


