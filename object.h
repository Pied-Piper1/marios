#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>
#include <QPixmap>
#include "util.h"


//设置显示zvalue优先度，背景为0，花、金币为1，障碍为2，动物为4,乌龟壳为5,碎片为6

class Object : public QGraphicsPixmapItem
{
protected:

    bool walkable;		// whether the object is walkable
    bool collidable;	// whether the object is collidable
    bool died=false;
    bool remove=false;
    bool moveable=false;

public:
    bool enemy;
    Object();
    bool isWalkable()   {return walkable;  }
    bool isCollidable() {return collidable;}
    bool isDied()       {return died;};
    bool isremove()     {return remove;};
    bool ismoveable()     {return moveable;};
    int view_x;

    // object name
    virtual QString name() = 0;

    // advance (=compute next location)
    virtual void advance() = 0;

    virtual void solveCollisions() = 0;


    // object hit by 'what' from direction 'fromDir'
    virtual void hit(Object *what, direction fromDir) = 0;

    // utility methods: detect collision/touching direction
    virtual direction collisionDirection(Object* item);
    virtual direction touchingDirection(Object* item);
};

#endif // OBJECT_H
