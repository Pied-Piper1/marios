#ifndef TURTLE_H
#define TURTLE_H

#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QBitmap>
#include <QTransform>
#include"object.h"
#include "QTransform"

class turtle:public Object
{
public:
    turtle(direction dir=LEFT);
    QPixmap texture[4];
    direction dir;
    int fall_speed;
    bool moving;
    int move_speed;
    bool blocked;
    bool failing;
    bool start_moving=false;
    bool turtleback=false;
    bool turtleback_2=false;
    bool turtlerotating=false;
    int turtlecount=250;

    static const int walk_div    = 10;
    QRectF boundingRect()const;
    void advance();
    // direction collisiondirection(QGraphicsPixmapItem*item);
    void solveCollisions();
    void change_direction();
    void update_move_speed();
    void hit(Object *what, direction fromDir);
    void die();
    QString name();
    void fall(bool flag);
    int move_counter;
    int moving_speed_div;
    int counting=0;


};
#endif // TURTLE_H
