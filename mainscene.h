#ifndef MAINSCENE_H
#define MAINSCENE_H
#include<QPushButton>
#include <QWidget>
#include<QTimer>
#include<QKeyEvent>
#include<map.h>
#include<kunkun.h>
#include<config.h>
#include<jianjiaokun.h>
#include<zhongfen.h>
#include<basketball.h>
#include <QLineEdit>
#include <QVBoxLayout>
#include"scene.h"

class Mainscene : public QWidget
{
    Q_OBJECT

public:


    Mainscene(QWidget *parent = nullptr);
   // void enableCollisionDetection();
    ~Mainscene();
    //初始化场景
    void initScene();

    //启动游戏
    void startgame();

    //更新游戏元素坐标
    void updatePosition();
    int mark = 0;
    void updateMark();
    //绘制到屏幕中
    void paintEvent(QPaintEvent *);

    //地图对象
    Map m_map;

    //坤坤对象
    Kunkun k_kunkun;
    Kunkun k_kunkun1;
    Kunkun k_kunkun2;
    Kunkun k_kunkun3;

    //篮球对象
    Basketball b_basketball;

    //跳跃判断
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //尖叫鸡出现
    void jianjiaokunToScene();
    Jianjiaokun j_jianjiaokuns[JIANJIAOKUN_NUM];//尖叫鸡数组
    int m_recorder;//尖叫鸡出现间隔

    //篮球出现
    void basketballToScene();
    //Basketball basketball;
    int b_recorder;//篮球出现间隔


    //中分出现
    void zhongfenToScene();
    Zhongfen z_zhongfens[ZHONGFEN_NUM];//中分数组
    int z_recorder;//中分出现间隔

    //碰撞检测
    bool collisiondDetection();
    bool checkbasketballCollision();

    //重新开始
//    void mousePressEvent(QMouseEvent *event);

    //定时器
    QTimer m_Timer;
    //QTimer* m_collisionTimer;


private:
    double y ;         // 坤坤的纵坐标
    double v;          // 坤坤的竖直速度
    const double g;    // 重力加速度
    const int ground;  // 地面的高度
    bool is_jumping;   // 标志坤坤是否正在跳跃
    bool is_releasing;
    double last_v;
    double last_h = 0.0; // 上一次跳跃的高度

    //重新开始按钮
    QPushButton* m_restartBtn;

    int m_gameover = 1;
    void restartGame();

public slots:
    void onTimer();


};
#endif // MAINSCENE_H
