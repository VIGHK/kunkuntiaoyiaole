#ifndef ZHONGFEN_H
#define ZHONGFEN_H

#include<QPixmap>
#include<QRect>
class Zhongfen
{
public:
    Zhongfen();
    //更新坐标

public:
    void updatePosition();

    QPixmap z_zhongfen;

    //位置
    int z_x;
    int z_y;

    //状态
    bool z_Free;

    //速度
    int z_Speed;
};

#endif
