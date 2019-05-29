//
// Created by Lokilanka on 2019/5/11.
//

#include "drawitems.h"
#include <graphics.h>
#include <extgraph.h>
#include <stdlib.h>
#include <math.h>


void LXLforward(double distance, double Angle) {
    if (distance > 0)
        DrawLine(distance * cos((PI * Angle / 180)), distance * sin((PI * Angle / 180)));
    else
        DrawLine(-distance * cos((PI * Angle / 180)), -distance * sin((PI * Angle / 180)));
}

void LXLmove(double x, double y, double distance, double Angle) {
    MovePen(x + distance * cos((PI * Angle / 180)), y + distance * sin((PI * Angle / 180)));
}


void DrawRoadobstacle(double x, double y, double width, double height) {
    DefineColor("Red", 1, 0, 0);
    SetPenColor("Red");
    StartFilledRegion(1);
    MovePen(x, y);
    double angle = 0;
    angle -= 75;
    LXLforward(height / sin(PI * 75 / 180), angle);
    angle -= 105;
    LXLforward(2 * height / tan(PI * 75 / 180), angle);
    angle -= 105;
    LXLforward(height / sin(PI * 75 / 180), angle);
    EndFilledRegion();
    DefineColor("white", 1, 1, 1);
    SetPenColor("white");
    MovePen(x, y);
    StartFilledRegion(1);
    MovePen(x - 0.5 * height / tan(PI * 75 / 180), y - 0.5 * height);
    angle = 0;
    LXLforward(height / tan(PI * 75 / 180), angle);
    angle -= 75;
    LXLforward(0.125 * height / sin(PI * 75 / 180), angle);
    angle -= 105;
    LXLforward(5 * height / (4 * tan(PI * 75 / 180)), angle);
    angle -= 105;
    LXLforward(0.125 * height / sin(PI * 75 / 180), angle);
    EndFilledRegion();
    MovePen(x, y);
    StartFilledRegion(1);
    MovePen(x - 0.75 * height / tan(PI * 75 / 180), y - 0.75 * height);
    angle = 0;
    LXLforward(3 * height / (2 * tan(PI * 75 / 180)), angle);
    angle -= 75;
    LXLforward(0.125 * height / sin(PI * 75 / 180), angle);
    angle -= 105;
    LXLforward(7 * height / (4 * tan(PI * 75 / 180)), angle);
    angle -= 105;
    LXLforward(0.125 * height / sin(PI * 75 / 180), angle);
    EndFilledRegion();
    DefineColor("Black", 0, 0, 0);
    SetPenColor("Black");
    MovePen(x, y);
    angle = 0;
    angle -= 75;
    LXLforward(height / sin(PI * 75 / 180), angle);
    angle -= 105;
    LXLforward(2 * height / tan(PI * 75 / 180), angle);
    angle -= 105;
    LXLforward(height / sin(PI * 75 / 180), angle);
}

void ClearPreroadobstacle(double x, double y, double width, double height) {
    SetEraseMode(TRUE);
    DrawRoadobstacle(x, y, width, height);
    SetEraseMode(FALSE);
}

void DrawCurebag(double x, double y) {
    DefineColor("Red", 1, 0, 0);
    SetPenColor("Red");
    StartFilledRegion(1);
    MovePen(x, y);
    DrawLine(0.1, 0);
    DrawLine(0, 0.1);
    DrawLine(0.1, 0);
    DrawLine(0, -0.1);
    DrawLine(0.1, 0);
    DrawLine(0, -0.1);
    DrawLine(-0.1, 0);
    DrawLine(0, -0.1);
    DrawLine(-0.1, 0);
    DrawLine(0, 0.1);
    DrawLine(-0.1, 0);
    DrawLine(0, 0.1);
    EndFilledRegion();
    DefineColor("Black", 0, 0, 0);
    SetPenColor("Black");
    MovePen(x, y);
    DrawLine(0.1, 0);
    DrawLine(0, 0.1);
    DrawLine(0.1, 0);
    DrawLine(0, -0.1);
    DrawLine(0.1, 0);
    DrawLine(0, -0.1);
    DrawLine(-0.1, 0);
    DrawLine(0, -0.1);
    DrawLine(-0.1, 0);
    DrawLine(0, 0.1);
    DrawLine(-0.1, 0);
    DrawLine(0, 0.1);
}

