#ifndef MARIO_H
#define MARIO_H
#include <QGraphicsPixmapItem>
#include<QBitmap>
#include<pipe.h>
#include "object.h"
#include <QGraphicsOpacityEffect>
#include<QTimer>
#include <QGraphicsScene>
#include "fireball.h"

class mario:public Object
{
public:
    QString name();
    void hit(Object *what, direction fromDir);
    QRectF boundingRect()const;
    mario(QPoint pos);
    QPixmap texture_walk[2][3];
    QPixmap texture_stand[2];
    QPixmap texture_jump[2];
    QPixmap texture_dead;
    QPixmap texture_small_to_big[4];
    QGraphicsOpacityEffect* opacityEffect = nullptr;
    bool large=false;
    bool jumping;
    bool movable;
    bool transferming;
    direction dir;
    int transformation_counter;
    int transformation_duration;
    int fail_counter;
    int jump_counter;
    int failing_speed;
    int move_counter;
    int wudi_duration;
    int wudi_counter;
    bool failing;
    bool blocked;
    bool prefallstate;
    bool grounded;
    bool on_bounce;
    bool  wudi;
    bool isfireball;
    static const int walk_div    = 6;			// walking animation
    static const int running_div = 4;			// running animation
    static const int transf_div  = 5;

    int jump_duration_tiny  = 30;	// when Mario jumps over enemies
    int jump_duration_small = 70;	// when small Mario jumps
    int jump_duration_big   = 90;

    double max_move_speed=2.0;
    double move_acceleration=0.2;
    double stop_acceleration=0.8;

    double jump_acceleration=0.16;
    double jumping_speed    =4.8;
    double falling_speed=0;
    double falling_acceleration=0.3;
    int change_picture_counter=0;

    void fall(bool flag);
    void jump();
    void start_bounce();
    void end_bounce();
    void starttransfer();
    void endtransfer();
    void animate();
    void move(bool flag);
    void advance();
    void set_direction(direction direct);
    int init_y;
    double moving_speed=0;
    int store_speed;
    direction collisiondirection(QGraphicsPixmapItem*item);
    void solveCollisions();
    void Set_Walk_Speed(int speed);
    void endjump();
    bool strends (std::string const &str, std::string const &end)
    {
        if (str.length() >= end.length())
            return (0 == str.compare (str.length() - end.length(), end.length(), end));
        else
            return false;
    }
    QPixmap loadTextureTransparent(const std::string & file, QColor mask_color = Qt::magenta)
    {
        QPixmap pixmap(file.c_str());
        pixmap.setMask(pixmap.createMaskFromColor(mask_color));
        return pixmap;
    }

    // load texture from image file
    // transparent pixel are identified with the given color
    // if an image format not supporting transparency is used (e.g. like .bmp)
    QPixmap loadTexture(const std::string file, QColor mask_color = Qt::magenta)
    {
        if(strends(file, ".bmp"))
            return loadTextureTransparent(file, mask_color);
        else
            return QPixmap(file.c_str());
    }

    void burnout();
    QGraphicsScene*scene;
    void SetScene(QGraphicsScene*scene);
    QGraphicsScene* GetScene();
};

#endif // MARIO_H
