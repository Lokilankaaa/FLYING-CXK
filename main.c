//
// Created by Lokilanka on 2019/5/11.
//

#include <sysfunction.h>
#include <graphics.h>
#include <menu.h>
#include <imgui.h>
#include <extgraph.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "WinMM.Lib")


void Main() {

    InitGraphics();
    InitGUI();
    SetWindowTitle("FLYING CXK");

    PlaySound("jntm.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    display();

    registerCharEvent(CharEventProcess);
    registerKeyboardEvent(KeyboardEventProcess);
    registerTimerEvent(TimerEventProcess);
    registerMouseEvent(MouseEventProcess);

}