void ClearPrecurebag(double x, double y) {
    SetEraseMode(TRUE);
    DrawCurebag(x, y);
    SetEraseMode(FALSE);
}

void DrawSpeeddown(double x, double y) {
    DefineColor("Blue", 0, 0, 1);
    SetPenColor("Blue");
    StartFilledRegion(1);
    MovePen(x, y);
    DrawLine(0.2, 0.2);
    DrawLine(0, -0.4);
    DrawLine(-0.2, 0.2);
    EndFilledRegion();
    StartFilledRegion(1);
    MovePen(x + 0.2, y);
    DrawLine(0.2, 0.2);
    DrawLine(0, -0.4);
    DrawLine(-0.2, 0.2);
    EndFilledRegion();
    DefineColor("Black", 0, 0, 0);
    SetPenColor("Black");
    MovePen(x, y);
    DrawLine(0.2, 0.2);
    DrawLine(0, -0.4);
    DrawLine(-0.2, 0.2);
    MovePen(x + 0.2, y);
    DrawLine(0.2, 0.2);
    DrawLine(0, -0.4);
    DrawLine(-0.2, 0.2);
}

void ClearPrespeeddown(double x, double y) {
    SetEraseMode(TRUE);
    DrawSpeeddown(x, y);
    SetEraseMode(FALSE);
}

void DrawImmortal(double x, double y) {
    SetPointSize(15);
    MovePen(x, y);
    DrawLine(0.5, 0);
    DrawLine(0, -0.5);
    DrawLine(-0.5, 0);
    DrawLine(0, 0.5);
    MovePen(x, y - 0.25);
    DefineColor("Red", 1, 0, 0);
    SetPenColor("Red");
    DrawTextString("律师函");
    MovePen(x, y - 0.4);
    DrawTextString("  警告");
}

void ClearPreimmortal(double x, double y) {
    SetEraseMode(TRUE);
    DrawImmortal(x, y);
    SetEraseMode(FALSE);
}

void DrawBasketball(double x, double y) {
    DefineColor("Orange", 1, .40, .1);
    DefineColor("Black", 0, 0, 0);
    SetPenColor("Orange");
    StartFilledRegion(1);
    MovePen(x + 0.2, y);
    DrawArc(0.2, 0, 360);
    EndFilledRegion();
    SetPenColor("Black");
    MovePen(x - 0.2, y);
    DrawLine(0.4, 0);
    MovePen(x, y - 0.2);
    DrawLine(0, 0.4);
    MovePen(x - 0.05 * 3.464101615, y + 0.1);
    DrawArc(0.2, 30, -60);
    MovePen(x + 0.05 * 3.464101615, y + 0.1);
    DrawArc(0.2, 150, 60);
    MovePen(x + 0.22, y);
    DrawArc(0.21, 0, 360);
}

void ClearPrebasketball(double x, double y) {
    SetEraseMode(TRUE);
    DrawBasketball(x, y);
    SetEraseMode(FALSE);
}


void DrawCxk(double x, double y, int unstoppable) {
    DrawCxkHead(x, y, unstoppable);
    DrawCxkBody(x, y, unstoppable);
    DrawCxkLeg(x, y, unstoppable);
    DrawCxkTie(x, y, unstoppable);
}

void ClearpreCxk(double x, double y, int unstoppable) {
    SetEraseMode(TRUE);
    DrawCxk(x, y, unstoppable);
    SetEraseMode(FALSE);
}

void DrawCxkHead(double x, double y, int unstoppable) {
    SetPenColor("Gray");
    StartFilledRegion(1);
    MovePen(x, y);
    DrawArc(0.32, 270, 360);
    EndFilledRegion();
    if (unstoppable)
        SetPenColor("Yellow");
    else
        SetPenColor("Red");
    MovePen(x - 0.1, y + 0.25);
    DrawTextString("美");
    SetPenColor("Black");
}
//cxk的头，附带美字

