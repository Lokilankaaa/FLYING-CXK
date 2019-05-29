//===========================================================================
//
//  唳垀衄氪ㄩ####
//
//  郔輪党蜊ㄩ2019爛4堎15
//            氝樓賸諷璃腔晇伎睿沓喃腔扢离ㄛ
//            眕摯扢离晇伎腔瞰赽ㄗ婓滲杅demoGuiALL.c腔drawButtons滲杅爵ㄘ
//  郔輪党蜊ㄩ2019爛2堎26
//            氝樓賸栳尨恅掛晤憮栳尨
//            氝樓賸雄賒栳尨
//            氝樓賸textbox 恅掛怀諷璃
//            潠趙賸粕等揭燴
//            蜊 uiGetInput 峈 uiGetMouse,uiGetKey,uiGetKeyboard
//  郔輪党蜊ㄩ2019爛2堎18
//  場棒斐膘ㄩ2018爛4堎ㄛ蚚衾<<最唗扢數蚳枙>>諺最諒悝
//
//===========================================================================

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include <time.h>

#include "imgui.h"


#define KMOD_SHIFT 0x01
#define KMOD_CTRL  0x02


/* 扷梓睿諾潔袨怓 */
typedef struct {
    double mousex;
    double mousey;
    int    mousedown;
    int    clickedItem;// item that was clicked
    int    actingMenu; // acting menu list
    int    kbdItem;    // item that takes keyboard
    int    lastItem;   // item that had focus just before
    int    keyPress;   // input key
    int    charInput;  // input char
    int    keyModifiers;  //  key modifier (shift, ctrl)
} UIState;

static UIState gs_UIState;

/* 滲杅靡ㄩ	InitGUI
 *
 * 髡夔ㄩ場宎趙馱釬
 *
 * 蚚楊ㄩ婓敦諳斐膘麼趼极扢离眳綴覃蚚
 */
void InitGUI()
{
    // doing nothing now
}

void mySetPenColor(char *color)
{
    if( color && strlen(color)>0 ) SetPenColor(color);
}

/*
 *  libgraphics 啎隅砱腔晇伎靡備
 *
 *  DefineColor("Black", 0, 0, 0);
 *  DefineColor("Dark Gray", .35, .35, .35);
 *  DefineColor("Gray", .6, .6, .6);
 *  DefineColor("Light Gray", .75, .75, .75);
 *  DefineColor("White", 1, 1, 1);
 *  DefineColor("Brown", .35, .20, .05);
 *  DefineColor("Red", 1, 0, 0);
 *  DefineColor("Orange", 1, .40, .1);
 *  DefineColor("Yellow", 1, 1, 0);
 *  DefineColor("Green", 0, 1, 0);
 *  DefineColor("Blue", 0, 0, 1);
 *  DefineColor("Violet", .93, .5, .93);
 *  DefineColor("Magenta", 1, 0, 1);
 *  DefineColor("Cyan", 0, 1, 1);
 */

/*
 *  粕等晇伎
 */
static struct {
    char frame[32];
    char label[32];
    char hotFrame[32];
    char hotLabel[32];
    int  fillflag;
} gs_predefined_colors[] = {
        {"Blue",      "Blue",	"Red",	    "Red",   0 }, //
        {"Orange",    "Black", "Green",    "Blue",  0 }, //
        {"Orange",    "White", "Green",    "Blue",  1 }, // 沓喃
        {"Light Gray","Black",  "Dark Gray","Blue",0 },  //
        {"Light Gray","Black",  "Dark Gray","Yellow",1 },  // 沓喃
        {"Brown",     "Red",    "Orange",   "Blue",0 },
        {"Brown",     "Red",    "Orange",   "White",1 }   // 沓喃
},

        gs_menu_color = {
        "Blue",      "Blue",	"Red",	    "Red",   0 , // 祥沓喃
},

        gs_button_color = {
        "Blue",      "Blue",	"Red",	    "Red",   0 , // 祥沓喃
},

        gs_textbox_color = {
        "Blue",      "Blue",	"Red",	    "Red",   0 , // 祥沓喃
};

