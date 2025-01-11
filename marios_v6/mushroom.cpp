#include "mushroom.h"
#include <QDebug>

mushroom::mushroom() {
    walkable=false;
    collidable=false;
    setPixmap(QString(":/res/mushroom-red.png"));
    moving=true;
    move_speed=1;
    moving_speed_div=2;
    move_counter=0;
    fall_speed=2;
    blocked=false;
    collidable=true;
    failing=false;
    died=false;
    moveable=true;
    setZValue(4);
}


QRectF mushroom::boundingRect()const{
    return QRectF(0,0,16,16);
}



void mushroom::hit(Object *what, direction fromDir){
    if(died)
        return;
    if(what->name()=="mario"){
        what->hit(this,inverse(fromDir));
        died=true;
        remove=true;
    }
}




void mushroom::advance()
{
    if(x()-view_x<=200)
        start_moving=true;
    if(!start_moving)
        return;

    if(y()>240)
        remove=true;

    solveCollisions();
    if(failing){
        move_speed=0;
        setY(y()+fall_speed);
    }
    if(!failing){
        move_speed=1;
    }
    move_speed = move_counter % moving_speed_div == 0;
    //    if(blocked){
    //    move_speed=0;
    //    blocked=false;}
    if(moving)
    {
        if(dir==RIGHT){
            setX(x()+move_speed);
        }
        if(dir==LEFT){
            setX(x()-move_speed);
        }
    }
}




void mushroom::solveCollisions()
{
    failing=true;
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(auto it :colliding_items){
        //        Pipe*pip=dynamic_cast<Pipe*>(it);
        //        goomba*goo=dynamic_cast<goomba*>(it);
        Object*obj=dynamic_cast<Object*>(it);
        if(obj&&obj->isCollidable()){
            direction dire=collisionDirection(obj);
            if((dire==RIGHT||dire==LEFT)&&dir==dire){
                change_direction();
            }
            if(dire==DOWN&&obj->isWalkable())
            {
                moveBy(0,-y()-boundingRect().height()+obj->y()+0.01);
                failing=false;
            }

        }
        //        if(pip){
        //            direction dire=collisiondirection(pip);
        //            if(dire==RIGHT||dire==LEFT){
        //                if(dir==dire){
        //                    change_direction();
        //                    blocked=true;
        //                }

        //            }
        //        }
        //        if(goo){
        //            direction dire=collisiondirection(goo);
        //            if(dire==RIGHT||dire==LEFT){
        //                if(dir==dire){
        //                    change_direction();
        //                }
        //            }

        //        }
    }
}


void mushroom::change_direction()
{
    if(dir==RIGHT){
        dir=LEFT;
    }
    else {
        dir=RIGHT;
    }

}


void mushroom::fall(bool flag)
{
    failing=flag;
}


QString mushroom::name(){
    return QString("mushroom");
}