void DrawCxkBody(double x, double y, int unstoppable) {
    if (unstoppable)
        SetPenColor("Yellow");
    else
        SetPenColor("Green");
    //StartFilledRegion(1);
    MovePen(x - 0.48, y + 0.12);
    DrawLine(0.96, -0.24);
    MovePen(x - 0.48, y + 0.12);
    DrawLine(-0.15, -0.6);
    DrawLine(0.24, -0.06);
    MovePen(x + 0.48, y - 0.12);
    DrawLine(-0.15, -0.6);
    DrawLine(-0.24, 0.06);
    MovePen(x - 0.3, y + 0.075);
    DrawLine(-0.225, -0.9);
    MovePen(x + 0.3, y - 0.075);
    DrawLine(-0.18, -0.75);
    DrawLine(-0.65, 0);
    //EndFilledRegion();
    SetPenColor("Black");
}
//cxk身体

void DrawCxkLeg(double x, double y, int unstoppable) {
    if (unstoppable)
        SetPenColor("Yellow");
    else
        SetPenColor("Brown");
    //StartFilledRegion(1);
    MovePen(x - 0.525, y - 0.825);
    DrawLine(0, -0.6);
    DrawLine(0.15, 0);
    DrawEllipticalArc(0.18, 0.4, 180, -180);
    MovePen(x + 0.11, y - 0.825);
    DrawLine(0, -0.6);
    DrawLine(-0.15, 0);
    //EndFilledRegion();
    SetPenColor("Black");
}
//cxk脚部

void DrawCxkTie(double x, double y, int unstoppable) {
    if (unstoppable)
        SetPenColor("Yellow");
    else
        SetPenColor("Black");
    //StartFilledRegion(1);
    MovePen(x - 0.3, y + 0.075);
    DrawLine(0.075, -0.6);
    DrawLine(-0.075, -0.3);
    MovePen(x + 0.3, y - 0.075);
    DrawLine(-0.375, -0.525);
    DrawLine(-0.06, -0.225);
    MovePen(x - 0.225, y + 0.055);
    DrawLine(0.09, -0.54);
    DrawLine(0.36, 0.44);
    //EndFilledRegion();
    SetPenColor("Black");
}
//cxk白带部分


void DrawCxkTwo(double x, double y, int unstoppable) {
    DrawCxkHead(x, y, unstoppable);
    DrawCxkBodyTwo(x, y, unstoppable);
    DrawCxkTieTwo(x, y, unstoppable);
    //腿部函数参数有变化↓
    DrawCxkLegTwo(x - 0.35, y - 0.9, unstoppable);
}

void ClearpreCxkTwo(double x, double y, int unstoppable) {
    SetEraseMode(TRUE);
    DrawCxkTwo(x, y, unstoppable);
    SetEraseMode(FALSE);
}

void DrawCxkBodyTwo(double x, double y, int unstoppable) {
    if (unstoppable)
        SetPenColor("Yellow");
    else
        SetPenColor("Green");
    MovePen(x - 0.5, y);
    DrawLine(1, 0);
    MovePen(x - 0.5, y);
    DrawArc(1.2, 0, 30);
    DrawLine(0.15, 0);
    DrawArc(1.2, 30, -30);
    DrawLine(0, -0.9);
    DrawLine(0.7, 0);
    DrawLine(0, 0.9);
    DrawArc(1.2, 180, 30);
    DrawLine(0.15, 0);
    DrawArc(1.2, 210, -30);
    SetPenColor("Black");
}

void DrawCxkTieTwo(double x, double y, int unstoppable) {
    if (unstoppable)
        SetPenColor("Yellow");
    else
        SetPenColor("Black");
    MovePen(x - 0.35, y);
    DrawLine(0.25, -0.5);
    DrawLine(0.01, -0.4);
    MovePen(x + 0.35, y);
    DrawLine(-0.25, -0.5);
    DrawLine(-0.01, -0.4);
    MovePen(x - 0.2, y);
    DrawLine(0.2, -0.4);
    DrawLine(0.2, 0.4);
    SetPenColor("Black");
}

void DrawCxkLegTwo(double x, double y, int unstoppable) {
    if (unstoppable)
        SetPenColor("Yellow");
    else
        SetPenColor("Black");
    MovePen(x, y);
    DrawLine(0.05, -0.35);
    DrawLine(-0.3, 0);
    DrawLine(0, -0.18);
    DrawLine(0.56, 0);
    DrawLine(0, 0.55);
    MovePen(x + 0.7, y);
    DrawLine(0, -0.53);
    DrawLine(-0.4, 0);
    MovePen(x + 0.4, y);
    DrawLine(0.05, -0.35);
    DrawLine(-0.15, 0);
    SetPenColor("Black");
}

