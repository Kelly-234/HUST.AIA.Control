#include "view.h"

void fun_0()
{
    Lcd_Clear(WHITE);
    Gui_DrawFont_GBK16(35, 120, BLUE, WHITE, (uint8_t *)"        Sudoku        ");
    Gui_DrawFont_GBK16(35, 150, GRAY2, WHITE, (uint8_t *)"Press K3 to continue.");
}
void fun_a1()
{
    Lcd_Clear(WHITE);
    Gui_DrawFont_GBK16(55, 20, RED, GRAY0, (uint8_t *)"Start the game <-");
    Gui_DrawFont_GBK16(55, 40, RED, GRAY0, (uint8_t *)"Settings         ");
}
void fun_b1()
{
    Lcd_Clear(WHITE);
    Gui_DrawFont_GBK16(55, 20, RED, GRAY0, (uint8_t *)"Start the game   ");
    Gui_DrawFont_GBK16(55, 40, RED, GRAY0, (uint8_t *)"Settings       <-");
}
void initView(void)
{
    uint8_t num_str[2] = {0};

    Lcd_Clear(WHITE);

    drawBar(30, 40, 210, 220, GRAY0);
    drawBarPos(currentCursor.x, currentCursor.y, CURSORCOLOR);
    for (int i = 0; i < 10; i++)
    {
        Gui_DrawLine(30 + i * 20, 40, 30 + i * 20, 220, BLACK);
    }
    for (int i = 0; i < 4; i++)
    {
        Gui_DrawLine(30 + i * 60 - 1, 40, 30 + i * 60 - 1, 220, BLACK);
        Gui_DrawLine(30 + i * 60 + 1, 40, 30 + i * 60 + 1, 220, BLACK);
    }
    for (int i = 0; i < 10; i++)
    {
        Gui_DrawLine(30, 40 + i * 20, 210, 40 + i * 20, BLACK);
    }
    for (int i = 0; i < 4; i++)
    {
        Gui_DrawLine(30, 40 + i * 60 - 1, 210, 40 + i * 60 - 1, BLACK);
        Gui_DrawLine(30, 40 + i * 60 + 1, 210, 40 + i * 60 + 1, BLACK);
    }
    for (int a = 0; a < 9; a++)
    {
        for (int b = 0; b < 9; b++)
        {
            if (num_mask[b][a] != 0)
            {
                flag_mask[a][b] = 1;
                gap_num -= 1;
                num_str[0] = '0' + num_mask[b][a];
                Gui_DrawFont_GBK16(37 + 20 * a, 42 + 20 * b, BLACK, GRAY0, num_str);
            }
        }
    }
    drawBar(30, 240, 210, 260, GRAY0);
    Gui_DrawLine(30, 240, 210, 240, BLACK);
    Gui_DrawLine(30, 260, 210, 260, BLACK);
    for (int i = 0; i < 10; i++)
    {
        Gui_DrawLine(30 + i * 20, 240, 30 + i * 20, 260, BLACK);
    }
    for (int num = 1; num < 10; num++)
    {
        num_str[0] = '0' + num;
        Gui_DrawFont_GBK16(17 + 20 * num, 242, BLACK, GRAY0, num_str);
    }
    Gui_DrawFont_GBK16(55, 270, RED, WHITE, (uint8_t *)"Number of errors:");
    num_str[0] = '0' + error_num;
    Gui_DrawFont_GBK16(118, 288, RED, WHITE, num_str);
}

void drawBar(int x0, int y0, int x1, int y1, int color)
{
    for (int i = x0; i < x1; i++)
    {
        for (int j = y0; j < y1; j++)
        {
            Gui_DrawPoint(i, j, color);
        }
    }
}
void drawBarPos(int x, int y, int color)
{
    x *= 20;
    y *= 20;
    drawBar(30 + x + 2, 40 + y + 2, 30 + x + 19, 40 + y + 19, color);
}
void drawCursor(int x, int y, int bg)
{
    uint8_t num_str[2] = {0};

    drawBarPos(x, y, bg);
    if (y < 10)
    {
        if (num_mask[y][x])
        {
            num_str[0] = '0' + num_mask[y][x];
            Gui_DrawFont_GBK16(37 + 20 * x, 42 + 20 * y, BLACK, bg, num_str);
        }
        else if (add_mask[x][y])
        {
            num_str[0] = '0' + add_mask[x][y];
            Gui_DrawFont_GBK16(37 + 20 * x, 42 + 20 * y, DGREEN, bg, num_str);
        }
    }
    else
    {
        num_str[0] = '0' + x + 1;
        Gui_DrawFont_GBK16(37 + 20 * x, 42 + 20 * y, BLACK, bg, num_str);
    }
}
void success(void)
{
    drawBar(30, 100, 210, 160, WHITE);
    int line[4][4] = {{30, 100, 30, 160}, {210, 100, 210, 160}, {30, 100, 210, 100}, {20, 160, 210, 160}};
    for (int i = 0; i < 4; i++)
    {
        Gui_DrawLine(line[i][0], line[i][1], line[i][2], line[i][3], BLACK);
    }
    Gui_DrawFont_GBK16(90, 122, RED, WHITE, (uint8_t *)"Success!");
}
void failure(void)
{
    drawBar(30, 100, 210, 160, WHITE);
    int line[4][4] = {{30, 100, 30, 160}, {210, 100, 210, 160}, {30, 100, 210, 100}, {30, 160, 210, 160}};
    for (int i = 0; i < 4; i++)
    {
        Gui_DrawLine(line[i][0], line[i][1], line[i][2], line[i][3], BLACK);
    }
    Gui_DrawFont_GBK16(90, 122, BLUE, WHITE, (uint8_t *)"Failure.");
}
void draw_set()
{
    uint8_t num_str[2] = {0};

    Lcd_Clear(WHITE);

    Gui_DrawFont_GBK16(92, 22, BLUE, WHITE, (uint8_t *)"Setting");
    Gui_DrawFont_GBK16(70, 52, DGREEN, WHITE, (uint8_t *)"Easy Mode 6*6");
    for (int i = 0; i < 3; i++)
    {
        num_str[0] = '1' + i;
        for (int r = 20; r > 17; r--)
            Gui_Circle(70 + i * 50, 100, r, DGREEN);
        for (int r = 17; r > 0; r--)
            Gui_Circle(70 + i * 50, 100, r, GREEN);
        Gui_DrawFont_GBK16(67 + i * 50, 92, DGREEN, GREEN, num_str);
    }
    Gui_DrawFont_GBK16(70, 152, DCYAN, WHITE, (uint8_t *)"Hard Mode 9*9");
    for (int i = 0; i < 3; i++)
    {
        num_str[0] = '1' + i;
        for (int r = 20; r > 17; r--)
            Gui_Circle(70 + i * 50, 202, r, DCYAN);
        for (int r = 17; r > 0; r--)
            Gui_Circle(70 + i * 50, 202, r, CYAN);
        Gui_DrawFont_GBK16(67 + i * 50, 194, DCYAN, CYAN, num_str);
    }
}