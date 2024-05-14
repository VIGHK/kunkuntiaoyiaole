#ifndef JIANJIAOKUN_H
#define JIANJIAOKUN_H


#include <QPixmap>
#include <QRect>
class Jianjiaokun
{
public:
    Jianjiaokun();

    void updatePosition();

public:
    QPixmap j_jianjiaokun1;
    QPixmap j_jianjiaokun2;
    QPixmap j_jianjiaokun3;
    QPixmap j_jianjiaokun4;
    QRectF  j_Collision;

    //位置
    int j_x;
    int j_y;

    QRect j_Rect1;
    QRect j_Rect2;
    QRect j_Rect3;
    QRect j_Rect4;

    //状态
    bool j_Free;

    //速度
    int j_Speed;

};

#endif // JIANJIAOKUN_H
