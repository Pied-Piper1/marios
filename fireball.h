#ifndef FIREBALL_H
#define FIREBALL_H
#include<object.h>
#include<QPixmap>
class fireball:public Object
{
public:
    fireball(direction Dir=RIGHT);
    QPixmap texture_fireball[4];
    double moving_speed_shuiping;
    double init_up_speed=3;
    double up_speed;
    double down_speed;
    double up_acceleration;//向上加速度
    double down_acceleration;//向下加速度
    double fixed_vertical_speed;
    double vertical_speed;
    double vertical_accleration;

    QPainterPath shape() const;
    QRectF boundingRect() const;


    virtual QString name() ;

    // advance (=compute next location)
    virtual void advance();

    virtual void solveCollisions();


    // object hit by 'what' from direction 'fromDir'
    virtual void hit(Object *what, direction fromDir){return;} ;


};

#endif // FIREBALL_H
