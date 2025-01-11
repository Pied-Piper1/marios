#include "mario.h"
#include<QDebug>

mario::mario(QPoint pos)
{

    texture_walk[0][0]=loadTexture(":/res/mario-small-walk-0.png");
    texture_walk[0][1]=loadTexture(":/res/mario-small-walk-1.png");
    texture_walk[0][2]=loadTexture(":/res/mario-small-walk-2.png");
    texture_walk[1][0]=loadTexture(":/res/mario-big-walk-0.png");
    texture_walk[1][1]=loadTexture(":/res/mario-big-walk-1.png");
    texture_walk[1][2]=loadTexture(":/res/mario-big-walk-2.png");
    texture_stand[0]=loadTexture(":/res/mario-small-stand.png");
    texture_stand[1]=loadTexture(":/res/mario-big-stand.png");
    texture_jump[0]=loadTexture(":/res/mario-small-jump.png");
    texture_jump[1]=loadTexture(":/res/mario-big-jump.png");

    opacityEffect = new QGraphicsOpacityEffect(nullptr);
    this->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(1.0);
    jumping=false;
    movable=false;
    transferming=false;
    failing=false;
    on_bounce=false;
    wudi=false;
    isfireball=false;
    prefallstate=failing;
    grounded=true;
    transformation_counter=2*transf_div;
    dir=RIGHT;
    this->setPixmap(texture_stand[0]);
    this->setPos(pos);
    jump_counter=0;
    init_y=y();
    fail_counter=0;
    moving_speed=1;
    blocked=false;
    move_counter=0;
    wudi_duration=150;
    wudi_counter=0;

    setZValue(4);
}

QRectF mario::boundingRect()const{
    if(large){
        return QRectF(0,0,16,32);
    }
    return QRectF(0,0,16,16);
}

void mario::fall(bool flag)
{
    if(flag&&!jumping){
        failing=true;
    }
    if(!flag){
        failing=false;
    }
}

void mario::jump()
{
    if(jumping)return;
    if(!failing){
        jumping=true;
        if(dir==LEFT){
            this->setPixmap((large)?texture_jump[1].transformed(QTransform().scale(-1,1)):texture_jump[0].transformed(QTransform().scale(-1,1)));
        }
        else {
            this->setPixmap((large)?texture_jump[1]:texture_jump[0]);
        }
    }
}

void mario::move(bool flag)
{
    movable=flag;
}

//void mario::advance(){
//    if(y()>240)
//        remove=true;
//    if(died){
//        setY(y()+failing_speed);
//        return;
//    }
//    if(jumping&&!failing)
//    {
//        setY(y()-jumping_speed);
//        jump_counter+=jumping_speed;
//        if(jump_counter>jump_duration_small)
//        {
//            if(on_bounce){
//                end_bounce();
//            }
//            jumping=false;
//            failing=true;
//            jump_counter=0;
//        }
//        grounded=false;
//    }

//    if(failing)
//    {
//        setY(y()+failing_speed);
//        //        if(y()>=init_y){
//        //            setPos(x(),init_y);
//        //            failing=false;
//        //            grounded=true;
//        //            if(dir==LEFT){
//        //                this->setPixmap(texture_stand[0].transformed(QTransform().scale(-1,1)));
//        //            }
//        //            else {
//        //                this->setPixmap(texture_stand[0]);
//        //            }

//        //        }
//    }
//    if(movable){
//        if(blocked){moving_speed=0;}
//        if(dir==RIGHT){
//            setX(x()+moving_speed);
//            setPixmap((large)?texture_walk[1][move_counter%2]:texture_walk[0][move_counter%2]);
//        }
//        if(dir==LEFT){
//            setX(x()-moving_speed);
//            setPixmap((large)?texture_walk[1][move_counter%2].transformed(QTransform().scale(-1,1)):texture_walk[0][move_counter%2].transformed(QTransform().scale(-1,1)));
//        }
//        move_counter++;
//    }
//    if(!movable){
//        move_counter=0;
//    }
//    if(!movable&&!jumping){
//        if(dir==RIGHT){
//            setPixmap((large)?texture_stand[1]:texture_stand[0]);
//        }
//        if(dir==LEFT){
//            setPixmap((large)?texture_stand[1].transformed(QTransform().scale(-1,1)):texture_stand[0].transformed(QTransform().scale(-1,1)));
//        }