void DrawColumn(double x, double y, double width, double height) {
    DefineColor("Black", 0, 0, 0);
    DefineColor("FGreen", 0, 0.9, 0);
    SetPenColor("FGreen");
    StartFilledRegion(1);
    MovePen(x, y);
    DrawLine(0.1 * width, 0);
    DrawLine(0, -0.25 * height);
    DrawLine(-0.1 * width, 0);
    DrawLine(0, 0.25 * height);
    EndFilledRegion();
    StartFilledRegion(1);
    MovePen(x + 0.2 * width, y);
    DrawLine(0.8 * width, 0);
    DrawLine(0, -0.25 * height);
    DrawLine(-0.8 * width, 0);
    DrawLine(0, 0.25 * height);
    EndFilledRegion();
    StartFilledRegion(1);
    MovePen(x, y - 0.25 * height);
    DrawLine(0.2 * width, 0);
    DrawLine(0, -0.75 * height);
    DrawLine(-0.2 * width, 0);
    DrawLine(0, 0.75 * height);
    EndFilledRegion();
    StartFilledRegion(1);
    MovePen(x + 0.3 * width, y - 0.25 * height);
    DrawLine(0.7 * width, 0);
    DrawLine(0, -0.75 * height);
    DrawLine(-0.7 * width, 0);
    DrawLine(0, 0.75 * height);
    EndFilledRegion();
    SetPenColor("Black");
    MovePen(x, y);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
    DrawLine(0, height);

    MovePen(x, y - 0.25 * height);
    DrawLine(width, 0);
    MovePen(x + width, y);
    DrawLine(0, -0.25 * height);

//    SetPenSize(4);
    DrawLine(0, -0.75 * height);
}

void ClearPrecolumn(double x, double y, double width, double height) {
    SetEraseMode(TRUE);
    DrawColumn(x, y, width, height);
    SetEraseMode(FALSE);
}

void DrawWarningsign(double x, double y, double width, double height) {
    SetPointSize(15);
    MovePen(x + 0.5 * width, y - 0.5 * width);
    DefineColor("Yellow", 1, 1, 0);
    DefineColor("Black", 0, 0, 0);
    SetPenColor("Black");
    StartFilledRegion(1);
    DrawArc(0.5 * width, 0, 360);
    EndFilledRegion();
    MovePen(x + 0.5 * width + 0.02, y - 0.5 * width);
    DrawArc(0.5 * width, 0, 360);
    MovePen(x + 0.8 * 0.5 * width, y - 0.5 * width);
    SetPenColor("Yellow");
    StartFilledRegion(1);
    DrawArc(0.8 * 0.5 * width, 0, 360);
    EndFilledRegion();
    SetPenColor("Black");
    MovePen(x + 0.5 * width, y - 0.5 * width);
    DrawArc(0.5 * width, 0, 360);
    MovePen(x - 0.4 * width, y - 0.5 * width);
    DrawTextString("  鸡你太");
    MovePen(x - 0.4 * width, y - 0.7 * width);
    DrawTextString("      丑");
    MovePen(x, y - width);
    SetPenSize(1);
    int i = 1;
    while (i <= 5) {
        if (i == 1 || i == 3 || i == 5) {
            SetPenColor("Black");
            DrawLine(0, 0.2 * (-height + 1.1 * width));
            i++;
        } else {
            SetPenColor("Yellow");
            DrawLine(0, 0.2 * (-height + 1.1 * width));
            i++;
        }
    }
    SetPenSize(1);
    SetPenColor("Black");
    StartFilledRegion(1);
    DrawLine(0.5 * width, 0);
    DrawLine(0, -0.1 * width);
    DrawLine(-width, 0);
    DrawLine(0, 0.1 * width);
    DrawLine(0.5 * width, 0);
    EndFilledRegion();
    DrawLine(0.5 * width, 0);
    DrawLine(0, -0.1 * width);
    DrawLine(-width, 0);
    DrawLine(0, 0.1 * width);
    DrawLine(0.5 * width, 0);
}


void ClearPrewarningsign(double x, double y, double width, double height) {
    SetEraseMode(TRUE);
    DrawWarningsign(x, y, width, height);
    SetEraseMode(FALSE);
}

