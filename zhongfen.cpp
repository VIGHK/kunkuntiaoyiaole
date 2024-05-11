#include<zhongfen.h>
#include"config.h"
Zhongfen::Zhongfen()
{
    //资源的加载
    z_zhongfen.load(ZHONGFEN_PATH);

    //尖叫鸡位置
    z_x = 0;
    z_y = 0;

    //尖叫鸡状态
    z_Free = true;

    //尖叫鸡速度
    z_Speed =ZHONGFEN_SPEED;

}


void Zhongfen::updatePosition()
{
    //空闲尖叫鸡状态 不计算坐标
    if (z_Free)
    {
        return;
    }

    z_x -= z_Speed;


    //如果超出屏幕 重置空闲状态
    if (z_x <= - 100)
    {
        z_Free = true;
    }
}
