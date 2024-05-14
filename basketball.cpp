#include "basketball.h"
#include "config.h"

Basketball::Basketball()
{
    // 加载篮球图片
    b_basketball.load(BASKETBALL_PATH);

    // 初始化篮球的位置
    b_x = 100;
    b_y = 300;

    // 设置篮球初始状态为空闲
    b_Free = true;

    // 初始化篮球速度
    b_Speed =BASKETBALL_SPEED;

    // 设置篮球的碰撞检测矩形
    b_Rect.setWidth(20);
    b_Rect.setHeight(20);
    b_Rect.moveTo(b_x, b_y);
}

void Basketball::updatePosition()
{
    // 如果篮球处于空闲状态，则不更新位置
    if (b_Free)
    {
        return;
    }

    // 向左移动篮球
    b_x -= b_Speed;

    // 更新矩形位置用于碰撞检测
    b_Rect.moveTo(b_x, b_y);

    // 如果篮球移出屏幕，则重置为空闲状态
    if (b_x <= -100)
    {
        b_Free = true;
    }
}
