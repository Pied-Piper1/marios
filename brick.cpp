#include "brick.h"

brick::brick() {
    setPixmap(loadTexture(":/res/brick.bmp"));
    walkable=true;
    collidable=true;
    setZValue(2);
}

QRectF brick::boundingRect()const{
    return QRectF(0,0,16,16);
}

QPainterPath brick::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void brick::advance(){
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

void brick::solveCollisions(){
    return;
}

QString brick::name(){
    return QString("brick");
}


void brick::SetScene(QGraphicsScene *scene)
{
    this->scene=scene;
}


QGraphicsScene *brick::GetScene()
{
    return this->scene;
}

void brick::hit(Object *what, direction fromDir){
    if(what->name()=="mario"&&fromDir==DOWN){
        if(((mario*)what)->large)
        {
            remove=true;
            QGraphicsScene*sc=GetScene();
            debris* obj1=new debris(LEFT,UP);
            debris* obj2=new debris(RIGHT,UP);
            debris* obj3=new debris(LEFT,DOWN);
            debris* obj4=new debris(RIGHT,DOWN);
            sc->addItem(obj1);
            sc->addItem(obj2);
            sc->addItem(obj3);
            sc->addItem(obj4);
            obj1->setPos(this->x(),this->y());
            obj2->setPos(this->x()+8,this->y());
            obj3->setPos(this->x(),this->y()+8);
            obj4->setPos(this->x()+8,this->y()+8);
        }
        else
            jumping=true;
    }
    return;
}


