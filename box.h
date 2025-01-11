#ifndef BOX_H
#define BOX_H

#include "object.h"
#include "mushroom.h"
#include "flower.h"
#include "money.h"
#include <QGraphicsScene>


class box:public Object
{
public:
    box(int what);//0为mushroom或者flower 1为金币
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
    QPixmap store[4];
    int state=0;
    int num=0;
    int type=0;
    bool used=false;
    QGraphicsScene*scene;
    void SetScene(QGraphicsScene*scene);
    QGraphicsScene* GetScene();
};

#endif // BOX_H
