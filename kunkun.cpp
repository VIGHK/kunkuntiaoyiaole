#include "kunkun.h"
#include "config.h"
#include<QKeyEvent>
Kunkun::Kunkun()
{
    //初始化加载坤坤图片
    k_kunkun.load(KUN_S0);
    k_kunkun1.load(KUN_S1);
    k_kunkun2.load(KUN_S2);
    k_kunkun3.load(KUN_S3);

    //初始化坤坤坐标
    k_x = 150;
    k_y = 200;

    //初始化边框
    //    d_rect.setWidth(d_dinosaur1.width()-75);
    k_rect.setWidth(5);
    k_rect.setHeight(10);        //d_dinosaur1.height()-45);
    k_rect.moveTo(k_x,k_y);

}


void Kunkun::setPosition(int x, int y)
{
    k_x = x;
    k_y = y;
    k_rect.moveTo(k_x,k_y);
}

