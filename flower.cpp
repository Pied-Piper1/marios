#include "flower.h"


flower::flower() {
    store[0]=loadTexture(":/res/flower-0.bmp");
    store[1]=loadTexture(":/res/flower-1.bmp");
    store[2]=loadTexture(":/res/flower-2.bmp");
    store[3]=loadTexture(":/res/flower-3.bmp");
    setPixmap(store[state]);
    walkable=false;
    collidable=false;
    setZValue(1);
}

QRectF flower::boundingRect()const{
    return QRectF(0,0,16,16);
}

QPainterPath flower::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void flower::advance(){
    num++;
    if(num%15==0)
        state++;
    setPixmap(store[state%4]);
    if(time){
        moveBy(0,-moving_speed);
        time--;
    }
}

void flower::solveCollisions(){
    return;
}

QString flower::name(){
    return QString("flower");
}

void flower::hit(Object *what, direction fromDir){
    if(time)
        return; //花完全升起
    if(died)
        return;
    if(what->name()=="mario"){
        what->hit(this,inverse(fromDir));
        died=true;
        remove=true;
    }
}

