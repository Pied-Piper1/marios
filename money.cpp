#include "money.h"


money::money() {
    store[0]=loadTexture(":/res/coin-0.png");
    store[1]=loadTexture(":/res/coin-1.png");
    store[2]=loadTexture(":/res/coin-2.png");
    store[3]=loadTexture(":/res/coin-3.png");
    setPixmap(store[state]);
    walkable=false;
    collidable=false;
    setZValue(1);
}

QRectF money::boundingRect()const{
    return QRectF(0,0,16,16);
}

QPainterPath money::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void money::advance(){
    num++;
    if(num%15==0)
        state++;
    setPixmap(store[state%4]);
    if(time){
        moveBy(0,-moving_speed);
        time--;
    }
    else
        remove=true;
}

void money::solveCollisions(){
    return;
}

QString money::name(){
    return QString("money");
}

void money::hit(Object *what, direction fromDir){
}
