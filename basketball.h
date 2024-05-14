#ifndef BASKETBALL_H
#define BASKETBALL_H

#include<QPixmap>
#include<QRect>

class Basketball
{
public:
    Basketball();
    void updatePosition();

    // 篮球图片
    QPixmap b_basketball;
    //":/basketball.png"

    // 篮球位置
    int b_x;
    int b_y;

    // 篮球状态
    bool b_Free;

    // 篮球速度
    int b_Speed;

    // 用于碰撞检测的矩形边框
    QRect b_Rect;
};

#endif // BASKETBALL_H
