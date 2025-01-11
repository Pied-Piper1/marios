#ifndef WALL_H
#define WALL_H


#include "object.h"

class wall : public Object
{
public:
    explicit wall();
    ~wall();
    QRectF boundingRect()const;
    QPainterPath shape() const;
    void advance();
    void solveCollisions();
    void hit(Object *what, direction fromDir);
    QString name();
};

#endif // WALL_H
