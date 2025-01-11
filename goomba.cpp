#include "goomba.h"

goomba::goomba(direction dir)
{
    this->dir=dir;
    texture_walk[0]=QPixmap(loadTexture(":/res/goomba-0.png"));
    texture_walk[1]=QPixmap(loadTexture(":/res/goomba-0.png"));
    texture_walk[2]=QPixmap(loadTexture(":/res/goomba-1.png"));
    texture_walk[3]=QPixmap(loadTexture(":/res/goomba-1.png"));
    texture_died=QPixmap(loadTexture(":/res/goomba-dead.png"));
    setPixmap(texture_walk[0]);
    moving=true;
    move_speed=1;
    moving_speed_div=2;
    move_counter=0;
    fall_speed=5;
    blocked=false;
    collidable=true;
    failing=false;
    died=false;
    enemy=true;
    moveable=true;
    setZValue(4);
}

QRectF goomba::boundingRect()const{
    if(died&&!falling_die)
        return QRectF(0,0,16,8);
    return QRectF(0,0,16,16);
}



void goomba::hit(Object *what, direction fromDir){
    if(died)
        return;
    if(what->name()=="mario"){
        if(fromDir==UP)
        {
            died=true;
            setPixmap(texture_died);
            moveBy(0,6);
            what->hit(this,inverse(fromDir));
            return;
        }
        else{
            what->hit(this,inverse(fromDir));
        }
    }
    if(what->name()=="fireball"){
        died=true;
        setPixmap(texture_walk[0].transformed(QTransform().rotate(180)));
        falling_die=true;
    }
    if(what->name()=="turtle"){
        died=true;
        setPixmap(texture_walk[0].transformed(QTransform().rotate(180)));
        falling_die=true;
    }
}



void goomba::advance()
{
    if(x()-view_x<=200)
        start_moving=true;
    if(!start_moving)
        return;
    if(y()>240)
        remove=true;

    if(died){
        if(falling_die)
        {
            moveBy(0,0.5);
        }
        else{
            died_counting++;
            if(died_counting>=30)
                remove=true;
        }
        return;
    }

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
    setPixmap(texture_walk[((move_counter++)/moving_speed_div)%4]);
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

//direction goomba::collisiondirection(QGraphicsPixmapItem *item)
//{
//    QRectF curr_rect =  sceneBoundingRect();
//        QRectF item_rect =  item->sceneBoundingRect();

//        if(!curr_rect.intersects(item_rect))
//            return UNKNOWN;

//        QRectF interRect = curr_rect.intersected(item_rect);

//        // IR is vertical
//        // --> collision is horizontal
//        if(interRect.width() < interRect.height())
//        {
//            // left side of IR coincides with left side of current rectangle
//            if(interRect.left() == curr_rect.x())
//                return LEFT;
//            else
//                return RIGHT;
//        }
//        // intersection rectangle is horizontal
//        // --> collision is vertical
//        else
//        {
//            // top side of IR coincides with top side of current rectangle
//            if(interRect.top() == curr_rect.y())
//                return UP;
//            else
//                return DOWN;
//        }
//}

void goomba::solveCollisions()
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
                failing=false;
                moveBy(0,-y()-boundingRect().height()+obj->y()+0.01);
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

void goomba::change_direction()
{
    if(dir==RIGHT){
        dir=LEFT;
    }
    else {
        dir=RIGHT;
    }

}


void goomba::fall(bool flag)
{
    failing=flag;
}


QString goomba::name(){
    return QString("goomba");
}
