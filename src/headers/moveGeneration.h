#include "../global/global.h"

#ifndef MOVEGENERATION_H
#define MOVEGENERATION_H

/*FUNCTION DECLARATION*/
void add_quiet_move(BOARD *board, int move, MOVE_LIST *list);
void add_capture_move(BOARD *board, int move, MOVE_LIST *list);
void add_en_passant_move(BOARD *board, int move, MOVE_LIST *list);
void add_white_pawn_capture_move(BOARD *board, int from, int to, int cap, MOVE_LIST *list);
void add_white_pawn_move(BOARD *board, int from, int to, MOVE_LIST *list);
void add_black_pawn_capture_move(BOARD *board, int from, int to, int cap, MOVE_LIST *list);
void add_black_pawn_move(BOARD *board, int from, int to, MOVE_LIST *list);
void generate_all_moves(BOARD *board, MOVE_LIST *list);
#endif