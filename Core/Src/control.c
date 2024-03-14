#include "control.h"

int check(int x, int y)
{
    int level_flag = 0;
    int flag_error = 0;
    if (level < 4)
    {
        level_flag = 1;
    }
    for (int i = 0; i < (9 - level_flag * 3); i++)
    {
        if ((num_mask[i][y] == add_mask[x][y]) || ((add_mask[i][y] == add_mask[x][y]) && (i != x)))
        {
            flag_error = 1;
            break;
        }
    }
    for (int i = 0; i < (9 - level_flag * 3); i++)
    {
        if ((num_mask[x][i] == add_mask[x][y]) || ((add_mask[x][i] == add_mask[x][y]) && (i != y)))
        {
            flag_error = 1;
            break;
        }
    }
    for (int i = (x / 3 * 3); i < (x / 3 * 3 + 3); i++)
    {
        for (int j = (y / (3 - level_flag) * (3 - level_flag)); j < (y / (3 - level_flag) * (3 - level_flag) + (3 - level_flag)); j++)
        {
            if ((num_mask[i][j] == add_mask[x][y]) || ((add_mask[i][j] == add_mask[x][y]) && (i != x) && (j != y)))
            {
                flag_error = 1;
                break;
            }
        }
        if (flag_error)
        {
            break;
        }
    }
    if (!flag_error) // ��д��ȷ
    {
        if (flag_mask[x][y] == 2) // �ϴ���д����
        {
            error_num -= 1;
            flag_mask[x][y] = 1;
            fill_num += 1;
        }
        else if (flag_mask[x][y] == 0) // �ϴ�û��
        {
            flag_mask[x][y] = 1;
            fill_num += 1;
        }
        // �ϴ���ȷ ����
        return 0;
    }
    else // ��д����
    {
        if (flag_mask[x][y] == 1) // �ϴ���д��ȷ
        {
            error_num += 1;
            flag_mask[x][y] = 2;
            fill_num -= 1;
        }
        else if (flag_mask[x][y] == 0) // �ϴ�û��
        {
            error_num += 1;
            flag_mask[x][y] = 2;
        }
        // �ϴδ��� ����
        return 1;
    }
}

