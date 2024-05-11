#ifndef kunkun_H
#define kunkun_H


#include<QPixmap>
#include<QRect>
#include<QKeyEvent>
class Kunkun
{
public:
    Kunkun();

    void setPosition(int x,int y);


    QPixmap k_kunkun1;
    QPixmap k_kunkun2;
    QPixmap k_kunkun3;

    int k_x;
    int k_y;



    QRect k_rect;
};

#endif
