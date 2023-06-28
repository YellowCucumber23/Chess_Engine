#include "../global/global.h"

#ifndef OUTPUT_H
#define OUTPUT_H
char *print_square(int sq);
char *print_move(int sq);
void print_move_list(MOVE_LIST *list);
int parse_move(char *char_ptr, BOARD *board);
#endif
