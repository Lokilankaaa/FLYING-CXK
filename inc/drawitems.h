//
// Created by Lokilanka on 2019/5/11.
//

#ifndef C_BIG_WORK_DRAWITEMS_H
#define C_BIG_WORK_DRAWITEMS_H

#include <genlib.h>

#define PI 3.1415926545

/*
 * 三种障碍物类型枚举
 */
typedef enum {
    TRIANGLE,
    PIPE,
    WARNING
} OBSTYPE;

typedef enum {
    BASKETBALL,
    CUREBAG,
    SPEEDDOWN,
    IMMORTAL
} ITEMTYPE;

/*
 * 障碍物属性结构体
 * 类型，坐标，宽度
 */
typedef struct obs {
    OBSTYPE obstacleType;
    double obstacleX;
    double obstacleY;
    double width;
} OBSTACLE;

typedef struct item {
    bool isitem;
    ITEMTYPE itemtype;
    double itemX;
    double itemY;
} ITEM;


/*图标绘制过程中用到的自创函数*/

void LXLforward(double distance, double Angle);

/*
 *沿当前方向画线，长度为distance，当distance为负数时后退(LXL所作图形使用）
 */

void LXLmove(double x, double y, double distance, double Angle);
/*
 *沿当前方向移动笔（不画线），长度为distance，当distance为负数时后退(LXL所作图形使用）
 */

/*图标函数*/

void DrawRoadobstacle(double x, double y, double width, double heigt);

void ClearPreroadobstacle(double x, double y, double width, double height);

/*
 *三角形路障，坐标x,y为三角形最上面的顶点，且为矩形边框最上面一条边的中点，该函数将在长为height，宽为width的矩形中，画出一个三角形红色底色白色条纹路障
 */

void DrawCurebag(double x, double y);

void ClearPrecurebag(double x, double y);

/*
 *十字形治疗包，坐标x,y为十字最左端小方块的左上顶点，十字整体为红色，大小在0.4*0.4的正方形边框之中
 */

void DrawSpeeddown(double x, double y);

void ClearPrespeeddown(double x, double y);

/*
 *两个三角形组成的加速道具，坐标x,y为最左侧三角形的左上顶点，箭头整体为蓝，在0.4*0.4的正方形边框之中
 */

void DrawImmortal(double x, double y);

void ClearPreimmortal(double x, double y);

/*
 *正方形的无敌道具，坐标x,y为正方形的左上顶点，在0.4*0.4的正方形边框中，印有文字律师函警告
 */

void DrawBasketball(double x, double y);

void ClearPrebasketball(double x, double y);

/*
 *画一个半径为0.2的篮球，坐标x,y为篮球的圆心，颜色为橙色，中间有黑色线条
 */

void DrawCxk(double x, double y, int unstoppable);

void ClearpreCxk(double x, double y, int unstoppable);

void DrawCxkHead(double x, double y, int unstoppable);

void DrawCxkBody(double x, double y, int unstoppable);

void DrawCxkTie(double x, double y, int unstoppable);

void DrawCxkLeg(double x, double y, int unstoppable);

void DrawCxkTwo(double x, double y, int unstoppable);

void ClearpreCxkTwo(double x, double y, int unstoppable);

void DrawCxkBodyTwo(double x, double y, int unstoppable);

void DrawCxkTieTwo(double x, double y, int unstoppable);

void DrawCxkLegTwo(double x, double y, int unstoppable);

void DrawLife(double x, double y, int life);

void ClearpreLife(double x, double y, int life);

void DrawColumn(double x, double y, double width, double height);

void ClearPrecolumn(double x, double y, double width, double height);

/*
 * 画一个长为height，宽为width的绿色管道的截面，x,y为长方形的左上顶点
 */

void DrawWarningsign(double x, double y, double width, double height);

void ClearPrewarningsign(double x, double y, double width, double height);
/*
 * 画一个整体高度为height，宽度为width的黄黑色警示牌，整体图形由最上方圆形，中间粗直线，下方矩形组成，x,y为圆形的圆心
 */

void DrawBackground();
/*
 * 画出游戏的背景
 */

#endif //C_BIG_WORK_DRAWITEMS_H
