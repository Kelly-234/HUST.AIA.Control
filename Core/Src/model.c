#include "model.h"

int num_mask[9][9] = {{0, 0, 0, 0, 0, 8, 0, 4, 9}, {4, 9, 8, 6, 1, 0, 5, 0, 0}, {3, 2, 0, 0, 0, 0, 7, 8, 0}, {0, 0, 0, 1, 0, 0, 4, 9, 0}, {7, 0, 0, 0, 5, 0, 3, 0, 0}, {0, 3, 0, 2, 6, 4, 8, 7, 1}, {5, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 5, 8, 6, 0, 0, 0}, {0, 0, 0, 0, 3, 1, 2, 0, 7}};
int add_mask[9][9];
int flag_mask[9][9];
int button1[2] = {0, 0};  // 数独区域
int button2[2] = {0, 10}; // 数字选择区域
int flag = 0;             // 0指数独区域，1指数字选择区域
int open_sum;
int fill_num = 0;
int gap_num = 81;
int flag_num;
int game_over;
int error_num = 0;
int max_error_num = 15;

pos currentCursor;