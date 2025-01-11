#include "box.h"
#include<QDebug>


box::box(int what) {
    store[0]=loadTexture(":/res/box-0.bmp");
    store[1]=loadTexture(":/res/box-1.bmp");
    store[2]=loadTexture(":/res/box-2.bmp");
    store[3]=loadTexture(":/res/box-used.bmp");
    setPixmap(store[state]);
    walkable=true;
    collidable=true;
    type=what;
    setZValue(2);
}

QRectF box::boundingRect()const{
    return QRectF(0,0,16,16);
}

QPainterPath box::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void box::advance(){
    if(!used)
    {
        num++;
        if(num%15==0)
            state++;
        setPixmap(store[state%3]);
        return;
    }
    if(jumping){
        moveBy(0,-moving_speed);
        dy++;
        if(dy>=4)
        {
            jumping=false;
            falling=true;
        }
        return;
    }
    if(falling){
        moveBy(0,moving_speed);
        dy--;
        if(dy==0)
            falling=false;
    }
    return;
}

void box::solveCollisions(){
    return;
}

QString box::name(){
    return QString("box");
}

void box::SetScene(QGraphicsScene *scene)
{
    this->scene=scene;
}

QGraphicsScene *box::GetScene()
{
    return this->scene;
}

void box::hit(Object *what, direction fromDir){
    if(what->name()=="mario"&&fromDir==DOWN&&!used)
    {
        jumping=true;
        used=true;
        setPixmap(store[3]);
        Object* obj;
        if(type==0)
        {
            if(((mario*)what)->large==false){
                obj=new mushroom;
                QGraphicsScene*sc=GetScene();
                sc->addItem(obj);
                obj->setPos(this->x(),this->y()-24);
                return;
            }
            else{
                obj=new flower;
                QGraphicsScene*sc=GetScene();
                sc->addItem(obj);
                obj->setPos(this->x(),this->y());
                return;
            }
        }
        else{
            obj=new money;
            QGraphicsScene*sc=GetScene();
            sc->addItem(obj);
            obj->setPos(this->x(),this->y());
        }
    }
    return;
}
