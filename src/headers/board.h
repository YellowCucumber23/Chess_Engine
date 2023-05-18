#include "../global/global.h"
#ifndef BOARD_H
#define BOARD_H

/*FUNCTION DECLARATION*/
void reset_board(BOARD *board);
int parse_fen(char *fen, BOARD *board);
void print_board(const BOARD *board);
void update_material_list(BOARD *board);
int check_board(BOARD *board);
#endif