void fun_control()
{
    int level_flag = 0;
    uint8_t error_num_str[3] = {0};
    uint8_t num_str[2] = {0};
    button1[0] = 0;
    button1[1] = 0;
    button2[0] = 0;
    if (level < 4)
    {
        level_flag = 1;
        button2[1] = 8; // ����ѡ������
    }
    else
    {
        button2[1] = 10; // ����ѡ������
    }
    currentCursor.x = 0;
    currentCursor.y = 0;
    flag = 0;
    error_num = 0;
    fill_num = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            add_mask[i][j] = 0;

    initView();
    drawCursor(currentCursor.x, currentCursor.y, GRAY1);

    while (1)
    {
        if ((KEYS_PUSHING0) || (KEYS_PUSHING1) || (KEYS_PUSHING2) || (KEYS_PUSHING3))
        {
            //HAL_Delay(150); // ����
            delay_ms(150);
            if (KEYS_PUSHING0 && KEYS_PUSHING3)
                break;
            else if (KEYS_PUSHING0 && KEYS_PUSHING1) // �����л�
            {
                if (flag)
                {
                    drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                    button2[0] = currentCursor.x;
                    button2[1] = currentCursor.y;
                    currentCursor.x = button1[0];
                    currentCursor.y = button1[1];
                    drawCursor(currentCursor.x, currentCursor.y, GRAY1);
                    if (add_mask[currentCursor.x][currentCursor.y])
                    {
                        check(currentCursor.x, currentCursor.y);
                        if (error_num > 9)
                        {
                            error_num_str[0] = '1';
                            error_num_str[1] = '0' + error_num - 10;
                            Gui_DrawFont_GBK16(112, 288, RED, WHITE, error_num_str);
                        }
                        else
                        {
                            error_num_str[0] = '0' + error_num;
                            error_num_str[1] = '\0';
                            drawBar(110, 288, 150, 320, WHITE);
                            Gui_DrawFont_GBK16(118, 288, RED, WHITE, error_num_str);
                        }
                        if (gap_num == fill_num) // �ɹ�
                        {
                            success();
                            level += 1;
                            while (1)
                            {
                                if (KEYS_PUSHING2)
                                {
                                    //HAL_Delay(20); // ����
                                    delay_ms(20);
                                    if (KEYS_PUSHING2)
                                    {
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        if (fill_num / 10)
                        {
                            error_num_str[0] = '0' + fill_num / 10;
                            error_num_str[1] = '0' + fill_num % 10;
                            Gui_DrawFont_GBK16(10, 10, RED, WHITE, error_num_str);
                        }
                        else
                        {
                            error_num_str[0] = '0' + fill_num;
                            error_num_str[1] = '\0';
                            drawBar(10, 10, 60, 30, WHITE);
                            Gui_DrawFont_GBK16(10, 10, RED, WHITE, error_num_str);
                        }
                    }
                    flag = 0;
                }
                else
                {
                    if (!num_mask[currentCursor.x][currentCursor.y])
                    {
                        drawCursor(currentCursor.x, currentCursor.y, YELLOW);
                        button1[0] = currentCursor.x;
                        button1[1] = currentCursor.y;
                        currentCursor.x = button2[0];
                        currentCursor.y = button2[1];
                        drawCursor(currentCursor.x, currentCursor.y, GRAY1);
                        flag = 1;
                    }
                }
            }
            else if (KEYS_PUSHING1 && KEYS_PUSHING2 && flag) // ѡ������
            {
                add_mask[button1[0]][button1[1]] = currentCursor.x + 1;
                num_str[0] = '0' + currentCursor.x + 1;
                Gui_DrawFont_GBK16(37 + level_flag * 30 + 20 * button1[0], 42 + level_flag * 30 + 20 * button1[1], DGREEN, YELLOW, num_str);
            }
            else if (KEYS_PUSHING0 && (!flag) && (currentCursor.y)) // ��
            {
                drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                currentCursor.y -= 1;
                drawCursor(currentCursor.x, currentCursor.y, GRAY1);
            }
            else if (KEYS_PUSHING1 && (!flag) && (currentCursor.y < (8 - level_flag * 3))) // ��
            {
                drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                currentCursor.y += 1;
                drawCursor(currentCursor.x, currentCursor.y, GRAY1);
            }
            else if (KEYS_PUSHING2 && currentCursor.x) // ��
            {
                drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                currentCursor.x -= 1;
                drawCursor(currentCursor.x, currentCursor.y, GRAY1);
            }
            else if (KEYS_PUSHING3 && (currentCursor.x < (8 - level_flag * 3))) // ��
            {
                drawCursor(currentCursor.x, currentCursor.y, GRAY0);
                currentCursor.x += 1;
                drawCursor(currentCursor.x, currentCursor.y, GRAY1);
            }
        }
    }
    Lcd_Clear(WHITE);
}

void fun_set()
{
    int color[4] = {DGREEN, DCYAN, GREEN, CYAN};
    currentCursor.x = 0;
    currentCursor.y = 0;
    draw_set();
    draw_round_cursor(currentCursor.x, currentCursor.y, RED, MAROON);
    while (1)
    {
        if ((KEYS_PUSHING0) || (KEYS_PUSHING1) || (KEYS_PUSHING2) || (KEYS_PUSHING3))
        {
            //HAL_Delay(100); // ����
            delay_ms(100);
            if (KEYS_PUSHING0 && KEYS_PUSHING1)
            {
                level = currentCursor.y * 3 + currentCursor.x + 1;
                break;
            }
            else if (KEYS_PUSHING0 && currentCursor.y)
            {
                //HAL_Delay(10);
                delay_ms(20);
                if (KEYS_PUSHING0)
                {
                    delay_ms(20);
                    //HAL_Delay(20);
                    draw_round_cursor(currentCursor.x, currentCursor.y, color[currentCursor.y + 2], color[currentCursor.y]);
                    currentCursor.y = 0;
                    draw_round_cursor(currentCursor.x, currentCursor.y, RED, MAROON);
                }
                while (KEYS_PUSHING0)
                {
                }
            }
            else if (KEYS_PUSHING1 && (!currentCursor.y))
            {
                delay_ms(20);
                //HAL_Delay(10);
                if (KEYS_PUSHING1)
                {
                    delay_ms(20);
                    //HAL_Delay(20);
                    draw_round_cursor(currentCursor.x, currentCursor.y, color[currentCursor.y + 2], color[currentCursor.y]);
                    currentCursor.y = 1;
                    draw_round_cursor(currentCursor.x, currentCursor.y, RED, MAROON);
                }
                while (KEYS_PUSHING1)
                {
                }
            }
            else if (KEYS_PUSHING2 && currentCursor.x)
            {
                delay_ms(20);
                //HAL_Delay(10);
                if (KEYS_PUSHING2)
                {
                    delay_ms(20);
                    //HAL_Delay(20);
                    draw_round_cursor(currentCursor.x, currentCursor.y, color[currentCursor.y + 2], color[currentCursor.y]);
                    currentCursor.x -= 1;
                    draw_round_cursor(currentCursor.x, currentCursor.y, RED, MAROON);
                }
                while (KEYS_PUSHING2)
                {
                }
            }
            else if (KEYS_PUSHING3 && (currentCursor.x < 2))
            {
                delay_ms(20);
                //HAL_Delay(10);
                if (KEYS_PUSHING3)
                {
                    delay_ms(20);
                    //HAL_Delay(20);
                    draw_round_cursor(currentCursor.x, currentCursor.y, color[currentCursor.y + 2], color[currentCursor.y]);
                    currentCursor.x += 1;
                    draw_round_cursor(currentCursor.x, currentCursor.y, RED, MAROON);
                }
                while (KEYS_PUSHING3)
                {
                }
            }
        }
    }
    Lcd_Clear(WHITE);
}
