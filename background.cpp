#include "background.h"

background::background(int num) {
    if(num==0)
        setPixmap(QString(":/res/welcome.png"));
    else if(num==1)
        setPixmap(QString(":/res/bush-small.png"));
    else if(num==2)
        setPixmap(QString(":/res/bush-med.png"));
    else if(num==3)
        setPixmap(QString(":/res/bush-big.png"));
    else if(num==4)
        setPixmap(QString(":/res/hill-small.png"));
    else if(num==5)
        setPixmap(QString(":/res/hill-big.png"));
    else if(num==6)
        setPixmap(QString(":/res/cloud-small.png"));
    else if(num==7)
        setPixmap(QString(":/res/cloud-med.png"));
    else if(num==8)
        setPixmap(QString(":/res/cloud-big.png"));
    else if(num==9)
        setPixmap(QString(":/res/castle.png"));
    setZValue(0);
    walkable=false;
    collidable=false;
}

QPainterPath background::shape() const {
    return QPainterPath();
}

// QRectF background::boundingRect() const{
//     if(num==0)
//         return QRectF(0,0,16*10,16*5);
//     if(0<num<4)
//         return QRectF(0,0,16*num,16);
//     if(num==4)
//         return QRectF(0,0,16*3,16);
//     if(num==5)
//         return QRectF(0,0,16*5,16*2);
//     if(5<num<9)
//         return QRectF(0,0,16*(num-3),16*2);
//     if(num==9)
//         return QRectF(0,0,16*9,16*12);
// }

void background::advance(){
    return;
}

void background::solveCollisions(){
    return;
}

QString background::name(){
    return QString("background");
}


void background::hit(Object *what, direction fromDir){
    return;
}
