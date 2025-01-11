#ifndef DEBRIS_H
#define DEBRIS_H

#include "object.h"


class debris:public Object
{
public:
    debris(direction Dir_h,direction Dir_v);
    QRectF boundingRect()const;
    QPainterPath shape() const;
    void advance();
    void solveCollisions();
    void hit(Object *what, direction fromDir);
    QString name();
    double horizontal_speed=0.5;
    double vertical_speed=0.3;
    double acceleration=0.1;
};

#endif // DEBRIS_H
