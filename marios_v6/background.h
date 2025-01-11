#ifndef BACKGROUND_H
#define BACKGROUND_H


#include "object.h"


class background:public Object
{
public:
    background(int num);
    //num 0 welcome
    //num 1-3 bush_small - bush_big
    //num 4-5 hill_small - hill_big
    //num 6-8 cloud_small - cloud_big
    //num 9 castle
    // QRectF boundingRect()const;
    QPainterPath shape() const;
    void advance();
    void solveCollisions();
    void hit(Object *what, direction fromDir);
    QString name();
    int num;
};

#endif // BACKGROUND_H
