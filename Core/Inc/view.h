#ifndef __VIEW_H
#define __VIEW_H

#include "stdio.h"
#include "stdlib.h"
#include "delay.h"
#include "def.h"
#include "GUI.h"
#include "control.h"
#include "model.h"

void initView(void);
void drawBar(int x0, int y0, int x1, int y1, int color);
void drawBarPos(int x, int y, int color);
void drawFlagPos(int x, int y, int bg);
void drawBarPosNum(int x, int y, int num, int bg);
void drawCursor(int x, int y, int bg);
void drawAllMine(void);
void success(void);
void failure(void);
void fun_0();
void fun_a1();
void fun_b1();
void draw_set();
void draw_round_cursor(int x, int y, int bg, int text);
void operating_instructions(void);
#endif
