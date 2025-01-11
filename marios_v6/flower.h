#ifndef FLOWER_H
#define FLOWER_H

#include "object.h"
#include "mario.h"


class flower:public Object
{
public:
    flower();
    QRectF boundingRect()const;
    QPainterPath shape() const;
    void advance();
    void solveCollisions();
    void hit(Object *what, direction fromDir);
    QString name();
    QPixmap store[4];
    int state=0;
    int moving_speed=1;
    int time=16;
    int num=0;//变图计数器
};
#endif // FLOWER_H
