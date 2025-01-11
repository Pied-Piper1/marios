#include "view.h"
#include "QIODevice"
#include "QFile"
#include "QTextStream"
#include <chrono>


view::view(QGraphicsView *parent):QGraphicsView(parent)
{
    scene=new QGraphicsScene;
    scene->setSceneRect(0, 0, 10000, 225);
    scene->setBackgroundBrush(QBrush(QColor(99,133,251)));//背景颜色


    init_background();
    paint();

    marios=new mario(QPoint(cell_length*2,view_h-cell_length/2*7));
    scene->addItem(marios);
    marios->SetScene(scene);
    marios->Set_Walk_Speed(moving_speed);
    marios->setPos(cell_length*2,view_h-cell_length/2*7);

    setScene(scene);
    scale(2.0,2.0);
    setFixedHeight(450);
    setFixedWidth(800);
    centerOn(200,112.5);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    //游戏帧
    game_frame=new QTimer(this);
    game_frame->setInterval(20);
    game_frame->start();
    connect(game_frame,&QTimer::timeout,this,[&](){
        if(!game_state)
        {
            game_frame->stop();
            return;
        }
        marios->solveCollisions();
        for(auto &l:scene->items()){
            if(((Object*)l)->isremove())
            {
                if(l!=marios)
                {
                    scene->removeItem(l);
                    delete l;
                }
                else{
                    game_state=0;
                    textItem = new QGraphicsTextItem("Game over!");
                    QFont font;
                    font.setPointSize(24); // 设置字体大小
                    font.setBold(true); // 设置字体加粗
                    textItem->setZValue(20);
                    textItem->setFont(font);
                    textItem->setDefaultTextColor(Qt::white);
                    scene->addItem(textItem);
                    textItem->setPos(view_x-80,112.5-16);
                    return;
                }
                continue;
            }
            if(((Object*)l)->ismoveable())
                ((Object*)l)->view_x=view_x;
            ((Object*)l)->advance();
        }
        if(marios->dir==RIGHT){
            if((marios->x())>=view_x-marios->boundingRect().width()/2)
            {
                view_x+=marios->moving_speed;
                centerOn(view_x,0);
            }
        }
        if(marios->dir==LEFT){
            if(view_x-marios->x()>200)
            {
                marios->setX(view_x-200);
            }
        }
    });

}



void view::restart(){
    scene->clear();

    init_background();
    paint();

    marios=new mario(QPoint(cell_length*2,view_h-cell_length/2*7));
    scene->addItem(marios);
    marios->Set_Walk_Speed(moving_speed);
    marios->SetScene(scene);
    marios->setPos(cell_length*2,view_h-cell_length/2*7);
    centerOn(200,112.5);
    view_x=200;
    game_frame->start();
    game_state=1;
}


void view::keyPressEvent(QKeyEvent *event) {
    if(game_state==0)
    {
        if(event->key()==Qt::Key_R)
            restart();
        return;
    }
    if (event->key() == Qt::Key_D) {
        marios->set_direction(RIGHT);
        marios->move(true);
    }
    if (event->key() == Qt::Key_A) {
        marios->set_direction(LEFT);
        marios->move(true);
    }
    if(event->key()==Qt::Key_Space)
    {
        marios->jump();
    }
    if(event->key()==Qt::Key_Shift)
    {
        marios->burnout();
    }
}


void view::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_D||event->key() == Qt::Key_A)
    {
        marios->move(false);
    }
}


