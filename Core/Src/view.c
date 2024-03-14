#include "view.h"

void fun_0()
{
    Lcd_Clear(WHITE);
    Gui_DrawFont_GBK16(35, 120, BLUE, WHITE, (uint8_t *)"       Sudoku        ");
    Gui_DrawFont_GBK16(37, 150, GRAY2, WHITE, (uint8_t *)"Press K3 to continue.");
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
    int level_flag = 0;
    if (level < 4)
    {
        level_flag = 1;
        gap_num = 36;
    }
    else
    {
        gap_num = 81;
    }
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            num_mask[j][i] = num_mask_lists[level - 1][j][i];

    Lcd_Clear(WHITE);
    operating_instructions();

    Gui_DrawFont_GBK16(90, 10, PURPLE, WHITE, (uint8_t *)"Level");
    num_str[0] = '0' + level;
    Gui_DrawFont_GBK16(140, 10, PURPLE, WHITE, num_str);
    drawBar(30 + level_flag * 30, 40 + level_flag * 30, 210 - level_flag * 30, 220 - level_flag * 30, GRAY0);
    for (int i = 0; i < (10 - level_flag * 3); i++)
    {
        Gui_DrawLine(30 + level_flag * 30 + i * 20, 40 + level_flag * 30, 30 + level_flag * 30 + i * 20, 220 - level_flag * 30, BLACK);
    }
    for (int i = 0; i < (4 - level_flag); i++)
    {
        Gui_DrawLine(30 + level_flag * 30 + i * 60 - 1, 40 + level_flag * 30, 30 + level_flag * 30 + i * 60 - 1, 220 - level_flag * 30, BLACK);
        Gui_DrawLine(30 + level_flag * 30 + i * 60 + 1, 40 + level_flag * 30, 30 + level_flag * 30 + i * 60 + 1, 220 - level_flag * 30, BLACK);
    }
    for (int i = 0; i < (10 - level_flag * 3); i++)
    {
        Gui_DrawLine(30 + level_flag * 30, 40 + i * 20 + level_flag * 30, 210 - level_flag * 30, 40 + level_flag * 30 + i * 20, BLACK);
    }
    if (level_flag)
    {
        for (int i = 0; i < 4; i++)
        {
            Gui_DrawLine(60, 70 + i * 40 - 1, 180, 70 + i * 40 - 1, BLACK);
            Gui_DrawLine(60, 70 + i * 40 + 1, 180, 70 + i * 40 + 1, BLACK);
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            Gui_DrawLine(30, 40 + i * 60 - 1, 210, 40 + i * 60 - 1, BLACK);
            Gui_DrawLine(30, 40 + i * 60 + 1, 210, 40 + i * 60 + 1, BLACK);
        }
    }
    for (int a = 0; a < (9 - level_flag * 3); a++)
    {
        for (int b = 0; b < (9 - level_flag * 3); b++)
        {
            if (num_mask[a][b] != 0)
            {
                flag_mask[a][b] = 1;
                gap_num -= 1;
                num_str[0] = '0' + num_mask[a][b];
                Gui_DrawFont_GBK16(37 + level_flag * 30 + 20 * a, 42 + level_flag * 30 + 20 * b, BLACK, GRAY0, num_str);
            }
        }
    }
    drawBar(30 + level_flag * 30, 240 - level_flag * 10, 210 - level_flag * 30, 260 - level_flag * 10, GRAY0);
    Gui_DrawLine(30 + level_flag * 30, 240 - level_flag * 10, 210 - level_flag * 30, 240 - level_flag * 10, BLACK);
    Gui_DrawLine(30 + level_flag * 30, 260 - level_flag * 10, 210 - level_flag * 30, 260 - level_flag * 10, BLACK);
    for (int i = 0; i < (10 - level_flag * 3); i++)
    {
        Gui_DrawLine(30 + level_flag * 30 + i * 20, 240 - level_flag * 10, 30 + level_flag * 30 + i * 20, 260 - level_flag * 10, BLACK);
    }
    for (int num = 1; num < (10 - level_flag * 3); num++)
    {
        num_str[0] = '0' + num;
        Gui_DrawFont_GBK16(17 + level_flag * 30 + 20 * num, 242 - level_flag * 10, BLACK, GRAY0, num_str);
    }
    Gui_DrawFont_GBK16(42, 270, RED, WHITE, (uint8_t *)"Number of conflicts:");
    Gui_DrawFont_GBK16(118, 288, RED, WHITE, (uint8_t *)"0");
}

