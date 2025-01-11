#ifndef BRICK_H
#define BRICK_H

#include "object.h"
#include "mario.h"
#include <QGraphicsScene>
#include "debris.h"


class brick:public Object
{
public:
    brick();
    QRectF boundingRect()const;
    QPainterPath shape() const;
    void advance();
    void solveCollisions();
    void hit(Object *what, direction fromDir);
    QString name();
    bool jumping=false;
    bool falling=false;
    int dy=0;
    int moving_speed=1;
    void SetScene(QGraphicsScene*scene);
    QGraphicsScene* GetScene();
    QGraphicsScene* scene;
};

#endif // BRICK_H