void view::init_background(){
    background* welcome=new background(0);
    scene->addItem(welcome);
    welcome->setPos(10,10);

    //背景贴图
    background* cloud_small[20];
    for(int i=1;i<20;i++){
        if(i%3==2){
            continue;
        }
        cloud_small[i]=new background(6);
        scene->addItem(cloud_small[i]);
        cloud_small[i]->setPos(50+i*200,30);
    }

    background* cloud_mid[20];
    for(int i=0;i<20;i++){
        cloud_mid[i]=new background(7);
        scene->addItem(cloud_mid[i]);
        cloud_mid[i]->setPos(390+i*310,15);
    }

    background* cloud_big[20];
    for(int i=0;i<20;i++){
        cloud_big[i]=new background(8);
        scene->addItem(cloud_big[i]);
        cloud_big[i]->setPos(460+i*450,26);
    }

    background* bash_small[20];
    for(int i=0;i<20;i++){
        if(i%5==4){
            continue;
        }
        bash_small[i]=new background(1);
        scene->addItem(bash_small[i]);
        bash_small[i]->setPos(30+(250+i*5)*i,horizon-cell_length);
    }

    background* bash_mid[20];
    for(int i=0;i<20;i++){
        if(i%3==2){
            continue;
        }
        bash_mid[i]=new background(2);
        scene->addItem(bash_mid[i]);
        bash_mid[i]->setPos(600+(600+i*8)*i,horizon-cell_length);
    }

    background* bash_big[20];
    for(int i=0;i<20;i++){
        if(i%3==2){
            continue;
        }
        bash_big[i]=new background(3);
        scene->addItem(bash_big[i]);
        bash_big[i]->setPos(800+(400+i*10)*i,horizon-cell_length);
    }

    background* hill_big[20];
    for(int i=0;i<20;i++){
        if(i%2==1){
            continue;
        }
        hill_big[i]=new background(5);
        scene->addItem(hill_big[i]);
        hill_big[i]->setPos(350+200*i,horizon-cell_length*2-3);
    }

    background* hill_small[20];
    for(int i=0;i<20;i++){
        if(i%3==2){
            continue;
        }
        hill_small[i]=new background(4);
        scene->addItem(hill_small[i]);
        hill_small[i]->setPos(850+300*i,horizon-cell_length-3);
    }

}

void view::add_box(int num,int x,int y){
    num=num%2;
    box* bo=new box(num);
    bo->SetScene(scene);
    scene->addItem(bo);
    bo->SetScene(scene);
    bo->setPos(cell_length*x,horizon-cell_length*y);
}

void view::add_pipe(int num,int x){
    pipe *pi_2=new pipe(num);
    scene->addItem(pi_2);
    pi_2->setPos(cell_length*x,horizon-(num+1)*cell_length);//水管

}
void view::add_mush(int num,int x,int y){
    if(num==1){
        mushroom* mushroom1=new mushroom;
        scene->addItem(mushroom1);
        mushroom1->setPos(cell_length*x,horizon-cell_length*y);
    }else{
        mushroom* mushroom2=new mushroom;
        scene->addItem(mushroom2);
        mushroom2->setPos(cell_length*x,horizon-cell_length*y);
    }
}

void view::add_brick(int x,int y=4){
    brick* b=new brick;
    scene->addItem(b);
    b->SetScene(scene);
    b->setPos(cell_length*x,horizon-cell_length*y);

}

