#include <QWidget>
#include<QMediaPlayer>
#include <QSound>
#include<QKeyEvent>
#include<QIcon>
#include<QPainter>
#include<QPushButton>
#include<QDebug>
#include"basketball.h"
#include<jianjiaokun.h>
#include"mainscene.h"
#include<config.h>
#include<map.h>
#include<kunkun.h>
#include<zhongfen.h>
#include"scene.h"


Mainscene::Mainscene(QWidget *parent)
    : QWidget(parent),  y(1000.0), v(0.0), g(0.06), ground(1200), is_jumping(false), is_releasing(false), last_v(0.0)

    // 构造函数的实现

{
    //调用初始化场景
    initScene();


    //启动游戏
    startgame();
}

Mainscene::~Mainscene()
{
}

void Mainscene::initScene()
{
    //窗口大小

    this->setFixedSize(WIN_LONG, GAME_HEIGHT);

    //标题
    setWindowTitle(GAME_TITLE);

    //图标
    setWindowIcon(QIcon( GAME_ICON));

    //定时器
    m_Timer.setInterval(GAME_RATE);



    //尖叫鸡出现的时间间隔
    m_recorder= 0;

    // 初始化重新开始按钮
    m_restartBtn = new QPushButton(this);
    m_restartBtn->setIcon(QIcon(RESTART));                   // 设置按钮图标
    m_restartBtn->setIconSize(QSize(350, 350));              // 设置图标大小与按钮一致
    m_restartBtn->setFixedSize(350, 350);                    // 设置按钮大小
    m_restartBtn->move(1200, 800);                           // 设置按钮位置
    m_restartBtn->setVisible(false);                         // 默认设置按钮为不可见
    m_restartBtn->setFocusPolicy(Qt::NoFocus);               // 设置按钮不接受焦点

    // 连接信号和槽以便按钮能够触发重启游戏
    connect(m_restartBtn, &QPushButton::clicked, this, &Mainscene::restartGame);

}


void Mainscene::startgame()
{

    m_Timer.start();

    connect(&m_Timer, &QTimer::timeout,[=](){

        jianjiaokunToScene();

        basketballToScene();

       zhongfenToScene();

        updatePosition();

        updateMark();

        update();//重新绘制窗口中所有信息


                if (collisiondDetection()||checkbasketballCollision()) { // 检查碰撞
                    m_gameover --;
                    QSound::play(HIT);
                     if (m_gameover == 0)
                      m_Timer.stop();
                            // 标记游戏结束
                        }
            });
           connect(&m_Timer, SIGNAL(timeout()), this, SLOT(onTimer()));
        }

//重新开始
void Mainscene::restartGame()
{
        mark = 0;
        m_gameover = 1; // 重置游戏结束标志
        y = ground; // 重置角色位置
        v = 0.0; // 重置速度
        is_jumping = false; // 重置跳跃状态
        is_jumping = false;
        is_releasing = false;

        m_restartBtn->setVisible(false);
        // 重新初始化游戏


        //尖叫鸡
        for (int i = 0; i < JIANJIAOKUN_NUM; i++) {
            j_jianjiaokuns[i].j_Free = true;
        }
        //标志是否可用，初始化

        for(int i = 0;i < JIANJIAOKUN_NUM; i++)
        {

                j_jianjiaokuns[i].j_x = -100;

        } //位置初始化


        //篮球
        // 设置篮球为自由状态
        b_basketball.b_Free = true;
        // 设置篮球的位置在屏幕外
        b_basketball.b_x = -100;

        m_Timer.start();

        //尖叫鸡出场
        jianjiaokunToScene();
        basketballToScene();

        //更新元素坐标
        updatePosition();

        //绘制到屏幕中
        update();//重新绘制窗口中所有信息

        if (collisiondDetection()) { // 检查碰撞
                   m_gameover --;
                    if (m_gameover == 0)
                     m_Timer.stop();
                           // 标记游戏结束
                       }
}




void Mainscene::updatePosition()
{
    //更新坐标
    m_map.mapPosition();

    //尖叫鸡
    for(int i = 0;i < JIANJIAOKUN_NUM; i++)
    {
        if(j_jianjiaokuns[i].j_Free == false)
        {
            j_jianjiaokuns[i].updatePosition();
        }
    }

    //篮球
        if(b_basketball.b_Free == false)
        {
           b_basketball.updatePosition();
        }

    //中分
    for(int i = 0;i < ZHONGFEN_NUM; i++)
    {
        if(z_zhongfens[i].z_Free == false)
        {
           z_zhongfens[i].updatePosition();
        }
    }
}

