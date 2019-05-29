//
// Created by Lokilanka on 2019/5/11.
//
#include <drawitems.h>
#include "graphics.h"
#include <sysfunction.h>
#include <drawitems.h>
#include <imgui.h>
#include <genlib.h>
#include <extgraph.h>
#include <windows.h>
#include <winnt.h>
#include <random.h>
#include <math.h>
#include <Linkedlist.h>
#include <stdio.h>
#include <string.h>
#include <menu.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "WinMM.Lib")

extern int PlayingGame;
extern int gameover;

PLAYERINFO *data;

/*
 * ???????????
 */
double cx = 5;
double cy = 1.6;

/*
 * ?????????????
 * ????????§Ø?
 * ?§Ø?????§¹?§Ø?
 */
bool ismove = FALSE;// ball
bool isjump = FALSE;// ball
bool Nojudge = FALSE;


/*
 * ????????????????
 */
OBSTACLE obs1, obs2;
/*
 * ???
 */
ITEM item1, item2;

/*
 * ????????¦Æ??????????????????
 */
const double OneFall = 0.15;
const double OneJump = 0.08;

/*
 * ???????????
 */
const double LowHeight = 1;//??????
const double UpperHeight = 3;//??????
const double LowWidth = 0.6;//??????
const double UpperWidth = 1;//??????

/*
 * buff¦Ë??????
 */
const double Lowposition = 1;
const double Upperposition = 6;
/*
 * ???????????
 * ????
 * ?¡Â?
 */
double STDSPEED = 0.05;
double ACCELERATOR = 0;
int LIFE = 3;
int OLDLIFE = 3;
int SCORE = 0;
int TIMESCORE = 0;
char *NAME = NULL;
//int PLAYMUSIC = 1;

void CharEventProcess(char ch) {
    uiGetChar(ch);
    display();
}

void MouseEventProcess(int x, int y, int button, int event) {
    uiGetMouse(x, y, button, event);
    display();
}

