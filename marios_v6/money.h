#ifndef MONEY_H
#define MONEY_H

#include "object.h"
#include "mario.h"


class money:public Object
{
public:
    money();
    QRectF boundingRect()const;
    QPainterPath shape() const;
    void advance();
    void solveCollisions();
    void hit(Object *what, direction fromDir);
    QString name();
    QPixmap store[4];
    int state=0;
    int moving_speed=1;
    int time=48/moving_speed;
    int num=0;//变图计数器
};


#endif // MONEY_H