void Mainscene::updateMark()
{
    mark++;
}

void Mainscene::paintEvent(QPaintEvent *)  //绘制
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(m_map.m_map1_posX,0,m_map.m_map1);
    painter.drawPixmap(m_map.m_map2_posX,0,m_map.m_map2);

    //绘制坤坤
    //painter.drawPixmap(k_kunkun.k_x, k_kunkun.k_y, k_kunkun.k_kunkun);
    if (k_kunkun.k_y == ground) {
        static int frame = 0;
        frame++;
        if (frame >= 20) {
            frame = 0;
        }
        if (frame < 10) {
            painter.drawPixmap(k_kunkun.k_x, k_kunkun.k_y, k_kunkun.k_kunkun1);
        } else {
            painter.drawPixmap(k_kunkun.k_x, k_kunkun.k_y, k_kunkun.k_kunkun2);
        }
    }
    else {
        // 在空中时只显示第三张图像
        painter.drawPixmap(k_kunkun.k_x, k_kunkun.k_y, k_kunkun.k_kunkun3);
    }

    //绘制篮球
        if(b_basketball.b_Free == false)
        {
            static int frame = 0;
            frame++;
            if (frame >= 60) {
                frame = 0;
            }
     //绘制篮球，并使其在竖直方向上下浮动
           painter.drawPixmap(b_basketball.b_x,b_basketball.b_y - 90+ (frame%60),b_basketball.b_basketball);
        }

    //绘制尖叫鸡
    for(int i = 0;i < JIANJIAOKUN_NUM; i++)
    {
        if(j_jianjiaokuns[i].j_Free == false)
        {
            painter.drawPixmap(j_jianjiaokuns[i].j_x,j_jianjiaokuns[i].j_y,j_jianjiaokuns[i].j_jianjiaokun1);
        }
    }

    //绘制中分
    for(int i = 0;i < ZHONGFEN_NUM; i++)
    {
        if(z_zhongfens[i].z_Free == false)
        {
            painter.drawPixmap(z_zhongfens[i].z_x,z_zhongfens[i].z_y,z_zhongfens[i].z_zhongfen);
        }
    }




        // 绘制得分
        QFont font;
        font.setPointSize(20);
        painter.setFont(font);
        painter.setPen(Qt::red);
        painter.drawText(rect().adjusted(0, 0, -10, 0), Qt::AlignRight | Qt::AlignTop, QString("Your mark : %1").arg(mark/10));



    if (m_gameover == 0) { // 游戏结束，显示重新开始按钮
            m_restartBtn->setVisible(true);
        } else { // 游戏未结束，隐藏重新开始按钮
            m_restartBtn->setVisible(false);
        }

}

//坤坤的跳跃逻辑
void Mainscene::onTimer()
{
    if (is_jumping) {
        y += v;
        v += g;

        if (y >= ground) {
            y = ground;
            v = -v; // 碰到地面后反弹
            is_jumping = false;
        }
    } else { // 自由落体
        if (y < ground) {
            if (is_releasing && v < 0 && y < last_h) {
                // 继续向上运动
                y += v;
                v += g;
            } else {
                // 自由落体
                y += v;
                v += g;
                if (y >= ground) {
                    y = ground;
                    v = 0.0;
                }
            }
        }
    }

    k_kunkun.setPosition(150, y);
    last_h = y;
}


//按下空格实现跳跃操作
void Mainscene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space && !is_jumping ) {
        QSound::play("");
        //qDebug()<<m_gameover;
    }
    if (event->key() == Qt::Key_Space && !is_jumping && y == ground) {

        is_jumping = true;
        v = -6.5;
        is_releasing = false;
    }
}

void Mainscene::keyReleaseEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Space && is_jumping) {

        is_jumping = false;
        is_releasing = true;
        last_v = v;
    }
}