//    }
//    if(wudi){
//        wudi_counter++;
//        opacityEffect->setOpacity((wudi%2)?0.3:1.0);
//        if(wudi_counter>wudi_duration){
//            wudi=false;
//            wudi_counter=0;
//            opacityEffect->setOpacity(1.0);
//        }
//    }

//    moving_speed=store_speed;

//}
void mario::advance(){
//    if(blocked)qDebug()<<"fuck and fuck"<<endl;
    if(y()>240)
        remove=true;
    if(died){
        setY(y()+failing_speed);
        return;
    }
    if(jumping&&!failing)
    {
        jumping_speed-=jump_acceleration;
        bool flag=false;
        if(jumping_speed<=0)
        {

            if(on_bounce)
            {
                end_bounce();
            }
            jumping_speed=0;
            setY(y()-jumping_speed);
            jumping=false;
            failing=true;
            jumping_speed=4.8;
            flag=true;

        }
        if(flag==false)
        {
          setY(y()-jumping_speed);
        }

        //jump_counter+=jumping_speed;
//        if(jump_counter>jump_duration_small)
//        {
//            if(on_bounce){
//                end_bounce();
//            }
//            jumping=false;
//            failing=true;
//            jump_counter=0;
//        }

        grounded=false;
    }

    if(failing)
    {
        falling_speed+=falling_acceleration;
        setY(y()+falling_speed);
        //        if(y()>=init_y){
        //            setPos(x(),init_y);
        //            failing=false;
        //            grounded=true;
        //            if(dir==LEFT){
        //                this->setPixmap(texture_stand[0].transformed(QTransform().scale(-1,1)));
        //            }
        //            else {
        //                this->setPixmap(texture_stand[0]);
        //            }

        //        }
    }
    if(movable){
        if(blocked){moving_speed=0;}
        if(dir==RIGHT){
            if(!blocked){
                moving_speed+=move_acceleration;
                if(moving_speed>=max_move_speed)
                {
                    moving_speed=max_move_speed;
                }
                setX(x()+moving_speed);
                }
            if(change_picture_counter==8)
            {
                if(!jumping)
                    setPixmap((large)?texture_walk[1][move_counter%3]:texture_walk[0][move_counter%3]);
                move_counter++;
                change_picture_counter=0;
            }

        }
        if(dir==LEFT){
            if(!blocked){
                moving_speed+=move_acceleration;
                if(moving_speed>=max_move_speed)
                {
                    moving_speed=max_move_speed;
                }
                setX(x()-moving_speed);
                }
            if(change_picture_counter==8)
            {
                if(!jumping)
                    setPixmap((large)?texture_walk[1][move_counter%3].transformed(QTransform().scale(-1,1)):texture_walk[0][move_counter%3].transformed(QTransform().scale(-1,1)));
                move_counter++;
                change_picture_counter=0;
            }
        }
        change_picture_counter++;
    }
    if(!movable&&moving_speed>0&&!blocked)
    {
        moving_speed-=stop_acceleration;
        if(moving_speed<=0){moving_speed=0;}
        if(dir==RIGHT)
        {
            setX(x()+moving_speed);

            if(change_picture_counter==8)
            {
                setPixmap((large)?texture_walk[1][move_counter%3]:texture_walk[0][move_counter%3]);
                move_counter++;
                change_picture_counter=0;
            }
        }
        if(dir==LEFT)
        {
            setX(x()-moving_speed);
            if(change_picture_counter==8)
            {
                setPixmap((large)?texture_walk[1][move_counter%3].transformed(QTransform().scale(-1,1)):texture_walk[0][move_counter%3].transformed(QTransform().scale(-1,1)));
                move_counter++;
                change_picture_counter=0;
            }
        }
        change_picture_counter++;
    }
    if(!movable&&moving_speed==0){
        move_counter=0;
        change_picture_counter=0;
    }
    if(!movable&&!jumping){
        if(dir==RIGHT){
            setPixmap((large)?texture_stand[1]:texture_stand[0]);
        }
        if(dir==LEFT){
            setPixmap((large)?texture_stand[1].transformed(QTransform().scale(-1,1)):texture_stand[0].transformed(QTransform().scale(-1,1)));
        }

    }
    if(wudi){
        wudi_counter++;
        opacityEffect->setOpacity((wudi%2)?0.3:1.0);
        if(wudi_counter>wudi_duration){
            wudi=false;
            wudi_counter=0;
            opacityEffect->setOpacity(1.0);
        }
    }

    //moving_speed=store_speed;

}

