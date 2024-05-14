#include"jianjiaokun.h"
#include"config.h"
Jianjiaokun::Jianjiaokun()
{
    //资源的加载
    j_jianjiaokun1.load(JIANJIAOKUN_PATH1);

    //尖叫鸡位置
    j_x = 0;
    j_y = 0;

    //尖叫鸡状态
    j_Free = true;

    //尖叫鸡速度
    j_Speed= JIANJIAOKUN_SPEED;

    //尖叫鸡边框（碰撞检测）
    j_Rect1.setWidth(j_jianjiaokun1.width());
    j_Rect1.setHeight(j_jianjiaokun1.height());
    j_Rect1.moveTo(j_x,j_y-80);

    j_Rect2.setWidth(30);
    j_Rect2.setHeight(15);
    j_Rect2.moveTo(j_x,j_y-80);

    j_Rect3.setWidth(30);
    j_Rect3.setHeight(15);
    j_Rect3.moveTo(j_x,j_y-80);

    j_Rect4.setWidth(80);
    j_Rect4.setHeight(15);
    j_Rect4.moveTo(j_x,j_y-40);
}

void Jianjiaokun::updatePosition()
{
    //空闲尖叫鸡状态 不计算坐标
    if (j_Free){
        return;
    }

    j_x-= j_Speed;
    j_Rect1.moveTo(j_x,j_y);

    //如果超出屏幕 重置空闲状态
   if (j_x <= - j_Rect1.width())
    {
        j_Free = true;
    }
}
