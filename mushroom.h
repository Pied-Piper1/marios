#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "object.h"
#include "mario.h"

class mushroom:public Object
{
public:
    mushroom();
    direction dir=RIGHT;
    int fall_speed;
    bool moving;
    int move_speed;
    bool blocked;
    bool failing;
    int died_counting;
    bool start_moving=false;

    static const int walk_div    = 10;
    void advance();
    QRectF boundingRect() const;
    void solveCollisions();
    void change_direction();
    void update_move_speed();
    void hit(Object *what, direction fromDir);
    void die();
    QString name();
    void fall(bool flag);
    int move_counter;
    int moving_speed_div;
};

#endif // MUSHROOM_H
