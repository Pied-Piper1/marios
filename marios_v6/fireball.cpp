#include "fireball.h"
#include<QDebug>
fireball::fireball(direction Dir)
{
    collidable=true;
    texture_fireball[0]=loadTexture(":/res/fireball-0.bmp");
    texture_fireball[1]=loadTexture(":/res/fireball-1.bmp");
    texture_fireball[2]=loadTexture(":/res/fireball-2.bmp");
    texture_fireball[3]=loadTexture(":/res/fireball-3.bmp");
    this->setPixmap(texture_fireball[0]);


    moving_speed_shuiping=6;
    fixed_vertical_speed=2.0;
    if(Dir==LEFT)
        moving_speed_shuiping=-moving_speed_shuiping;
    vertical_speed=2;
    vertical_accleration=0.2;
    remove=false;
    setZValue(4);
}



void fireball::advance()
{
    if(y()>240)
    {
        remove=true;
        return;
    }
    solveCollisions();
    moveBy(moving_speed_shuiping,vertical_speed);
    vertical_speed+=vertical_accleration;
}

void fireball::solveCollisions()
{
    if(remove)
        return;
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(auto it :colliding_items)
    {
        Object *obj=dynamic_cast<Object*>(it);
        if(obj)
        {
            direction dire=collisionDirection(obj);
            if(obj->name()=="goomba"||obj->name()=="mario"||obj->name()=="mushroom"||obj->name()=="turtle")
            {
                obj->hit(this,inverse(dire));
                remove=true;
                return;
            }
            if(dire==DOWN)
            {
                if(obj->isWalkable())
                    vertical_speed=-fixed_vertical_speed;
            }
            else
                remove=true;
            }
    }
}

QRectF fireball::boundingRect()const{
    return QRectF(0,0,8,8);
}

QPainterPath fireball::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

QString fireball::name()
{
    return QString("fireball");
}
