// scene.h

#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QKeyEvent>

class Mainscene; // 前向声明以避免重复包含

class Scene : public QWidget
{
    Q_OBJECT

public:
    // 构造函数和析构函数
    explicit Scene(Mainscene *mainscene, QWidget *parent = nullptr);
    ~Scene();

protected:
    // 键盘和绘图事件
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    // 无参数的自定义信号
    void space_key_pressed();

private slots:
    // 槽函数：响应空格键按下
    void onSpaceKeyPressed();

private:
    // 私有函数：初始化场景
    void initScene();

    // 成员变量：指向主场景的指针
    Mainscene *mainscene;
};

#endif // SCENE_H
