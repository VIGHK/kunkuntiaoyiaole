#ifndef CONFIG_H
#define CONFIG_H



//******************游戏配置数据
#define GAME_WIDTH 2400
//图片宽度
#define GAME_HEIGHT 1693//界面高度
#define WIN_LONG 2400 //窗口长度
#define GAME_TITLE "坤坤跳跳乐"//标题

//游戏图标
#define GAME_ICON ":/start.jpg"//  图片加载路径
#define GAME_RATE 10         // 10毫秒刷新一次


//******************坤坤配置数据
#define KUN_S0 ":/kunkun.png"
#define KUN_S1 ":/kunkun.png"
#define KUN_S2 ":/kunkun1.png"
#define KUN_S3 ":/jump.png"


//******************地图配置数据
#define MAP_PATH ":/background.jpg"  //地图路径
#define MAP_SCROLL_SPEED      3     //地图滚动速度2像素


//******************中分配置数据
#define ZHONGFEN_PATH ":/zhongfen.png" // 中分图片路径
#define ZHONGFEN_SPEED 1               // 中分速度
#define ZHONGFEN_NUM 20                // 中分总量
#define ZHONGFEN_INTERVAL 800        // 中分出场间隔


//******************尖叫鸡配置数据
#define JIANJIAOKUN_PATH1 ":/jianjiaokun4.png"   //小尖叫鸡路径
#define JIANJIAOKUN_PATH2 ":/jianjiaokun1.png"   //大尖叫鸡路径
#define JIANJIAOKUN_PATH3 ":/jianjiaokun2.png"   //大中尖叫鸡路径
#define JIANJIAOKUN_PATH4 ":/jianjiaokun3.png"   //大中小尖叫鸡路径

#define JIANJIAOKUN_SPEED 3         //尖叫鸡速度
#define JIANJIAOKUN_NUM 6          //尖叫鸡总量
#define JIANJIAOKUN_INTERVAL 400  //尖叫鸡出场间隔

//******************篮球数据配置
#define BASKETBALL_SPEED 4                // 篮球速度
#define BASKETBALL_INTERVAL 400      //篮球出场间隔
#define BASKETBALL_PATH ":/basketball.png" // 篮球图片路径

//******************其他
#define HIT ":/hit.wav"
#define JUMP ":/jump2.wav"
#define REACH ":/1/reach.wav"
#define RESTART ":/restart.jpg"
#endif // CONFIG_H
