#include "control.h"

int check(int x, int y)
{
    int flag_error = 0;
    for (int i = 0; i < 9; i++)
    {
        if (num_mask[y][i] == add_mask[x][y])
        {
            flag_error = 1;
            break;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (num_mask[i][x] == add_mask[x][y])
        {
            flag_error = 1;
            break;
        }
    }
    for (int i = (x / 3 * 3); i < (x / 3 * 3 + 3); i++)
    {
        for (int j = (y / 3 * 3); j < (y / 3 * 3 + 3); j++)
        {
            if (num_mask[j][i] == add_mask[x][y])
            {
                flag_error = 1;
                break;
            }
        }
    }
    if (flag_error && (!flag_mask[x][y]))
    {
        flag_mask[x][y] = 1;
        fill_num += 1;
        return 1;
    }
    else
    {
        flag_mask[x][y] = 1;
        return 0;
    }
}
void fun_mine()
{
    uint8_t num_str[2] = {0};
    uint8_t error_num_str[3] = {0};

    initView();
    while (1)
    {
        if (game_over)
        {
            if (KEYS_PUSHING0 && KEYS_PUSHING3)
            {
                break;
            }
            else
                continue;
        }

        /* USER CODE END WHILE */
        if ((KEYS_PUSHING0) || (KEYS_PUSHING1) || (KEYS_PUSHING2) || (KEYS_PUSHING3))
        {
            HAL_Delay(100); // 消抖
            if (KEYS_PUSHING0 && KEYS_PUSHING3)
            {
                break;
            }
            if (KEYS_PUSHING0 && KEYS_PUSHING1) // 区域切换
            {
                drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                if (flag)
                {
                    button2[0] = currentCursor.x;
                    button2[1] = currentCursor.y;
                    currentCursor.x = button1[0];
                    currentCursor.y = button1[1];
                    if (add_mask[currentCursor.x][currentCursor.y])
                    {
                        if (check(currentCursor.x, currentCursor.y))
                        {
                            error_num += 1;
                            if (error_num > 9)
                            {
                                error_num_str[0] = '1';
                                error_num_str[1] = '0' + error_num - 10;
                                Gui_DrawFont_GBK16(110, 288, RED, WHITE, error_num_str);
                            }
                            else
                            {
                                error_num_str[0] = '0' + error_num;
                                error_num_str[1] = '\0';
                                Gui_DrawFont_GBK16(118, 288, RED, WHITE, error_num_str);
                            }
                            if (error_num > max_error_num)
                            {
                                failure();
                            }
                        }
                        if ((gap_num == fill_num) && error_num == 0) // 成功
                        {
                            success();
                        }
                    }
                    flag = 0;
                }
                else
                {
                    if (!num_mask[currentCursor.y][currentCursor.x])
                    {
                        button1[0] = currentCursor.x;
                        button1[1] = currentCursor.y;
                        currentCursor.x = button2[0];
                        currentCursor.y = button2[1];
                        flag = 1;
                    }
                }
                drawCursor(currentCursor.x, currentCursor.y, GRAY1);
            }
            else if (KEYS_PUSHING1 && KEYS_PUSHING2 && flag) // 选择数字
            {
                add_mask[button1[0]][button1[1]] = currentCursor.x + 1;
                num_str[0] = '0' + currentCursor.x + 1;
                Gui_DrawFont_GBK16(30 + button1[0] * 20 + 7, 40 + button1[1] * 20 + 2, DGREEN, GRAY0, num_str);
            }
            // 下面是上下左右
            else if (KEYS_PUSHING0 && (!flag))
            {
                HAL_Delay(10);
                if (KEYS_PUSHING0)
                {
                    HAL_Delay(500);
                    if (KEYS_PUSHING0)
                    {
                        while (KEYS_PUSHING0)
                        {
                            if (currentCursor.y > POS_Y_MIN)
                            {
                                drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                                currentCursor.y -= 1;
                                drawCursor(currentCursor.x, currentCursor.y, GRAY1);
                            }
                        }
                        continue;
                    }
                    else
                    {
                        if (currentCursor.y > POS_Y_MIN)
                        {
                            drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                            currentCursor.y -= 1;
                            drawCursor(currentCursor.x, currentCursor.y, GRAY1);
                        }
                    }
                }
            }
            else if (KEYS_PUSHING3 && (!flag))
            {
                if (currentCursor.y < POS_Y_MAX)
                {
                    drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                    currentCursor.y += 1;
                    drawCursor(currentCursor.x, currentCursor.y, GRAY1);
                }
                while (KEYS_PUSHING3)
                {
                }
            }
            else if (KEYS_PUSHING1)
            {
                if (currentCursor.x > POS_X_MIN)
                {
                    drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                    currentCursor.x -= 1;
                    drawCursor(currentCursor.x, currentCursor.y, GRAY1);
                }
                while (KEYS_PUSHING1)
                {
                }
            }
            else if (KEYS_PUSHING2)
            {
                if (currentCursor.x < POS_X_MAX)
                {
                    drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                    currentCursor.x += 1;
                    drawCursor(currentCursor.x, currentCursor.y, GRAY1);
                }
                while (KEYS_PUSHING2)
                {
                }
            }
        }
    }
    Lcd_Clear(WHITE);
}

void fun_set()
{
    int min_num_0, min_num_1;
    min_num_0 = fill_num % 10;
    min_num_1 = (fill_num - min_num_0) / 10;
    draw_set();
    while (1)
    {
        if (KEYS_PUSHING0 == KEYON)
        {
            HAL_Delay(10);
            if (KEYS_PUSHING0 == KEYON)
            {
                HAL_Delay(500);
                if (KEYS_PUSHING0 == KEYON)
                {
                    while (KEYS_PUSHING0 == KEYON)
                    {
                        fill_num = fill_num + 1;
                        min_num_0 = fill_num % 10;
                        min_num_1 = (fill_num - min_num_0) / 10;
                        Gui_DrawFont_Num32(120, 70, RED, GRAY0, min_num_0);
                        Gui_DrawFont_Num32(80, 70, RED, GRAY0, min_num_1);
                        HAL_Delay(500);
                    }
                    continue;
                }
                else
                    fill_num = fill_num + 1;
                {
                    min_num_0 = fill_num % 10;
                    min_num_1 = (fill_num - min_num_0) / 10;
                    Gui_DrawFont_Num32(120, 70, RED, GRAY0, min_num_0);
                    Gui_DrawFont_Num32(80, 70, RED, GRAY0, min_num_1);
                }
            }
        }
        if (KEYS_PUSHING1 == KEYON)
        {
            HAL_Delay(10);
            if (KEYS_PUSHING1 == KEYON)
            {
                HAL_Delay(500);
                if (KEYS_PUSHING1 == KEYON)
                {
                    while (KEYS_PUSHING1 == KEYON)
                    {
                        fill_num = fill_num - 1;
                        min_num_0 = fill_num % 10;
                        min_num_1 = (fill_num - min_num_0) / 10;
                        Gui_DrawFont_Num32(120, 70, RED, GRAY0, min_num_0);
                        Gui_DrawFont_Num32(80, 70, RED, GRAY0, min_num_1);
                        HAL_Delay(500);
                    }
                    continue;
                }
                else
                    fill_num = fill_num - 1;
                {
                    min_num_0 = fill_num % 10;
                    min_num_1 = (fill_num - min_num_0) / 10;
                    Gui_DrawFont_Num32(120, 70, RED, GRAY0, min_num_0);
                    Gui_DrawFont_Num32(80, 70, RED, GRAY0, min_num_1);
                }
            }
        }
        if (KEYS_PUSHING3 == KEYON)
        {
            HAL_Delay(10);
            if (KEYS_PUSHING3 == KEYON)
            {
                break;
            }
        }
    }
    Lcd_Clear(WHITE);
}
