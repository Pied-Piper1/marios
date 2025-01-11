#ifndef PIPE_H
#define PIPE_H

#include "object.h"


class pipe: public Object
{
public:
    pipe(int num);//num为1*(num+1)水管，num的取值为1-3
    QRectF boundingRect()const;
    QPainterPath shape() const;
    void advance();
    void solveCollisions();
    void hit(Object *what, direction fromDir);
    QString name();
    int num;
};

#endif // PIPE_H
