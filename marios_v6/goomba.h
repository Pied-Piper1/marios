#ifndef GOOMBA_H
#define GOOMBA_H

#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QBitmap>
#include <QTransform>
#include"object.h"

class goomba:public Object
{
public:
    goomba(direction dir);
    QPixmap texture_walk[4];
    QPixmap texture_died;
    direction dir;
    int fall_speed;
    bool moving;
    int move_speed;
    bool blocked;
    bool failing;
    int died_counting=0;
    bool start_moving=false;

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
    bool falling_die=false;


};

#endif // GOOMBA_H
