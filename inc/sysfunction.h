//
// Created by Lokilanka on 2019/5/11.
//

#ifndef C_BIG_WORK_SYSFUNCTION_H
#define C_BIG_WORK_SYSFUNCTION_H

#include <genlib.h>
#include <stdlib.h>
#include <Linkedlist.h>

#define FALLINGINTERVAL 20
#define JUMPINGINTERVAL 10
#define AIDJUMPINTERVAL 300
#define OBSTACLEMOVEINTERVAL 100
#define ACCELERATEINTERVAL 5000
#define ITEMMOVINGINTERVAL 100
#define NOJUDGEINTERVAL 2000
#define JUDGEITEMINTERVAL 1
#define IMMORTALINTERVAL 3000
#define SHOWLIFEINTERVAL 1
#define MENUINTERVAL 1
#define TIMEINTERVAL 1000


typedef enum {
    AIDJUMPID,
    FALLINGID,
    JUMPID,
    OBSTACLEMOVEID,
    ACCELERATIONID,
    ITEMMOVINGID,
    NOJUDGEID,
    JUDGEITEMID,
    LIFEID,
    MENUID,
    TIMEID
} TimerIDD;

void CharEventProcess(char ch);

void MouseEventProcess(int x, int y, int button, int event);

/*
 * 键盘回调函数
 */
void KeyboardEventProcess(int key, int event);

/*
 * 定时器回调函数
 */
void TimerEventProcess(int TID);

/*
 * 上下边界判断函数
 */
bool JudgeBorder();

/*
 * 障碍物碰撞判断函数
 */
bool JudgeObstacle();

/*
 * 物品碰撞判断函数
 */
bool JudgeItem();

/*
 * 初始化游戏
 */
void InitGame();

/*
 * 游戏失败
 */
void GameOver();

/*
 * 重试
 */
void Retry();

/*
 * 暂停游戏
 */
void PauseGame();

/*
 * 继续游戏
 */
void Resume();

/*
 * 游戏保存
 */
void DataSave(PLAYERINFO *phead);

/*
 * 游戏读档
 */
PLAYERINFO *DataLoad();

/*
 * 更新游戏记录
 */
PLAYERINFO *UpdateData(PLAYERINFO *phead, int Score, char *name);

#endif //C_BIG_WORK_SYSFUNCTION_H