void KeyboardEventProcess(int key, int event) {
    uiGetKeyboard(key, event);
    display();
    switch (event) {
        case KEY_DOWN:
            switch (key) {
                case VK_SPACE:
                    if (ismove) {
                        if (isjump) {
                            isjump = FALSE;
                            cancelTimer(FALLINGID);
                            startTimer(JUMPID, JUMPINGINTERVAL);
                            startTimer(AIDJUMPID, AIDJUMPINTERVAL);
                        }
                    }
                    break;
//                case VK_F3:
//                    PLAYMUSIC = 1;
//                    break;
                case VK_F1:
                    if (PlayingGame)
                        PauseGame();
                    break;
                case VK_F2:
                    if (PlayingGame)
                        Resume();
                    break;
//                case VK_F4:
//                    PLAYMUSIC = 0;
//                    break;
                default:
                    break;
            }
            break;
        case KEY_UP:
            switch (key) {
                case VK_SPACE:
                    isjump = TRUE;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void TimerEventProcess(int TID) {
    display();
    switch (TID) {
        case AIDJUMPID:
            if (!JudgeBorder() && !JudgeObstacle()) {
                cancelTimer(JUMPID);
                startTimer(FALLINGID, FALLINGINTERVAL);
                cancelTimer(AIDJUMPID);
            } else {
                cancelTimer(JUMPID);
                cancelTimer(AIDJUMPID);
            }
            break;
        case FALLINGID:
            if (!JudgeBorder() && !JudgeObstacle()) {
                if (ismove) {
                    ClearpreCxkTwo(cx, cy, Nojudge);
                    ClearpreCxk(cx, cy, Nojudge);
                    cy -= OneFall;
                    DrawCxk(cx, cy, Nojudge);
                }
            }
            break;
        case JUMPID:
            if (!JudgeBorder() && !JudgeObstacle()) {
                ClearpreCxk(cx, cy, Nojudge);
                ClearpreCxkTwo(cx, cy, Nojudge);
                cy += OneJump;
                DrawCxkTwo(cx, cy, Nojudge);
            }
            break;
        case ACCELERATIONID:
            if (ACCELERATOR <= 4)
                ACCELERATOR += 0.02;
            break;
        case OBSTACLEMOVEID:
            if (ismove) {
                if (obs1.obstacleX >= 10) {
                    obs1.obstacleType = RandomInteger(0, 2);
                    obs1.obstacleY = RandomReal(LowHeight, UpperHeight);
                    obs1.width = RandomReal(LowWidth, UpperWidth);
                }
                if (obs2.obstacleX >= 10) {
                    obs2.obstacleType = RandomInteger(0, 2);
                    obs2.obstacleY = RandomReal(LowHeight, UpperHeight);
                    obs2.width = RandomReal(LowWidth, UpperWidth);
                }
                switch (obs1.obstacleType) {
                    case TRIANGLE:
                        ClearPreroadobstacle(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                        break;
                    case PIPE:
                        ClearPrecolumn(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                        break;
                    case WARNING:
                        ClearPrewarningsign(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                        break;
                }

                switch (obs2.obstacleType) {
                    case TRIANGLE:
                        ClearPreroadobstacle(obs2.obstacleX, obs2.obstacleY, obs1.width, obs2.obstacleY);
                        break;
                    case PIPE:
                        ClearPrecolumn(obs2.obstacleX, obs2.obstacleY, obs2.width, obs2.obstacleY);
                        break;
                    case WARNING:
                        ClearPrewarningsign(obs2.obstacleX, obs2.obstacleY, obs2.width, obs2.obstacleY);
                        break;
                }
                DrawBackground();
                if (obs1.obstacleX <= 10 && obs1.obstacleX > 5) {
                    obs1.obstacleX -= STDSPEED + ACCELERATOR;
                    switch (obs1.obstacleType) {
                        case TRIANGLE:
                            DrawRoadobstacle(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                            break;
                        case PIPE:
                            DrawColumn(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                            break;
                        case WARNING:
                            DrawWarningsign(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                            break;
                    }
                } else if (obs1.obstacleX <= 5 && obs1.obstacleX > 0) {
                    obs1.obstacleX -= STDSPEED + ACCELERATOR;
                    obs2.obstacleX -= STDSPEED + ACCELERATOR;
                    switch (obs1.obstacleType) {
                        case TRIANGLE:
                            DrawRoadobstacle(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                            break;
                        case PIPE:
                            DrawColumn(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                            break;
                        case WARNING:
                            DrawWarningsign(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                            break;
                    }
                    switch (obs2.obstacleType) {
                        case TRIANGLE:
                            DrawRoadobstacle(obs2.obstacleX, obs2.obstacleY, obs2.width, obs2.obstacleY);
                            break;
                        case PIPE:
                            DrawColumn(obs2.obstacleX, obs2.obstacleY, obs2.width, obs2.obstacleY);
                            break;
                        case WARNING:
                            DrawWarningsign(obs2.obstacleX, obs2.obstacleY, obs2.width, obs2.obstacleY);
                            break;
                    }
                } else if (obs1.obstacleX <= 0) {
                    obs1 = obs2;
                    obs2.obstacleX = 10;
                    obs2.obstacleType = RandomInteger(0, 2);
                    switch (obs1.obstacleType) {
                        case TRIANGLE:
                            DrawRoadobstacle(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                            break;
                        case PIPE:
                            DrawColumn(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                            break;
                        case WARNING:
                            DrawWarningsign(obs1.obstacleX, obs1.obstacleY, obs1.width, obs1.obstacleY);
                            break;
                    }
                }
            }
            break;
        case ITEMMOVINGID:
            if (ismove) {
                if (item1.itemX >= 10) {
                    item1.isitem = RandomInteger(0, 10);
                    if (!item1.isitem) {
                        item1.itemtype = RandomInteger(0, 3);
                        if (obs1.obstacleType == TRIANGLE) {
                            if (item1.itemtype == CUREBAG) {
                                if (item1.itemX >= obs1.obstacleX - 0.3 && item1.itemX < obs1.obstacleX)
                                    item1.itemY = RandomReal(obs1.obstacleY, Upperposition);
                                if (item1.itemX >= obs1.obstacleX - obs1.obstacleY * tan(15 * PI / 180) - 0.3 &&
                                    item1.itemX <= obs1.obstacleX - 0.3)
                                    item1.itemY = RandomReal(
                                            0.2 + tan(75 * PI / 180) * (item1.itemX + 0.3 - obs1.obstacleX) +
                                            obs1.obstacleY, Upperposition);
                                else if (item1.itemX <= obs1.obstacleX + obs1.obstacleY * tan(15 * PI / 180) &&
                                         item1.itemX > obs1.obstacleX)
                                    item1.itemY = RandomReal(
                                            0.2 + obs1.obstacleY -
                                            tan(75 * PI / 180) * (item1.itemX - obs1.obstacleX),
                                            Upperposition);
                                else if (item1.itemX > obs1.obstacleX + obs1.obstacleY * tan(15 * PI / 180) ||
                                         item1.itemX < obs1.obstacleX - 0.3 - obs1.obstacleY * tan(15 * PI / 180))
                                    item1.itemY = RandomReal(Lowposition, Upperposition);
                            } else if (item1.itemtype == BASKETBALL) {
                                if (item1.itemX >= obs1.obstacleX - 0.2 && item1.itemX <= obs1.obstacleX + 0.2)
                                    item1.itemY = RandomReal(obs1.obstacleY, Upperposition);
                                if (item1.itemX >= obs1.obstacleX - obs1.obstacleY * tan(15 * PI / 180) - 0.2 &&
                                    item1.itemX <= obs1.obstacleX - 0.2)
                                    item1.itemY = RandomReal(0.2 + obs1.obstacleY +
                                                             tan(75 * PI / 180) * (item1.itemX + 0.2 - obs1.obstacleX),
                                                             Upperposition);
                                else if (item1.itemX > obs1.obstacleX + 0.2 &&
                                         item1.itemX <= obs1.obstacleX + obs1.obstacleY * tan(15 * PI / 180) + 0.2)
                                    item1.itemY = RandomReal(0.2 + obs1.obstacleY -
                                                             tan(75 * PI / 180) * (item1.itemX - 0.2 - obs1.obstacleX),
                                                             Upperposition);
                                else if (item1.itemX > obs1.obstacleX + obs1.obstacleY * tan(15 * PI / 180) + 0.2 ||
                                         item1.itemX < obs1.obstacleX - obs1.obstacleY * tan(15 * PI / 180) - 0.2)
                                    item1.itemY = RandomReal(Lowposition, Upperposition);
                            } else {
                                if (item1.itemX >= obs1.obstacleX - 0.4 && item1.itemX <= obs1.obstacleX)
                                    item1.itemY = RandomReal(obs1.obstacleY, Upperposition);
                                if (item1.itemX >= obs1.obstacleX - obs1.obstacleY * tan(15 * PI / 180) - 0.4 &&
                                    item1.itemX <= obs1.obstacleX - 0.4)
                                    item1.itemY = RandomReal(0.4 + obs1.obstacleY +
                                                             tan(75 * PI / 180) * (item1.itemX + 0.4 - obs1.obstacleX),
                                                             Upperposition);
                                else if (item1.itemX > obs1.obstacleX &&
                                         item1.itemX <= obs1.obstacleX + obs1.obstacleY * tan(15 * PI / 180))
                                    item1.itemY = RandomReal(0.4 + obs1.obstacleY +
                                                             tan(75 * PI / 180) * (item1.itemX - obs1.obstacleX),
                                                             Upperposition);
                                else if (item1.itemX > obs1.obstacleX + obs1.obstacleY * tan(15 * PI / 180) ||
                                         item1.itemX < obs1.obstacleX - obs1.obstacleY * tan(15 * PI / 180) - 0.4)
                                    item1.itemY = RandomReal(Lowposition, Upperposition);
                            }
                        } else {
                            if (item1.itemtype == CUREBAG) {
                                if (item1.itemX >= obs1.obstacleX - 0.3 && item1.itemX <= obs1.obstacleX + obs1.width)
                                    item1.itemY = RandomReal(obs1.obstacleY + 0.2, Upperposition);
                                else
                                    item1.itemY = RandomReal(Lowposition, Upperposition);
                            } else if (item1.itemtype == BASKETBALL) {
                                if (item1.itemX >= obs1.obstacleX - 0.2 &&
                                    item1.itemX <= obs1.obstacleX + obs1.width + 0.2)
                                    item1.itemY = RandomReal(obs1.obstacleY + 0.2, Upperposition);
                                else
                                    item1.itemY = RandomReal(Lowposition, Upperposition);
                            } else {
                                if (item1.itemX >= obs1.obstacleX - 0.4 && item1.itemX <= obs1.obstacleX + obs1.width)
                                    item1.itemY = RandomReal(obs1.obstacleY + 0.4, Upperposition);
                                else
                                    item1.itemY = RandomReal(Lowposition, Upperposition);
                            }
                        }
                    }
                }

                if (!item1.isitem) {
                    switch (item1.itemtype) {
                        case BASKETBALL:
                            ClearPrebasketball(item1.itemX, item1.itemY);
                            break;
                        case CUREBAG:
                            ClearPrecurebag(item1.itemX, item1.itemY);
                            break;
                        case SPEEDDOWN:
                            ClearPrespeeddown(item1.itemX, item1.itemY);
                            break;
                        case IMMORTAL:
                            ClearPreimmortal(item1.itemX, item1.itemY);
                            break;
                    }
//                    DrawBackground();
                }

                if (item1.itemX <= 10 && item1.itemX >= 1) {
                    if (!item1.isitem) {
                        item1.itemX -= STDSPEED + ACCELERATOR;
//                        DrawBackground();
                        switch (item1.itemtype) {
                            case BASKETBALL:
                                DrawBasketball(item1.itemX, item1.itemY);
                                break;
                            case CUREBAG:
                                DrawCurebag(item1.itemX, item1.itemY);
                                break;
                            case SPEEDDOWN:
                                DrawSpeeddown(item1.itemX, item1.itemY);
                                break;
                            case IMMORTAL:
                                DrawImmortal(item1.itemX, item1.itemY);
                                break;
                        }
                    }
                } else if (item1.itemX <= 1) {
                    item1.itemX = 10;
                }
            }
            break;
        case NOJUDGEID:
            Nojudge = FALSE;
            cancelTimer(NOJUDGEID);
            break;
        case JUDGEITEMID:
            JudgeItem();
            break;
        case LIFEID:
            if (OLDLIFE != LIFE) {
                ClearpreLife(8.8, 7, OLDLIFE);
                DrawLife(8.8, 7, LIFE);
                OLDLIFE = LIFE;
            } else {
                DrawLife(8.8, 7, LIFE);
            }
            break;
        case TIMEID:
            ClearScore(TIMESCORE + 5 * SCORE);
            TIMESCORE++;

            ShowScore(TIMESCORE + 5 * SCORE);
            break;
        default:

            break;
    }
}

bool JudgeBorder() {
    if (cy <= 1.9) {
        ClearpreCxk(cx, cy, Nojudge);
        cy = 1.9;
        DrawCxk(cx, cy, Nojudge);
        return FALSE;
    } else if ((cy >= GetWindowHeight() - 1.1)) {
        ClearpreCxkTwo(cx, cy, Nojudge);
        cy = GetWindowHeight() - 1;
        DrawCxk(cx, cy, Nojudge);
        if (!Nojudge) {
            if (LIFE > 0)
                LIFE--;
            if (!LIFE) {
                GameOver();
                return TRUE;
            } else {
                Nojudge = TRUE;
                startTimer(NOJUDGEID, NOJUDGEINTERVAL);
            }
        }
        return FALSE;
    } else {
        return FALSE;
    }
}

bool JudgeObstacle() {
    if ((cx >= obs1.obstacleX - 0.25 - obs1.obstacleY * tan(15 * PI / 180) + (cy - 1.6) / tan(75 * PI / 180) &&
         cx <= obs1.obstacleX && cy - 1.6 <= obs1.obstacleY) ||
        (cx <= obs1.obstacleX + 0.56 + obs1.obstacleY * tan(15 * PI / 180) - (cy - 1.6) / tan(75 * PI / 180) &&
         cx >= obs1.obstacleX && cy - 1.6 <= obs1.obstacleY)) {
        if (!Nojudge) {
            if (LIFE > 0)
                LIFE--;
            if (!LIFE) {
                GameOver();
                return TRUE;
            } else {
                Nojudge = TRUE;
                startTimer(NOJUDGEID, NOJUDGEINTERVAL);
            }
        }
        return FALSE;
    }
    if ((cx >= obs2.obstacleX - 0.25 - obs2.obstacleY * tan(15 * PI / 180) + (cy - 1.6) / tan(75 * PI / 180) &&
         cx <= obs2.obstacleX && cy - 1.6 <= obs2.obstacleY) ||
        (cx <= obs2.obstacleX + 0.56 + obs2.obstacleY * tan(15 * PI / 180) - (cy - 1.6) / tan(75 * PI / 180) &&
         cx >= obs2.obstacleX && cy - 1.6 <= obs2.obstacleY)) {
        if (!Nojudge) {
            if (LIFE > 0)
                LIFE--;
            if (!LIFE) {
                GameOver();
                return TRUE;
            } else {
                Nojudge = TRUE;
                startTimer(NOJUDGEID, NOJUDGEINTERVAL);
            }
        }
        return FALSE;
    }

    return FALSE;
}

bool JudgeItem() {
    if (item1.itemtype == CUREBAG) {
        if (item1.itemX <= cx + 0.64 && item1.itemX >= cx - 0.94 && item1.itemY <= cy + 0.82 &&
            item1.itemY >= cy - 1.55) {
            ClearPrecurebag(item1.itemX, item1.itemY);
            if (LIFE < 3 && LIFE > 0)
                LIFE++;
            item1.itemX = 10;
        }
    } else if (item1.itemtype == BASKETBALL) {
        if (item1.itemX <= cx + 0.84 && item1.itemX >= cx - 0.84 && item1.itemY <= cy + 0.82 &&
            item1.itemY >= cy - 1.65) {
            ClearPrebasketball(item1.itemX, item1.itemY);
            ClearScore(TIMESCORE + 5 * SCORE);
            SCORE++;
            ShowScore(TIMESCORE + 5 * SCORE);
            item1.itemX = 10;
        }
    } else {
        if (item1.itemX <= cx + 0.64 && item1.itemX >= cx - 1.04 && item1.itemY <= cy + 1.02 &&
            item1.itemY >= cy - 1.45) {
            if (item1.itemtype == SPEEDDOWN) {
                ClearPrespeeddown(item1.itemX, item1.itemY);
                if (ACCELERATOR >= 1)
                    ACCELERATOR--;
                item1.itemX = 10;
            } else {
                ClearPreimmortal(item1.itemX, item1.itemY);
                Nojudge = TRUE;
                startTimer(NOJUDGEID, IMMORTALINTERVAL);
                item1.itemX = 10;
            }
        }

    }
}

void InitGame() {
//    InitGraphics();
//    InitGUI();
    Randomize();
    ismove = isjump = TRUE;
    startTimer(FALLINGID, FALLINGINTERVAL);
    startTimer(OBSTACLEMOVEID, OBSTACLEMOVEINTERVAL);
    startTimer(ACCELERATIONID, ACCELERATEINTERVAL);
    startTimer(ITEMMOVINGID, ITEMMOVINGINTERVAL);
    startTimer(JUDGEITEMID, JUDGEITEMINTERVAL);
    startTimer(LIFEID, SHOWLIFEINTERVAL);
    startTimer(MENUID, MENUINTERVAL);
    startTimer(TIMEID, TIMEINTERVAL);

    obs1.obstacleX = obs2.obstacleX = item1.itemX = 10;
    PlayingGame = 1;
    DrawCxk(GetWindowWidth() / 2, 1.6, Nojudge);
}

void Retry() {
//    DisplayClear();
    gameover = 0;
    PlayingGame = 1;

    startTimer(FALLINGID, FALLINGINTERVAL);
    startTimer(OBSTACLEMOVEID, OBSTACLEMOVEINTERVAL);
    startTimer(ACCELERATIONID, ACCELERATEINTERVAL);
    startTimer(ITEMMOVINGID, ITEMMOVINGINTERVAL);
    startTimer(JUDGEITEMID, JUDGEITEMINTERVAL);
    startTimer(LIFEID, SHOWLIFEINTERVAL);
    startTimer(TIMEID, TIMEINTERVAL);
    ACCELERATOR = 0;
    LIFE = 3;
    SCORE = 0;
    TIMESCORE = 0;

    obs1.obstacleX = obs2.obstacleX = 10;
    item1.itemX = 10;
    ismove = isjump = TRUE;
    Nojudge = FALSE;
    Randomize();
    cx = GetWindowWidth() / 2, cy = 1.6;
    DrawCxk(cx, 1.6, Nojudge);
    DisplayClear();
}

void GameOver() {

    cancelTimer(FALLINGID);
    cancelTimer(OBSTACLEMOVEID);
    cancelTimer(ACCELERATIONID);
    cancelTimer(ITEMMOVINGID);
    cancelTimer(JUDGEITEMID);
    cancelTimer(LIFEID);
    cancelTimer(TIMEID);
    DisplayClear();
    obs1.obstacleX = obs2.obstacleX;
    item1.itemX = 10;
    cy = 3.5;
    ismove = isjump = FALSE;
    Nojudge = TRUE;

    PlayingGame = 0;
    gameover = 1;

    data = UpdateData(data, 5 * SCORE + TIMESCORE, NAME);
}

void PauseGame() {

    cancelTimer(FALLINGID);
    cancelTimer(OBSTACLEMOVEID);
    cancelTimer(ACCELERATIONID);
    cancelTimer(ITEMMOVINGID);
    cancelTimer(JUDGEITEMID);
    cancelTimer(LIFEID);
    cancelTimer(TIMEID);
    ismove = FALSE;
}

void Resume() {
    startTimer(FALLINGID, FALLINGINTERVAL);
    startTimer(OBSTACLEMOVEID, OBSTACLEMOVEINTERVAL);
    startTimer(ACCELERATIONID, ACCELERATEINTERVAL);
    startTimer(ITEMMOVINGID, ITEMMOVINGINTERVAL);
    startTimer(JUDGEITEMID, JUDGEITEMINTERVAL);
    startTimer(LIFEID, SHOWLIFEINTERVAL);
    startTimer(TIMEID, TIMEINTERVAL);
    ismove = TRUE;
}

void DataSave(PLAYERINFO *phead) {
    FILE *fp = NULL;
    PLAYERINFO *cur = phead->next;
    if ((fp = fopen("playerdata.dat", "wb")) != NULL) {
        while (cur) {
            fwrite(&(cur->score), sizeof(int), 1, fp);
            fwrite(&(cur->name), NAMELENGTH * sizeof(char), 1, fp);
            cur = cur->next;
        }
    }
    fclose(fp);
}

PLAYERINFO *DataLoad() {
    FILE *fp;
    PLAYERINFO *phead = CreatenewLinkedlist();
    PLAYERINFO *cur = phead->next;
    if ((fp = fopen("playerdata.dat", "rb")) != NULL) {
        while (!feof(fp)) {
            fread(&(cur->score), sizeof(int), 1, fp);
            fread(&(cur->name), NAMELENGTH * sizeof(char), 1, fp);
            cur = AddLastNode(cur);
        }
    }
    fclose(fp);
    return phead;
}

PLAYERINFO *UpdateData(PLAYERINFO *phead, int Score, char *name) {
    phead = InsertNode(phead, Score, name);
    return phead;
}