//尖叫鸡的随机出现
void Mainscene::jianjiaokunToScene()
{
    m_recorder++;
    if(m_recorder <JIANJIAOKUN_INTERVAL)
    {
        return;
    }
//调用次数

    m_recorder = 0;
    //重置计时器

    for(int i = 0;i < JIANJIAOKUN_NUM; i++)
    {
        if(j_jianjiaokuns[i].j_Free==true)
        {
            int type = qrand() % 4 + 1;
            //随机生成尖叫鸡类型
            QPixmap pixmap;

            //根据尖叫鸡类型加载资源并设置属性
            if (type == 1) {
                pixmap.load(JIANJIAOKUN_PATH1);
                j_jianjiaokuns[i].j_Collision.setWidth(15);
                j_jianjiaokuns[i].j_Collision.setHeight(25);
            }

            else if (type == 2) {
                pixmap.load(JIANJIAOKUN_PATH2);
                j_jianjiaokuns[i].j_Collision.setWidth(15);
                j_jianjiaokuns[i].j_Collision.setHeight(25 );
            }

            else if (type == 3) {
                pixmap.load(JIANJIAOKUN_PATH3);
               j_jianjiaokuns[i].j_Collision.setWidth(15);
                j_jianjiaokuns[i].j_Collision.setHeight(25);
            }

            else if (type == 4) {
                pixmap.load(JIANJIAOKUN_PATH4);
                j_jianjiaokuns[i].j_Collision.setWidth(40);
               j_jianjiaokuns[i].j_Collision.setHeight(25);
            }

            //设置尖叫鸡的状态和位置
           j_jianjiaokuns[i].j_jianjiaokun1 = pixmap;
           j_jianjiaokuns[i].j_Free = false;
           j_jianjiaokuns[i].j_x = WIN_LONG + j_jianjiaokuns[i].j_jianjiaokun1.width();
           j_jianjiaokuns[i].j_y = 1500 - j_jianjiaokuns[i].j_jianjiaokun1.height();
            break;
        }
    }
}

void Mainscene::basketballToScene()
{
    b_recorder++;
    if (b_recorder < BASKETBALL_INTERVAL)
    {
        return;
    }
    b_recorder = 0;

    if (b_basketball.b_Free)
    {
        QPixmap pixmap;
        pixmap.load(BASKETBALL_PATH);
        b_basketball.b_basketball = pixmap;
        b_basketball.b_Free = false; // 表明篮球现在在场上
        b_basketball.b_x = WIN_LONG -50; // 确保篮球在窗口内
        b_basketball.b_y = 770;
        // 确保Y坐标合适
    }
}

void Mainscene::zhongfenToScene()
{
    z_recorder++;
    if(z_recorder < ZHONGFEN_INTERVAL)
    {
        return;
    }

    z_recorder = 0;
    //重置计时器
    for(int i = 0;i < ZHONGFEN_NUM; i++)
    {
        if(z_zhongfens[i].z_Free)
        {

            QPixmap pixmap;
            pixmap.load(ZHONGFEN_PATH);


            z_zhongfens[i].z_zhongfen = pixmap;
            z_zhongfens[i].z_Free = false;
            z_zhongfens[i].z_x = WIN_LONG ;
            z_zhongfens[i].z_y = qrand() % 251;
            break;
        }
    }
}


bool Mainscene::collisiondDetection()
{
    QRect dinosaurRect(k_kunkun.k_x, k_kunkun.k_y, k_kunkun.k_kunkun.width(),k_kunkun.k_kunkun.height());
    for (int i = 0; i < JIANJIAOKUN_NUM; i++)
    {
        if (j_jianjiaokuns[i].j_Free == false){
        QRect enermyRect(j_jianjiaokuns[i].j_x, j_jianjiaokuns[i].j_y, j_jianjiaokuns[i].j_jianjiaokun1.width(),j_jianjiaokuns[i].j_jianjiaokun1.height());
        if (dinosaurRect.intersects(enermyRect))
        {
           j_jianjiaokuns[i].j_Free = true;
            return true; // 碰撞检测成功
        }
       }
    }
     return false; // 没有碰撞
}


bool Mainscene::checkbasketballCollision()
{
    QRect dinosaurRect(k_kunkun.k_x, k_kunkun.k_y, k_kunkun.k_kunkun.width(), k_kunkun.k_kunkun.height());

        if (b_basketball.b_Free == false){
        QRect enermyRect(b_basketball.b_x, b_basketball.b_y,b_basketball.b_basketball.width(), b_basketball.b_basketball.height());
        if (dinosaurRect.intersects(enermyRect))
        {
            b_basketball.b_Free = true;
            return true; // 碰撞检测成功
        }
       }
    return false; // 没有碰撞

}
