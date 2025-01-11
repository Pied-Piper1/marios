#include "lift.h"

lift::lift(direction Dir)
{
    setPixmap(QString(":/res/platform.png"));
    walkable=true;
    collidable=true;
    setZValue(2);
    if(Dir==DOWN)
        moving_speed=0.5;
    else
        moving_speed=-0.5;
}


QRectF lift::boundingRect()const{
    return QRectF(0,0,16*3,8);
}


QPainterPath lift::shape() const {
    // 返回你的图形项的精确形状
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void lift::solveCollisions(){
    return;
}

void lift::advance(){
    if(y()>240)
        setY(-20);
    if(y()<-20)
        setY(240);
    moveBy(0,moving_speed);
}

QString lift::name(){
    return QString("lift");
}


void lift::hit(Object *what, direction fromDir){
    if(what->zValue()==4||what->zValue()==5)
    {
        if(fromDir==UP)
            what->moveBy(0,moving_speed);
    }
    return;
}

lift::~lift() {}