void view::add_lift(std::string s,int x){
    if(s=="UP"){
        lift* l=new lift(UP);
        scene->addItem(l);
        l->setPos(cell_length*x,horizon-cell_length*5);
    }else{
        lift* l=new lift(DOWN);
        scene->addItem(l);
        l->setPos(cell_length*x,horizon-cell_length*8);
    }

}
void view::paint(){
    for(int i=0;i<1000;i++){
        if(i==20||i==21||i==65||i==66||i==120||i==121||i==175||i==176||i==177||i==225||i==226||i==270||i==271||i==272||i==273||i==274||i==275||i==350||i==351||i==401||i==402||i==470)
            continue;
        wall* p=new wall();
        wall* p2=new wall();
        wall* p3=new wall();
        scene->addItem(p);
        scene->addItem(p2);
        scene->addItem(p3);
        p->setPos(cell_length*i,view_h-cell_length/2);
        p2->setPos(cell_length*i,view_h-cell_length/2*3);
        p3->setPos(cell_length*i,view_h-cell_length/2*5);
    }//地面绘制


    pipe *pi=new pipe(2);
    scene->addItem(pi);
    pi->setPos(cell_length*8,horizon-3*cell_length);//水管


    for(int i=12;i<20;i++){
        for(int j=1;j<i-11;j++)
        {
            block* b=new block;
            scene->addItem(b);
            b->setPos(cell_length*i,horizon-cell_length*j);
        }
    }


    brick * b=new brick;
    scene->addItem(b);
    b->SetScene(scene);
    b->setPos(cell_length*25,horizon-cell_length*4);

    for(int i=27;i<30;i++){
        brick * b1;
        b1=new brick;
        scene->addItem(b1);
        b1->SetScene(scene);
        b1->setPos(cell_length*i,horizon-cell_length*4);
    }


    box* bo=new box(0);
    scene->addItem(bo);
    bo->SetScene(scene);
    bo->setPos(cell_length*26,horizon-cell_length*4);


    box* bos=new box(1);
    scene->addItem(bos);
    bos->SetScene(scene);
    bos->setPos(cell_length*35,horizon-cell_length*4);

    pipe *pi_2=new pipe(1);
    scene->addItem(pi_2);
    pi_2->setPos(cell_length*38,horizon-2*cell_length);//水管

    pipe *pi_3=new pipe(2);
    scene->addItem(pi_3);
    pi_3->setPos(cell_length*43,horizon-3*cell_length);//水管

    pipe *pi_4=new pipe(3);
    scene->addItem(pi_4);
    pi_4->setPos(cell_length*48,horizon-4*cell_length);//水管

    add_box(1,53,4);

    for(int i=56;i<61;i++){
        if(i%2==1){
            add_box(1,i,4);
            continue;
        }
        b=new brick;
        scene->addItem(b);
        b->SetScene(scene);
        b->setPos(cell_length*i,horizon-cell_length*4);
    }
    add_box(0,58,7);
    add_pipe(1,69);

    goomba* gooma11=new goomba(RIGHT);
    gooma11->setPos(cell_length*70,horizon-4*cell_length);
    scene->addItem(gooma11);

    add_pipe(2,75);
    for(int i=79;i<87;i++){
        for(int j=1;j<i-78;j++)
        {
            block* b=new block;
            scene->addItem(b);
            b->setPos(cell_length*i,horizon-cell_length*j);
        }
    }

    add_box(0,92,4);
    for(int i=95;i<100;i++){
        brick*b2;
        b2=new brick;
        scene->addItem(b2);
        b2->SetScene(scene);
        b2->setPos(cell_length*i,horizon-cell_length*4);
    }
    add_box(1,98,7);
    goomba* goma11=new goomba(RIGHT);
    goma11->setPos(cell_length*102,horizon-4*cell_length);
    scene->addItem(goma11);

    add_brick(102,4);
    add_box(1,103,4);
    add_brick(104,4);

    for (int i=105;i<110;i++) {
        add_brick(i,7);
    }

    add_pipe(3,115);

    add_lift("UP",127);
    for(int i=130;i<=136;i++){
        if(i==133||i==135){
            add_box(1,i,9);
        }
        brick*b2;
        b2=new brick;
        scene->addItem(b2);
        b2->SetScene(scene);
        b2->setPos(cell_length*i,horizon-cell_length*6);
    }
    turtle* t3=new turtle(LEFT);
    t3->setPos(cell_length*134,horizon-5*cell_length);
    scene->addItem(t3);
    for(int i=143;i<152;i++){
        for(int j=1;j<i-142;j++)
        {
            block* b=new block;
            scene->addItem(b);
            b->setPos(cell_length*i,horizon-cell_length*j);
        }
    }
    add_pipe(1,156);

    goomba* goomba11=new goomba(RIGHT);
    goomba11->setPos(cell_length*160,horizon-4*cell_length);
    scene->addItem(goomba11);

    add_pipe(2,164);

    turtle* t1=new turtle(LEFT);
    t1->setPos(cell_length*166,horizon-5*cell_length);
    scene->addItem(t1);

    add_pipe(3,170);

    add_brick(180,4);
    add_box(1,181,4);
    add_brick(182,4);
    add_brick(183,4);
    add_brick(184,4);
    add_brick(185,4);

    for(int i=186;i<=191;i++){
        brick*b2;
        b2=new brick;
        scene->addItem(b2);
        b2->SetScene(scene);
        b2->setPos(cell_length*i,horizon-cell_length*8);
    }
    add_lift("down",193);





    auto now = std::chrono::high_resolution_clock::now();
    unsigned seed = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    srand(seed);

    // 随机添加水管和敌人
    int no_tur=0;
    int no_mush=0;
    for(int i = 200; i < 1000; i++) {
        if((i==20||i==21||i==65||i==66||i==120||i==121||i==225||i==226||i==270||i==271||i==272||i==273||i==274||i==275||i==350||i==351||i==401||i==402||i==470)==true){
            continue;
        }
        int randNum = rand() % 100;

        if(randNum < 12) { // 15%的几率添加一个水管
            int pipe_height = rand() % 3 + 1;  // 随机选择水管高度
            add_pipe(pipe_height, i);
            i+=5;
            continue;
        }

        if(randNum >= 15 && randNum < 22) { // 10%的几率添加一个goomba
            if(i-no_mush<12){
                continue;
            }
            goomba* goomba1 = new goomba(RIGHT);
            goomba1->setPos(cell_length * i, horizon - 4 * cell_length);
            scene->addItem(goomba1);
            no_mush=i;
            randNum = rand() % 100;
        }

        if(randNum >= 25 && randNum < 31) { // 10%的几率添加一个turtle
            if(i-no_tur<10){
                continue;
            }
            turtle* t = new turtle(LEFT);
            t->setPos(cell_length * i, horizon - 5 * cell_length);
            scene->addItem(t);
            no_tur=i;
            randNum = rand() % 100;
            continue;
        }

        if(randNum > 34&&randNum<37) { // 5%的几率添加一个单独的box
            box* soloBox = new box(0);
            scene->addItem(soloBox);
            soloBox->setPos(cell_length * i, horizon - cell_length * 3); // 随机高度
            continue;
        }
        if(randNum>94){
            brick* b1 = new brick();
            box* bx1 = new box(0);
            brick* b2 = new brick();
            box* bx2 = new box(0);
            brick* b3 = new brick();

            scene->addItem(b1);
            scene->addItem(bx1);
            scene->addItem(b2);
            scene->addItem(bx2);
            scene->addItem(b3);

            b1->setPos(cell_length * i, horizon - cell_length * 5);
            bx1->setPos(cell_length * (i + 1), horizon - cell_length * 5);
            b2->setPos(cell_length * (i + 2), horizon - cell_length * 5);
            bx2->setPos(cell_length * (i + 3), horizon - cell_length * 5);
            b3->setPos(cell_length * (i + 4), horizon - cell_length * 5);
        }
        if(randNum%30==1){
            add_mush(randNum%7,i,5);
        }

    }


    goomba* goomba1=new goomba(RIGHT);
    goomba1->setPos(cell_length*8,horizon-4*cell_length);
    scene->addItem(goomba1);


    turtle* t=new turtle(LEFT);
    t->setPos(cell_length*50,horizon-5*cell_length);
    scene->addItem(t);

    mushroom* mushroom1=new mushroom;
    scene->addItem(mushroom1);
    mushroom1->setPos(cell_length*26,horizon-cell_length*5);

    // mushroom* mushroom2=new mushroom;
    // scene->addItem(mushroom2);
    // mushroom2->setPos(cell_length*9,horizon-cell_length*5);


    lift* l=new lift(UP);
    scene->addItem(l);
    l->setPos(cell_length*52,horizon-cell_length*5);
}




