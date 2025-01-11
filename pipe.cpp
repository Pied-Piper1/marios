#include "pipe.h"

pipe::pipe(int num):num(num){
    if(num==1)
        setPixmap(QString(":/res/pipe-small.png"));
    else if(num==2)
        setPixmap(QString(":/res/pipe-med.png"));
    else if(num==3)
        setPixmap(QString(":/res/pipe-big.png"));

    walkable=true;
    collidable=true;
    setZValue(2);
}

QRectF pipe::boundingRect()const{
    return QRectF(0,0,16*2,16*(num+1));
}

QPainterPath pipe::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void pipe::advance(){
    return;
}

void pipe::solveCollisions(){
    return;
}

QString pipe::name(){
    return QString("pipe");
}


void pipe::hit(Object *what, direction fromDir){
    return;
}



