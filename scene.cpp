#include "mainscene.h"
#include "scene.h"
#include <QPushButton>
#include <QDebug>
#include <map.h>
#include <QIcon>
#include <QPainter>
#include <QKeyEvent>
#include <jianjiaokun.h>
#include <kunkun.h>
#include <config.h>
#include <QFont>

Scene::Scene(Mainscene *mainscene, QWidget *parent) : QWidget(parent), mainscene(mainscene)
{
    initScene(); // 初始化场景
    connect(this, &Scene::space_key_pressed, this, &Scene::onSpaceKeyPressed); // 连接信号和槽，仅一次
}

// 析构函数
Scene::~Scene()
{
}

// 初始化场景
void Scene::initScene()
{
    setFixedSize(WIN_LONG, GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
}

// 键盘事件处理
void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        emit space_key_pressed();
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

// 空格键按下时调用的槽
void  Scene::onSpaceKeyPressed()
{
    hide(); // 隐藏当前窗口
    mainscene->show(); // 显示MainScene
}

void Scene::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // 绘制背景图片
    painter.drawPixmap(0, 0, QPixmap(":/background.jpg"));

    //绘制第一张图片
    painter.drawPixmap(150,1300,QPixmap(":/jianjiaokun4"));


    // 绘制第二张图片
    painter.drawPixmap(150, 900, QPixmap(":/jump.png"));

    //绘制第三张图片
    painter.drawPixmap(800,1300,QPixmap(":/jianjiaokun3.png"));

    //绘制第四张图片
    painter.drawPixmap(1550,1300,QPixmap(":/jianjiaokun2.png"));

    //绘制第五张图片
    painter.drawPixmap(2000,1300,QPixmap(":/jianjiaokun2.png"));

    //绘制第六张图片
    painter.drawPixmap(300,400,QPixmap(":/zhongfen.png"));

    //绘制第七张图片
    painter.drawPixmap(500,100,QPixmap(":/zhongfen.png"));

    //绘制第八张图片
    painter.drawPixmap(900,200,QPixmap(":/zhongfen.png"));

    //绘制第九张图片
    painter.drawPixmap(1200,450,QPixmap(":/zhongfen.png"));

    //绘制第十张图片
    painter.drawPixmap(1500,200,QPixmap(":/zhongfen.png"));

    //绘制第十一张图片
    painter.drawPixmap(1900,100,QPixmap(":/zhongfen.png"));

    //绘制第十二张图片
    painter.drawPixmap(2100,400,QPixmap(":/zhongfen.png"));

    //绘制第十三张图片
    painter.drawPixmap(1230,100,QPixmap(":/basketball.png"));

    //绘制第十四张图片
    painter.drawPixmap(2000,900,QPixmap(":/jump.png"));

    //绘制第十五张图片
    painter.drawPixmap(1210,1250,QPixmap(":/kunkun1.png"));

    // 设置字体大小和应用字体
    QFont font = painter.font();
    font.setPointSize(60);
    painter.setFont(font);

    // 获取绘图区域的中心位置并设置对齐方式
    QRect centerRect = rect();  // 获取当前画布的矩形区域
    int textWidth = painter.fontMetrics().horizontalAdvance("按下空格以开始");
    int textHeight = painter.fontMetrics().height();
    centerRect.setHeight(textHeight);  // 将矩形高度设为文字高度，确保垂直居中
    centerRect.setWidth(textWidth);    // 将矩形宽度设为文字宽度，确保水平居中

    // 将绘制文本的区域移至中心
    centerRect.moveCenter(rect().center());

    // 绘制文字
    painter.drawText(centerRect, Qt::AlignCenter, "按下空格以开始");

    // 绘制在文字下方的图片，确保其大小与文字区域相匹配
    QPixmap image(":/start.jpg");
    QPixmap scaledImage = image.scaled(centerRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(centerRect, scaledImage);

    // 重新绘制文字，确保文字在最上层
    painter.drawText(centerRect, Qt::AlignCenter, "按下空格以开始");
}
