#ifndef __MODEL_H
#define __MODEL_H

#include "def.h"
typedef struct
{
    int x;
    int y;
} pos;
typedef struct
{
    uint8_t current;             // ��ǰ
    uint8_t up;                  // �ϲ�˵�
    uint8_t down;                // �²�˵�
    uint8_t enter;               // ����
    uint8_t back;                // ����
    void (*current_operation)(); // ������õĺ���
} key_table;
extern int num_mask[9][9];
extern int add_mask[9][9];
extern int flag_mask[9][9];
extern int button1[2];
extern int button2[2];
extern int open_sum;
extern int fill_num;
extern int gap_num;
extern int flag_num;
extern int error_num;
extern int max_error_num;
extern int game_over;
extern int flag;
extern pos currentCursor;

#define POS_X_MIN 0
#define POS_X_MAX 8
#define POS_Y_MIN 0
#define POS_Y_MAX 8
#define CURSORCOLOR GRAY1
#define SEED 6991

#endif