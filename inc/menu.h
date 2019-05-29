//
// Created by user on 2019/5/27.
//

#ifndef C_BIG_WORK_MENU_H
#define C_BIG_WORK_MENU_H

void DisplayClear(void);

void drawMenu();

void ShowHelpWindow();

void ShowAboutWindow();

void ShowRank(PLAYERINFO *phead);

void drawButtons();

void EnterName();

void drawGamingButtons();

void ShowGameOver();

void ShowScore(int score);

void ClearScore(int score);

void display();

char *NumberToChar(int n);

void StartInterface();

#endif //C_BIG_WORK_MENU_H