void setButtonColors(char *frame, char*label, char *hotFrame, char *hotLabel, int fillflag)
{
    if(frame) strcpy(gs_button_color.frame, frame);
    if(label) strcpy(gs_button_color.label, label);
    if(hotFrame) strcpy(gs_button_color.hotFrame, hotFrame);
    if(hotLabel) strcpy(gs_button_color.hotLabel ,hotLabel);
    gs_button_color.fillflag = fillflag;
}

void setMenuColors(char *frame, char*label, char *hotFrame, char *hotLabel, int fillflag)
{
    if(frame) strcpy(gs_menu_color.frame, frame);
    if(label) strcpy(gs_menu_color.label, label);
    if(hotFrame) strcpy(gs_menu_color.hotFrame, hotFrame);
    if(hotLabel) strcpy(gs_menu_color.hotLabel ,hotLabel);
    gs_menu_color.fillflag = fillflag;
}

void setTextBoxColors(char *frame, char*label, char *hotFrame, char *hotLabel, int fillflag)
{
    if(frame) strcpy(gs_textbox_color.frame, frame);
    if(label) strcpy(gs_textbox_color.label, label);
    if(hotFrame) strcpy(gs_textbox_color.hotFrame, hotFrame);
    if(hotLabel) strcpy(gs_textbox_color.hotLabel ,hotLabel);
    gs_textbox_color.fillflag = fillflag;
}

void usePredefinedColors(int k)
{
    int N = sizeof(gs_predefined_colors)/sizeof(gs_predefined_colors[0]);
    gs_menu_color    = gs_predefined_colors[k%N];
    gs_button_color  = gs_predefined_colors[k%N];
    gs_textbox_color = gs_predefined_colors[k%N];
}
void usePredefinedButtonColors(int k)
{
    int N = sizeof(gs_predefined_colors)/sizeof(gs_predefined_colors[0]);
    gs_button_color  = gs_predefined_colors[k%N];
}
void usePredefinedMenuColors(int k)
{
    int N = sizeof(gs_predefined_colors)/sizeof(gs_predefined_colors[0]);
    gs_menu_color    = gs_predefined_colors[k%N];
}
void usePredefinedTexBoxColors(int k)
{
    int N = sizeof(gs_predefined_colors)/sizeof(gs_predefined_colors[0]);
    gs_textbox_color = gs_predefined_colors[k%N];
}

/* 覃蚚蜆滲杅,腕善扷梓腔袨怓 */
void uiGetMouse(int x, int y, int button, int event)
{
    gs_UIState.mousex = ScaleXInches(x);/*pixels --> inches*/
    gs_UIState.mousey = ScaleYInches(y);/*pixels --> inches*/

    switch (event) {
        case BUTTON_DOWN:
            gs_UIState.mousedown = 1;
            break;
        case BUTTON_UP:
            gs_UIState.mousedown = 0;
            break;
    }
}

/* 覃蚚蜆滲杅,腕善瑩攫腔怀 */
void uiGetKeyboard(int key, int event)
{
    if( event==KEY_DOWN )
    {
        switch (key )
        {
            case VK_SHIFT:
                gs_UIState.keyModifiers |= KMOD_SHIFT;
                break;
            case VK_CONTROL:
                gs_UIState.keyModifiers |= KMOD_CTRL;
                break;
            default:
                gs_UIState.keyPress = key;
        }
    }
    else if( event==KEY_UP )
    {
        switch (key )
        {
            case VK_SHIFT:
                gs_UIState.keyModifiers &= ~KMOD_SHIFT;
                break;
            case VK_CONTROL:
                gs_UIState.keyModifiers &= ~KMOD_CTRL;
                break;
            default:
                gs_UIState.keyPress = 0;
        }
    }
}

/* 覃蚚蜆滲杅,腕善恅掛怀 */
void uiGetChar(int ch)
{
    gs_UIState.charInput = ch;
}


