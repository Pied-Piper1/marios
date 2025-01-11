#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "wall.h"
#include <QVBoxLayout>
#include <QString>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include "pipe.h"
#include "mario.h"
#include "background.h"
#include "block.h"
#include "brick.h"
#include "box.h"
#include "goomba.h"
#include "mushroom.h"
#include "fireball.h"
#include "turtle.h"
#include "lift.h"

class view:public QGraphicsView
{

    Q_OBJECT

public:
    view(QGraphicsView *parent=nullptr);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void init_background();
    void add_box(int num,int x,int y);
    void add_brick(int x,int y);
    void add_pipe(int num,int x);
    void add_mush(int num,int x,int y);
    void add_go(int num,int x,int y);
    void add_lift(std::string s,int x);
    void paint();
    void restart();
private:
    QTimer* game_frame;
    QGraphicsScene* scene;
    mario* marios;
    qreal view_x=200;
    int moving_speed=5;
    int view_h=225;
    int view_w=400;
    int cell_length=16;
    int horizon=view_h-cell_length/2*5;//水平面高度
    int game_state=1;                    //0为over，1为start
    QGraphicsTextItem *textItem = new QGraphicsTextItem("Game over!");
};

#endif // VIEW_H
