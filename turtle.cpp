#include "turtle.h"


turtle::turtle(direction dir)
{
    this->dir=dir;
    texture[0]=QPixmap(loadTexture(":/res/turtle-walk-0.png"));
    texture[1]=QPixmap(loadTexture(":/res/turtle-walk-1.png"));
    texture[2]=QPixmap(loadTexture(":/res/turtle-turtleback-0.png"));
    texture[3]=QPixmap(loadTexture(":/res/turtle-turtleback-1.png"));
    if(dir==LEFT)
        setPixmap(texture[0].transformed(QTransform().scale(-1,1)));
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
    walkable=true;
    setZValue(4);
}


QRectF turtle::boundingRect()const{
    if(turtleback||turtleback_2||turtlerotating)
        return QRectF(0,0,16,16);
    return QRectF(0,0,16,24);
}



void turtle::hit(Object *what, direction fromDir){
    if(died)
        return;
    if(turtlerotating)
    {
        return;
    }
    if(what->name()=="mario"){
        if(fromDir==UP)
        {
            if(!turtleback&&!turtleback_2)
            {
                turtleback=true;
                moveBy(0,8);
                setPixmap(texture[2]);
            }
            else{
                if(what->x()<x())
                    dir=RIGHT;
                else
                    dir=LEFT;
                turtlerotating=true;
                setPixmap(texture[2]);
                setZValue(5);
            }
            what->hit(this,inverse(fromDir));
            return;
        }
        else{
            if(!turtleback&&!turtleback_2)
                what->hit(this,inverse(fromDir));
        }
    }
    if(what->name()=="fireball"){
        died=true;
        setPixmap(texture[2].transformed(QTransform().rotate(180)));
    }
    if(what->name()=="turtle"){
        if(((turtle*)what)->turtlerotating)
        {
            died=true;
            setPixmap(texture[2].transformed(QTransform().rotate(180)));
        }
    }
}



void turtle::advance()
{
    if(x()-view_x<=200)
        start_moving=true;
    if(!start_moving)
        return;
    if(y()>240)
        remove=true;

    if(died)
    {
        moveBy(0,0.5);
        return;
    }

    if(turtlerotating&&(x()-view_x<=-300||x()-view_x>=300))
    {
        remove=true;
    }


    if(!turtlerotating){
        if(turtleback){
            if(turtlecount)
                turtlecount--;
            else{
                turtlecount=250;
                turtleback_2=true;
                setPixmap(texture[3]);
                turtleback=false;
            }
            return;
        }

        if(turtleback_2){
            if(turtlecount)
                turtlecount--;
            else{
                turtlecount=250;
                setPixmap(texture[0]);
                moveBy(0,-8);
                turtleback_2=false;
            }
            return;
        }
    }


    solveCollisions();
    if(failing){
        move_speed=0;
        setY(y()+fall_speed);
    }
    if(!failing){
        move_speed=1;
    }

    if(turtlerotating)
    {
        move_speed=4;
        moving=true;
    }

    // move_speed = move_counter % moving_speed_div == 0;
    //    if(blocked){
    //    move_speed=0;
    //    blocked=false;}
    if(!turtlerotating)
    {
        counting++;
        if(counting==3){
            if(dir==LEFT)
                setPixmap(texture[((move_counter++)/moving_speed_div)%2]);
            else
                setPixmap(texture[((move_counter++)/moving_speed_div)%2].transformed(QTransform().scale(-1,1)));
        counting=0;
        }

    }
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

void turtle::solveCollisions()
{
    failing=true;
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(auto it :colliding_items){
        //        Pipe*pip=dynamic_cast<Pipe*>(it);
        //        goomba*goo=dynamic_cast<goomba*>(it);
        Object*obj=dynamic_cast<Object*>(it);
        if(obj&&obj->isCollidable()){
            direction dire=collisionDirection(obj);
            if(turtlerotating)
                obj->hit(this,inverse(dire));
            if((dire==RIGHT||dire==LEFT)&&dir==dire){
                change_direction();
                if(turtlerotating&&obj->zValue()==4)
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

void turtle::change_direction()
{
    if(dir==RIGHT){
        dir=LEFT;
    }
    else {
        dir=RIGHT;
    }

}


void turtle::fall(bool flag)
{
    failing=flag;
}


QString turtle::name(){
    return QString("turtle");
}
