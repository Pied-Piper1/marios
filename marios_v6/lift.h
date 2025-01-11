#ifndef LIFT_H
#define LIFT_H

#include "object.h"

class lift : public Object
{
public:
    explicit lift(direction Dir=DOWN);
    ~lift();
    QRectF boundingRect()const;
    QPainterPath shape() const;
    void advance();
    void solveCollisions();
    void hit(Object *what, direction fromDir);
    QString name();
    double moving_speed;
};


#endif // LIFT_H
