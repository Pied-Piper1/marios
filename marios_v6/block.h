#ifndef BLOCK_H
#define BLOCK_H

#include "object.h"

class block:public Object
{
public:
    block();
    QRectF boundingRect()const;
    QPainterPath shape() const;
    void advance();
    void solveCollisions();
    void hit(Object *what, direction fromDir);
    QString name();
    int num;
};

#endif // BLOCK_H