//绘制血条函数，life为人物生命值
void DrawLife(double x, double y, int life) {
    if (life != 1 && life != 2 && life != 3)
        return;
    else {
        StartFilledRegion(1);
        SetPenColor("Red");
        MovePen(x, y);
        DrawLine(0.4 * life, 0);
        DrawLine(0, -0.3);
        DrawLine(-0.4 * life, 0);
        DrawLine(0, 0.3);
        EndFilledRegion();
    }
    SetPenColor("Black");
    MovePen(x, y);
    DrawLine(1.2, 0);
    DrawLine(0, -0.3);
    DrawLine(-1.2, 0);
    DrawLine(0, 0.3);
    MovePen(x + 0.4, y);
    DrawLine(0, -0.3);
    MovePen(x + 0.8, y);
    DrawLine(0, -0.3);
}

void ClearpreLife(double x, double y, int life) {
    SetEraseMode(TRUE);
    DrawLife(x, y, life);
    SetEraseMode(FALSE);
}

void DrawBackground() {
    DefineColor("Floor", 0.825, 0.775, 0.695);
    DefineColor("LightPurple", 0.85, 0.725, 1);
    DefineColor("LightBlue", 0.75, 0.95, 1);
    DefineColor("White", 1, 1, 1);
    DefineColor("Black", 0, 0, 0);
    MovePen(0, 7);
    DrawLine(10, 0);
    DrawLine(0, -7);
    DrawLine(-10, 0);
    DrawLine(0, 7);
    MovePen(0, 6.7);
    DrawLine(10, 0);
    SetPenColor("Floor");
    StartFilledRegion(1);
    MovePen(0, 0);
    DrawLine(0.8, 0.3);
    DrawLine(9.2, 0);
    DrawLine(0, -0.15);
    DrawLine(-0.4, -0.15);
    DrawLine(-9.6, 0);
    EndFilledRegion();
    SetPenColor("Black");
    MovePen(0, 0);
    DrawLine(0.8, 0.3);
    DrawLine(9.2, 0);
    DrawLine(0, -0.15);
    DrawLine(-0.4, -0.15);
    DrawLine(-9.6, 0);
    MovePen(0.8, 0.3);
    DrawLine(0, 6.4);
    /* draw the sign */
    //fill color the structure//
    SetPenColor("LightPurple");
    StartFilledRegion(1);
    MovePen(6.5, 6);
    DrawLine(0, -1.9);
    DrawLine(0.1, -0.1);
    DrawLine(0.9, 0);
    DrawLine(0, 2);
    DrawLine(-1, 0);
    EndFilledRegion();
    SetPenColor("White");
    StartFilledRegion(1);
    MovePen(6.6, 5.9);
    DrawLine(0, -1);
    DrawLine(0.15, 0);
    DrawLine(0.1, -0.1);
    DrawLine(-0.25, 0);
    DrawLine(0, -0.65);
    DrawLine(0.05, -0.05);
    DrawLine(0.75, 0);
    DrawLine(0, 0.7);
    DrawLine(-0.5, 0);
    DrawLine(-0.1, 0.1);
    DrawLine(0, 0.3);
    DrawLine(0.1, -0.1);
    DrawLine(0, -0.2);
    DrawLine(0.2, 0);
    DrawLine(0, 0.2);
    DrawLine(-0.3, 0.3);
    DrawLine(0, 0.3);
    DrawLine(0.1, 0.1);
    DrawLine(0.2, 0);
    DrawLine(0.1, -0.1);
    DrawLine(0, -0.8);
    DrawLine(0.2, 0);
    DrawLine(0, 1);
    DrawLine(-0.8, 0);
    EndFilledRegion();
    //fill color the inner part//
    StartFilledRegion(1);
    MovePen(6.925, 5.65);
    DrawLine(0, -0.2);
    DrawLine(0.15, -0.15);
    DrawLine(0, 0.35);
    DrawLine(-0.15, 0);
    EndFilledRegion();
    SetPenColor("LightPurple");
    StartFilledRegion(1);
    MovePen(6.925, 4.625);
    DrawLine(0, -0.35);
    DrawLine(0.15, 0);
    DrawLine(0, 0.35);
    DrawLine(-0.15, 0);
    EndFilledRegion();
    StartFilledRegion(1);
    MovePen(7.1125, 4.625);
    DrawLine(0, -0.35);
    DrawLine(0.15, 0);
    DrawLine(0, 0.35);
    DrawLine(-0.15, 0);
    EndFilledRegion();
    StartFilledRegion(1);
    MovePen(6.8125, 4.625);
    DrawLine(0, -0.35);
    DrawLine(0.075, 0);
    DrawLine(0, 0.35);
    DrawLine(-0.075, 0);
    EndFilledRegion();
    SetPenColor("White");
    StartFilledRegion(1);
    MovePen(6.975, 4.525);
    DrawLine(0, -0.15);
    DrawLine(0.05, 0);
    DrawLine(0, 0.15);
    DrawLine(-0.05, 0);
    EndFilledRegion();
    StartFilledRegion(1);
    MovePen(7.1625, 4.525);
    DrawLine(0, -0.15);
    DrawLine(0.05, 0);
    DrawLine(0, 0.15);
    DrawLine(-0.05, 0);
    EndFilledRegion();
    // draw the edges//
    SetPenColor("Black");
    MovePen(6.5, 6);
    DrawLine(0, -1.9);
    DrawLine(0.1, -0.1);
    DrawLine(0.9, 0);
    DrawLine(0, 2);
    DrawLine(-1, 0);
    MovePen(6.6, 5.9);
    DrawLine(0, -1);
    DrawLine(0.15, 0);
    DrawLine(0.1, -0.1);
    DrawLine(-0.25, 0);
    DrawLine(0, -0.65);
    DrawLine(0.05, -0.05);
    DrawLine(0.75, 0);
    DrawLine(0, 0.7);
    DrawLine(-0.5, 0);
    DrawLine(-0.1, 0.1);
    DrawLine(0, 0.3);
    DrawLine(0.1, -0.1);
    DrawLine(0, -0.2);
    DrawLine(0.2, 0);
    DrawLine(0, 0.2);
    DrawLine(-0.3, 0.3);
    DrawLine(0, 0.3);
    DrawLine(0.1, 0.1);
    DrawLine(0.2, 0);
    DrawLine(0.1, -0.1);
    DrawLine(0, -0.8);
    DrawLine(0.2, 0);
    DrawLine(0, 1);
    DrawLine(-0.8, 0);
    MovePen(6.925, 5.65);
    DrawLine(0, -0.2);
    DrawLine(0.15, -0.15);
    DrawLine(0, 0.35);
    DrawLine(-0.15, 0);
    MovePen(6.925, 4.625);
    DrawLine(0, -0.35);
    DrawLine(0.15, 0);
    DrawLine(0, 0.35);
    DrawLine(-0.15, 0);
    MovePen(7.1125, 4.625);
    DrawLine(0, -0.35);
    DrawLine(0.15, 0);
    DrawLine(0, 0.35);
    DrawLine(-0.15, 0);
    MovePen(6.8125, 4.625);
    DrawLine(0, -0.35);
    DrawLine(0.075, 0);
    DrawLine(0, 0.35);
    DrawLine(-0.075, 0);
    MovePen(6.975, 4.525);
    DrawLine(0, -0.15);
    DrawLine(0.05, 0);
    DrawLine(0, 0.15);
    DrawLine(-0.05, 0);
    MovePen(7.1625, 4.525);
    DrawLine(0, -0.15);
    DrawLine(0.05, 0);
    DrawLine(0, 0.15);
    DrawLine(-0.05, 0);
    /* draw the colourful strings */
    SetPenColor("LightBlue");
    StartFilledRegion(1);
    MovePen(0.8, 2.8);
    DrawLine(2.5, -2.5);
    DrawLine(0.5, 0);
    DrawLine(-3, 3);
    DrawLine(0, -0.5);
    EndFilledRegion();
    SetPenColor("LightPurple");
    StartFilledRegion(1);
    MovePen(0.8, 3.3);
    DrawLine(1.5, -1.5);
    DrawLine(0, 0.5);
    DrawLine(-1.5, 1.5);
    DrawLine(0, -0.5);
    EndFilledRegion();
    SetPenColor("Black");
    MovePen(0.8, 2.8);
    DrawLine(2.5, -2.5);
    DrawLine(0.5, 0);
    DrawLine(-3, 3);
    DrawLine(0, -0.5);
    MovePen(0.8, 3.3);
    DrawLine(1.5, -1.5);
    DrawLine(0, 0.5);
    DrawLine(-1.5, 1.5);
    DrawLine(0, -0.5);
}