void operating_instructions(void)
{
    Gui_DrawFont_GBK16(73, 40, PURPLE, WHITE, (uint8_t *)"Instructions");
    Gui_DrawFont_GBK16(64, 80, RED, WHITE, (uint8_t *)"K1");
    Gui_DrawFont_GBK16(140, 80, BLUE, WHITE, (uint8_t *)"UP");
    Gui_DrawFont_GBK16(64, 100, RED, WHITE, (uint8_t *)"K2");
    Gui_DrawFont_GBK16(140, 100, BLUE, WHITE, (uint8_t *)"DOWN");
    Gui_DrawFont_GBK16(64, 120, RED, WHITE, (uint8_t *)"K3");
    Gui_DrawFont_GBK16(140, 120, BLUE, WHITE, (uint8_t *)"LEFT");
    Gui_DrawFont_GBK16(64, 140, RED, WHITE, (uint8_t *)"K4");
    Gui_DrawFont_GBK16(140, 140, BLUE, WHITE, (uint8_t *)"RIGHT");
    Gui_DrawFont_GBK16(45, 160, RED, WHITE, (uint8_t *)"K1 & K2");
    Gui_DrawFont_GBK16(140, 160, BLUE, WHITE, (uint8_t *)"Shift");
    Gui_DrawFont_GBK16(45, 180, RED, WHITE, (uint8_t *)"K2 & K3");
    Gui_DrawFont_GBK16(140, 180, BLUE, WHITE, (uint8_t *)"Confirm");
    Gui_DrawFont_GBK16(45, 200, RED, WHITE, (uint8_t *)"K1 & K4");
    Gui_DrawFont_GBK16(140, 200, BLUE, WHITE, (uint8_t *)"Restart");
    Gui_DrawFont_GBK16(37, 240, GRAY2, WHITE, (uint8_t *)"Press K3 to continue.");
    while (1)
    {
        if (KEYS_PUSHING2)
        {
            delay_ms(20);
            //HAL_Delay(20); // Ïû¶¶
            if (KEYS_PUSHING2)
            {
                break;
            }
        }
    }
    Lcd_Clear(WHITE);
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
    int level_flag = 0;
    if (level < 4)
    {
        level_flag = 1;
    }
    x *= 20;
    y *= 20;
    drawBar(30 + level_flag * 30 + x + 2, 40 + level_flag * 30 + y + 2, 30 + level_flag * 30 + x + 19, 40 + level_flag * 30 + y + 19, color);
}

void drawCursor(int x, int y, int bg)
{
    int level_flag = 0;
    uint8_t num_str[2] = {0};
    if (level < 4)
    {
        level_flag = 1;
    }

    drawBarPos(x, y, bg);
    if (y < (10 - level_flag * 2))
    {
        if (num_mask[x][y])
        {
            num_str[0] = '0' + num_mask[x][y];
            Gui_DrawFont_GBK16(37 + level_flag * 30 + 20 * x, 42 + level_flag * 30 + 20 * y, BLACK, bg, num_str);
        }
        else if (add_mask[x][y])
        {
            num_str[0] = '0' + add_mask[x][y];
            Gui_DrawFont_GBK16(37 + level_flag * 30 + 20 * x, 42 + level_flag * 30 + 20 * y, DGREEN, bg, num_str);
        }
    }
    else
    {
        num_str[0] = '0' + x + 1;
        Gui_DrawFont_GBK16(37 + level_flag * 30 + 20 * x, 42 + level_flag * 30 + 20 * y, BLACK, bg, num_str);
    }
}

void success(void)
{
    drawBar(30, 100, 210, 160, WHITE);
    int line[4][4] = {{30, 100, 30, 160}, {210, 100, 210, 160}, {30, 100, 210, 100}, {30, 160, 210, 160}};
    for (int i = 0; i < 4; i++)
    {
        Gui_DrawLine(line[i][0], line[i][1], line[i][2], line[i][3], BLACK);
    }
    Gui_DrawFont_GBK16(90, 112, RED, WHITE, (uint8_t *)"Success!");
    Gui_DrawFont_GBK16(38, 132, RED, WHITE, (uint8_t *)"Press K3 to continue.");
}

void failure(void)
{
    drawBar(30, 100, 210, 160, WHITE);
    int line[4][4] = {{30, 100, 30, 160}, {210, 100, 210, 160}, {30, 100, 210, 100}, {30, 160, 210, 160}};
    for (int i = 0; i < 4; i++)
    {
        Gui_DrawLine(line[i][0], line[i][1], line[i][2], line[i][3], BLACK);
    }
    Gui_DrawFont_GBK16(90, 112, BLUE, WHITE, (uint8_t *)"Failure.");
    Gui_DrawFont_GBK16(38, 132, BLUE, WHITE, (uint8_t *)"Press K3 to continue.");
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
void draw_round_cursor(int x, int y, int bg, int text)
{
    uint8_t num_str[2] = {0};
    num_str[0] = '1' + x;
    for (int r = 20; r > 17; r--)
        Gui_Circle(70 + x * 50, 100 + y * 102, r, text);
    for (int r = 17; r > 0; r--)
        Gui_Circle(70 + x * 50, 100 + y * 102, r, bg);
    Gui_DrawFont_GBK16(67 + x * 50, 92 + y * 102, text, bg, num_str);
}