/* 聆彸ㄩ釴梓萸(x,y)岆瘁弇衾婦峓睿 [x1,x2] X [y1,y2] 囀窒 */
static bool inBox(double x, double y, double x1, double x2, double y1, double y2)
{
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

/*
 * 滲杅靡ㄩbutton
 *
 * 髡夔ㄩ珆尨珨跺偌聽ㄗbuttonㄘ
 *
 * 蚚楊ㄩif( button(GenUUID(0),x,y,w,h,label) ) {
 *           硒俴逄曆ㄛ砒茼蚚誧偌狟蜆偌聽
 *       }
 *
 *   id  - 峔珨瘍
 *   x,y - 弇离
 *   w,h - 遵僅睿詢僅
 *   label - 偌聽奻腔恅趼梓
 *
 * 殿隙硉
 *   0 - 蚚誧羶衄萸僻ㄗ偌狟甜庋溫ㄘ偌聽
 *   1 - 萸僻賸偌聽
 */
int button(int id, double x, double y, double w, double h, char *label)
{
    char * frameColor = gs_button_color.frame;
    char * labelColor = gs_button_color.label;
    double movement = 0.2*h;
    double shrink = 0.15*h;
    double sinkx = 0, sinky = 0;
    //int isHotItem = 0;

    if (inBox(gs_UIState.mousex, gs_UIState.mousey, x, x + w, y, y + h)) {
        frameColor = gs_button_color.hotFrame;
        labelColor = gs_button_color.hotLabel;
        gs_UIState.actingMenu = 0; // menu lose focus
        if ( gs_UIState.mousedown) {
            gs_UIState.clickedItem = id;
            sinkx =   movement;
            sinky = - movement;
        }
    }
    else {
        if ( gs_UIState.clickedItem==id )
            gs_UIState.clickedItem = 0;
    }

    // If no widget has keyboard focus, take it
    if (gs_UIState.kbdItem == 0)
        gs_UIState.kbdItem = id;
    // If we have keyboard focus, we'll need to process the keys
    if ( gs_UIState.kbdItem == id && gs_UIState.keyPress==VK_TAB )
    {
        // If tab is pressed, lose keyboard focus.
        // Next widget will grab the focus.
        gs_UIState.kbdItem = 0;
        // If shift was also pressed, we want to move focus
        // to the previous widget instead.
        if ( gs_UIState.keyModifiers & KMOD_SHIFT )
            gs_UIState.kbdItem = gs_UIState.lastItem;
        gs_UIState.keyPress = 0;
    }
    gs_UIState.lastItem = id;

    // draw the button
    mySetPenColor(frameColor);
    drawBox(x+sinkx, y+sinky, w, h, gs_button_color.fillflag,
            label, 'C', labelColor);
    if( gs_button_color.fillflag ) {
        mySetPenColor( labelColor );
        drawRectangle(x+sinkx, y+sinky, w, h, 0);
    }

    // 賒瑩攫枑尨, show a small ractangle frane
    if( gs_UIState.kbdItem == id ) {
        mySetPenColor( labelColor );
        drawRectangle(x+sinkx+shrink, y+sinky+shrink, w-2*shrink, h-2*shrink, 0);
    }

    if( gs_UIState.clickedItem==id && // must be clicked before
        ! gs_UIState.mousedown )   // but now mouse button is up
    {
        gs_UIState.clickedItem = 0;
        gs_UIState.kbdItem = id;
        return 1;
    }

    return 0;
}

/*
 * 珆尨珨跺粕等砐
 *   id  - 粕等砐腔峔珨瘍
 *   x,y - 粕等砐腔弇离
 *   w,h - 粕等砐腔湮苤
 *   label - 粕等砐腔梓恅趼
 *
 * 殿隙硉
 *   0 - 蚚誧羶衄萸僻ㄗ偌狟甜庋溫ㄘ森粕等砐
 *   1 - 萸僻賸森粕等砐
 */
static int menuItem(int id, double x, double y, double w, double h, char *label)
{
    char * frameColor = gs_menu_color.frame;
    char * labelColor = gs_menu_color.label;
    if (inBox(gs_UIState.mousex, gs_UIState.mousey, x, x + w, y, y + h)) {
        frameColor = gs_menu_color.hotFrame;
        labelColor = gs_menu_color.hotLabel;
        //if (gs_UIState.mousedown) {
        if ( (gs_UIState.clickedItem == id ||gs_UIState.clickedItem == 0) && gs_UIState.mousedown) {
            gs_UIState.clickedItem = id;
        }
    }
    else {
        if ( gs_UIState.clickedItem==id )
            gs_UIState.clickedItem = 0;
    }

    mySetPenColor(frameColor);
    drawBox(x, y, w, h, gs_menu_color.fillflag, label, 'L', labelColor);

    if( gs_UIState.clickedItem==id && // must be clicked before
        ! gs_UIState.mousedown )     // but now mouse button is up
    {
        gs_UIState.clickedItem = 0;
        return 1;
    }

    return 0;
}

/*
 * 滲杅靡ㄩshortcutkey
 *
 * 髡夔ㄩ植粕等梓笢枑※辦豎瑩§湮迡趼譫
 *       猁辦豎瑩梓祩 Ctrl-X 弇衾梓腔賦帣窒煦
 */
static char ToUpperLetter(char c)
{
    return (c>='a' && c<='z' ? c-'a'+'A' : c);
}

static char shortcutkey(char *s)
{
    char predStr[] = "Ctrl-";
    int M = strlen(predStr)+1;
    int n = s ? strlen(s) : 0;

    if( n<M || strncmp(s+n-M, predStr, M-1)!=0 )
        return 0;

    return ToUpperLetter(s[n-1]);
}

/*
 * 滲杅靡ㄩmenuList
 *
 * 髡夔ㄩ珆尨珨跺郪粕等
 *
 * 蚚楊ㄩchoice = menuList(GenUUID(0),x,y,w,h,labels,n);
 *
 *   id  - 粕等腔峔珨瘍
 *   x,y,w,h - 粕等濬梗腔弇离睿湮苤
 *   wlist,h - 粕等蹈桶腔遵僅睿詢僅
 *   labels[] - 梓恅趼ㄛ[0]岆粕等濬梗ㄛ[1...n-1]岆粕等蹈桶
 *   n   - 粕等砐腔跺杅
 *
 * 殿隙硉
 *   -1    - 蚚誧羶衄萸僻ㄗ偌狟甜庋溫ㄘ偌聽
 *   >=0   - 蚚誧恁笢腔粕等砐 index ㄗ婓labels[]笢ㄘ
 *
 */
int menuList(int id, double x, double y, double w, double wlist, double h, char *labels[], int n)
{
    static int unfoldMenu = 0;
    int result = 0;
    int k = -1;

    // 揭燴辦豎瑩

    if( gs_UIState.keyModifiers & KMOD_CTRL ) {
        for( k=1; k<n; k++ ) {
            int kp = ToUpperLetter( gs_UIState.keyPress );
            if( kp && kp == shortcutkey(labels[k]) ) {
                gs_UIState.keyPress = 0;
                break;
            }
        }
    }

    if( k>0 && k<n )
    {	// 傖髡饜辦豎瑩
        unfoldMenu = 0;
        return k;
    }

    // 揭燴扷梓

    if( inBox(gs_UIState.mousex, gs_UIState.mousey, x, x + w, y, y + h) )
        gs_UIState.actingMenu = id;

    if( menuItem(id, x, y, w, h, labels[0]) )
        unfoldMenu = ! unfoldMenu;

    if( gs_UIState.actingMenu == id && unfoldMenu  ) {
        int k;
        gs_UIState.charInput = 0; // disable text editing
        gs_UIState.keyPress = 0;  // disable text editing
        for( k=1; k<n; k++ ) {
            if ( menuItem(GenUIID(k)+id, x, y-k*h, wlist, h, labels[k]) ) {
                unfoldMenu = 0;
                result = k;
            }
        }
    }
    return result;
}

void drawMenuBar(double x, double y, double w, double h)
{
    mySetPenColor(gs_menu_color.frame);
    drawRectangle(x,y,w,h,gs_menu_color.fillflag);
}


/*
 * 滲杅靡ㄩtextbox
 *
 * 髡夔ㄩ珆尨珨跺恅掛晤憮遺ㄛ珆尨睿晤憮恅掛趼睫揹
 *
 * 蚚楊ㄩtextbox(GenUUID(0),x,y,w,h,textbuf,buflen);
 *       麼氪
         if( textbox(GenUUID(0),x,y,w,h,textbuf,buflen) ) {
 *           恅掛趼睫揹掩晤憮党蜊賸ㄛ硒俴眈茼逄曆
 *       }
 *
 *   id  - 峔珨瘍ㄛ珨啜蚚GenUUID(0), 麼蚚GenUUIDㄗk)ㄗk岆悜遠曹講ㄘ
 *   x,y - 恅掛遺弇离
 *   w,h - 恅掛遺腔遵僅睿詢僅
 *   textbuf - 掩晤憮腔恅掛趼睫揹ㄗ眕\0賦帣ㄘ
 *   buflen - 褫湔揣腔恅掛趼睫揹腔郔湮酗僅
 * 殿隙硉
 *   0 - 恅掛羶衄掩晤憮
 *   1 - 掩晤憮賸
 */
int textbox(int id, double x, double y, double w, double h, char textbuf[], int buflen)
{
    char * frameColor = gs_textbox_color.frame;
    char * labelColor = gs_textbox_color.label;
    int textChanged = 0;
    int len = strlen(textbuf);
    double indent = GetFontAscent()/2;
    double textPosY = y+h/2-GetFontAscent()/2;

    if ( inBox(gs_UIState.mousex, gs_UIState.mousey, x, x + w, y, y + h) )
    {
        frameColor = gs_textbox_color.hotFrame;
        labelColor = gs_textbox_color.hotLabel;
        gs_UIState.actingMenu = 0; // menu lose focus
        if ( gs_UIState.mousedown) {
            gs_UIState.clickedItem = id;
        }
    }

    // If no widget has keyboard focus, take it
    if (gs_UIState.kbdItem == 0)
        gs_UIState.kbdItem = id;

    if (gs_UIState.kbdItem == id)
        labelColor = gs_textbox_color.hotLabel;

    // Render the text box
    mySetPenColor(frameColor);
    drawRectangle(x, y, w, h, gs_textbox_color.fillflag);
    // show text
    mySetPenColor(labelColor);
    MovePen(x+indent, textPosY);
    DrawTextString(textbuf);
    // add cursor if we have keyboard focus
    if ( gs_UIState.kbdItem == id && (clock() >> 8) & 1)
    {
        //MovePen(x+indent+TextStringWidth(textbuf), textPosY);
        DrawTextString("_");
    }

    // If we have keyboard focus, we'll need to process the keys
    if ( gs_UIState.kbdItem == id )
    {
        switch (gs_UIState.keyPress)
        {
            case VK_RETURN:
            case VK_TAB:
                // lose keyboard focus.
                gs_UIState.kbdItem = 0;
                // If shift was also pressed, we want to move focus
                // to the previous widget instead.
                if ( gs_UIState.keyModifiers & KMOD_SHIFT )
                    gs_UIState.kbdItem = gs_UIState.lastItem;
                // Also clear the key so that next widget won't process it
                gs_UIState.keyPress = 0;
                break;
            case VK_BACK:
                if( len > 0 ) {
                    textbuf[--len] = 0;
                    textChanged = 1;
                }
                gs_UIState.keyPress = 0;
                break;
        }
        // char input
        if (gs_UIState.charInput >= 32 && gs_UIState.charInput < 127 && len+1 < buflen ) {
            textbuf[len] = gs_UIState.charInput;
            textbuf[++len] = 0;
            gs_UIState.charInput = 0;
            textChanged = 1;
        }
    }

    gs_UIState.lastItem = id;

    if( gs_UIState.clickedItem==id && // must be clicked before
        ! gs_UIState.mousedown )     // but now mouse button is up
    {
        gs_UIState.clickedItem = 0;
        gs_UIState.kbdItem = id;
    }

    return textChanged;
}


/* 賒珨跺撻倛 */
void drawRectangle(double x, double y, double w, double h, int fillflag)
{
    MovePen(x, y);
    if( fillflag ) StartFilledRegion(1);
    {
        DrawLine(0, h);
        DrawLine(w, 0);
        DrawLine(0, -h);
        DrawLine(-w, 0);
    }
    if( fillflag ) EndFilledRegion();
}

/* 賒珨跺撻倛ㄛ甜婓囀窒懈笢珆尨珨跺趼睫揹梓label */
void drawBox(double x, double y, double w, double h, int fillflag, char *label, char labelAlignment, char *labelColor)
{
    double fa = GetFontAscent();
    // rect
    drawRectangle(x,y,w,h,fillflag);
    // text
    if( label && strlen(label)>0 ) {
        mySetPenColor(labelColor);
        if( labelAlignment=='L' )
            MovePen(x+fa/2, y+h/2-fa/2);
        else if( labelAlignment=='R' )
            MovePen(x+w-fa/2-TextStringWidth(label), y+h/2-fa/2);
        else // if( labelAlignment=='C'
            MovePen(x+(w-TextStringWidth(label))/2, y+h/2-fa/2);
        DrawTextString(label);
    }
}

/* 珆尨趼睫揹梓 */
void drawLabel(double x, double y, char *label)
{
    if( label && strlen(label)>0 ) {
        MovePen(x,y);
        DrawTextString(label);
    }
}


void drawMyBox(double x, double y, double w, double h, int fillflag, char *label, char labelAlignment, char *labelColor)
{
    double r = GetFontHeight()/3;
    double fa = GetFontAscent();

    MovePen(x, y);
    if( fillflag ) StartFilledRegion(1);
    {
        MovePen(x, y+r);
        DrawLine(0, h-2*r);
        DrawArc(r, 180, -90);
        MovePen(x+r, y+h);
        DrawLine(w-2*r, 0);
        DrawArc(r, 90, -90);
        MovePen(x+w, y+h-r);
        DrawLine(0, -(h-2*r));
        DrawArc(r, 0, -90);
        MovePen(x+w-r, y);
        DrawLine(-(w-2*r), 0);
        DrawArc(r, 270, -90);
    }
    if( fillflag ) EndFilledRegion();

    if( label && strlen(label)>0 ) {
        mySetPenColor(labelColor);
        if( labelAlignment=='L' )
            MovePen(x+fa/2, y+h/2-fa/2);
        else if( labelAlignment=='R' )
            MovePen(x+w-fa/2-TextStringWidth(label), y+h/2-fa/2);
        else // if( labelAlignment=='C'
            MovePen(x+(w-TextStringWidth(label))/2, y+h/2-fa/2);
        DrawTextString(label);
    }
}

int Mybutton(int id, double x, double y, double w, double h, char *label, int flag)
{
    char * frameColor = gs_button_color.frame;
    char * labelColor = gs_button_color.label;

    if (inBox(gs_UIState.mousex, gs_UIState.mousey, x, x + w, y, y + h)) {
        frameColor = gs_button_color.hotFrame;
        labelColor = gs_button_color.hotLabel;
        gs_UIState.actingMenu = 0; // menu lose focus
        if ( gs_UIState.mousedown)
            gs_UIState.clickedItem = id;
    }
    else {
        if ( gs_UIState.clickedItem==id )
            gs_UIState.clickedItem = 0;
    }

    // draw the button
    mySetPenColor(frameColor);
    if(flag)
        drawMyBox(x, y, w, h, gs_button_color.fillflag, label, 'C', labelColor);
    else
        drawBox(x, y, w, h, 0, label, "C", labelColor);

    if( gs_UIState.clickedItem==id && // must be clicked before
        ! gs_UIState.mousedown )   // but now mouse button is up
    {
        gs_UIState.clickedItem = 0;
        return 1;
    }

    return 0;
}

char *Textbox(double x, double y, double w, double h, char textbuf[], int buflen)
{
    char * frameColor = gs_textbox_color.frame;
    char * labelColor = gs_textbox_color.label;
    int len = strlen(textbuf);
    double indent = GetFontAscent()/2;
    double textPosY = y+h/2-GetFontAscent()/2;

    // Render the text box
    mySetPenColor(frameColor);
    drawRectangle(x, y, w, h, 0);//gs_textbox_color.fillflag);
    // show text
    mySetPenColor("Red");//(labelColor);
    MovePen(x+indent, textPosY);
    DrawTextString(textbuf);
    // add cursor if we have keyboard focus
    if ((clock() >> 8) & 1)   //( gs_UIState.kbdItem == id && (clock() >> 8) & 1))
    {
        //MovePen(x+indent+TextStringWidth(textbuf), textPosY);
        DrawTextString("_");
    }

    switch (gs_UIState.keyPress)
    {
        case VK_RETURN:
            gs_UIState.kbdItem = 0;
            return textbuf;
        case VK_BACK:
            if( len > 0 )
                textbuf[--len] = 0;
            gs_UIState.keyPress = 0;
            break;
    }
    // char input
    if (gs_UIState.charInput >= 48 && gs_UIState.charInput < 122 && len+1 < buflen ) {
        textbuf[len] = gs_UIState.charInput;
        textbuf[++len] = 0;
        gs_UIState.charInput = 0;
    }
    return NULL;
}

int PressESC ()
{
    if (gs_UIState.keyPress == VK_ESCAPE)
        return 1;
    return 0;
}
