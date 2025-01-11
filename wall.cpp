#include "wall.h"

wall::wall()
{
    setPixmap(QString(":/res/wall.png"));
    walkable=true;
    collidable=true;
    setZValue(2);
}


QRectF wall::boundingRect()const{
    return QRectF(0,0,16,16);
}


QPainterPath wall::shape() const {
    // 返回你的图形项的精确形状
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void wall::solveCollisions(){
    return;
}

void wall::advance(){
    return;
}

QString wall::name(){
    return QString("wall");
}


void wall::hit(Object *what, direction fromDir){
    return;
}


wall::~wall() {}
