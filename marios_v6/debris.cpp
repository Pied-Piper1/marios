#include "debris.h"



debris::debris(direction Dir_h,direction Dir_v) {
    setPixmap(loadTexture(":/res/brick-debris.bmp"));
    walkable=false;
    collidable=false;
    if(Dir_h==LEFT)
        horizontal_speed=-horizontal_speed;
    if(Dir_v==DOWN)
        vertical_speed=-1.5;
    setZValue(6);
}

QRectF debris::boundingRect()const{
    return QRectF(0,0,8,8);
}

QPainterPath debris::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void debris::advance(){
    if(y()>240)
        remove=true;
    vertical_speed+=acceleration;
    moveBy(horizontal_speed,vertical_speed);
}

void debris::solveCollisions(){
    return;
}

QString debris::name(){
    return QString("debris");
}

void debris::hit(Object *what, direction fromDir){

}