void mario::set_direction(direction direct)
{
    if(dir!=direct){
        dir=direct;
    }
}


void mario::solveCollisions()
{
    if(died)
        return;
    blocked=false;
    failing=true;
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(auto &it :colliding_items){
        Object *obj=dynamic_cast<Object*>(it);
        direction dire=collisionDirection(obj);
        if(obj){
            obj->hit(this,inverse(dire));
            if(dire==UNKNOWN)
                qDebug()<<"falddk";
            if(dire==DOWN&&obj->isWalkable()){
                if(x()<obj->x()+obj->boundingRect().width()-1&&x()+boundingRect().width()>obj->x()+1)
                {
                    failing=false;
                    falling_speed=0;
                    moveBy(0,-y()-boundingRect().height()+obj->y()+0.001);
                }
            }
            if(dire==UP&&obj->isCollidable()){
                jumping=false;
                jump_counter=0;
                jumping_speed=4.8;
            }
            if((dire==RIGHT||dire==LEFT)&&obj->isCollidable()){
                if(dir==dire){
                    if(!wudi&&obj->zValue()!=4)
                    {
                        blocked=true;
                        if(dir==RIGHT)
                            moveBy(-x()-boundingRect().width()+obj->x()+0.01,0);
                        if(dir==LEFT)
                            moveBy(-x()+obj->x()+obj->boundingRect().width()-0.01,0);
                    }
                }
            }

        }
    }
    if(jumping)
    {failing=false;
    falling_speed=0;
    }
}

void mario::Set_Walk_Speed(int speed)
{
    moving_speed=speed;
    store_speed=speed;
}

void mario::endjump()
{
    if(jumping) jumping=false;

}
void mario::start_bounce(){
    jumping=true;
    jumping_speed=2.5;
    jump_counter=0;
    jump_duration_small=10;
    on_bounce=true;
    failing=false;
}
void mario::end_bounce(){
    jumping=false;
    jump_duration_small=70;
    on_bounce=false;
}
QString mario::name(){
    return QString("mario");
}

void mario::hit(Object *what, direction fromDir){
    if(what->name()=="goomba"||what->name()=="turtle")
    {
        if(fromDir!=DOWN)
        {   if(!large&&!wudi)
            {
                died=true;
                remove=true;
                setPixmap(QString(":/res/mario-small-fall.png"));
            }
            if(large){
                large=false;
                isfireball=false;
                wudi=true;
                moveBy(0,16);
                setPixmap(QString(":/res/mario-small-stand.png"));
            }
        }
        else{
            start_bounce();
        }
    }
    if(what->name()=="mushroom"){
        if(fromDir!=DOWN){
            if(!large)
                moveBy(0,-16);
        }
            else
                start_bounce();
        if(large)
            isfireball=true;
        else
            {
            large=true;
            setPixmap(texture_stand[1]);
            }
    }
    if(what->name()=="flower"){
        if(large)
            isfireball=true;
        else
        {
            large=true;
            setPixmap(texture_stand[1]);
        }
    }
}


void mario::SetScene(QGraphicsScene *scene)
{
    this->scene=scene;
}

QGraphicsScene *mario::GetScene()
{
    return this->scene;
}


void mario::burnout(){
    if(!isfireball)
        return;
    fireball* obj=new fireball(dir);
    QGraphicsScene*sc=GetScene();
    sc->addItem(obj);
    if(dir==LEFT)
    obj->setPos(this->x()-8,this->y()+16);
    else
    obj->setPos(this->x()+17,this->y()+16);
}
