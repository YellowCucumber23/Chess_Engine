#include "../global/global.h"
#include "../headers/moveGeneration.h"
#include "../headers/board.h"
#include <stdio.h>
#include <stdlib.h>

void add_quiet_move(BOARD *board, int move, MOVE_LIST *list){
    list->move[list->count].move = move;
    list->move[list->count].score = 0;
    list->count++;
}
void add_capture_move(BOARD *board, int move, MOVE_LIST *list){
    list->move[list->count].move = move;
    list->move[list->count].score = 0;
    list->count++;
}
void add_en_passant_move(BOARD *board, int move, MOVE_LIST *list){
    list->move[list->count].move = move;
    list->move[list->count].score = 0;
    list->count++;
}

void add_white_pawn_capture_move(BOARD *board, int from, int to, int cap, MOVE_LIST *list){
    if(ranks_board[from] == RANK_7){
        add_capture_move(board, create_move(from, to, cap, wQ, 0), list);
        add_capture_move(board, create_move(from, to, cap, wR, 0), list);
        add_capture_move(board, create_move(from, to, cap, wB, 0), list);
        add_capture_move(board, create_move(from, to, cap, wN, 0), list);
    } else {
        add_capture_move(board, create_move(from, to, cap, EMPTY, 0), list);
    }
}

void add_white_pawn_move(BOARD *board, int from, int to, MOVE_LIST *list){
    if(ranks_board[from] == RANK_7){
        add_capture_move(board, create_move(from, to, EMPTY, wQ, 0), list);
        add_capture_move(board, create_move(from, to, EMPTY, wR, 0), list);
        add_capture_move(board, create_move(from, to, EMPTY, wB, 0), list);
        add_capture_move(board, create_move(from, to, EMPTY, wN, 0), list);
    } else {
        add_capture_move(board, create_move(from, to, EMPTY, EMPTY, 0), list);
    }
}

void add_black_pawn_capture_move(BOARD *board, int from, int to, int cap, MOVE_LIST *list){
    if(ranks_board[from] == RANK_2){
        add_capture_move(board, create_move(from, to, cap, bQ, 0), list);
        add_capture_move(board, create_move(from, to, cap, bR, 0), list);
        add_capture_move(board, create_move(from, to, cap, bB, 0), list);
        add_capture_move(board, create_move(from, to, cap, bN, 0), list);
    } else {
        add_capture_move(board, create_move(from, to, cap, EMPTY, 0), list);
    }
}

void add_black_pawn_move(BOARD *board, int from, int to, MOVE_LIST *list){
    if(ranks_board[from] == RANK_2){
        add_capture_move(board, create_move(from, to, EMPTY, bQ, 0), list);
        add_capture_move(board, create_move(from, to, EMPTY, bR, 0), list);
        add_capture_move(board, create_move(from, to, EMPTY, bB, 0), list);
        add_capture_move(board, create_move(from, to, EMPTY, bN, 0), list);
    } else {
        add_capture_move(board, create_move(from, to, EMPTY, EMPTY, 0), list);
    }
}

void generate_all_moves(BOARD *board, MOVE_LIST *list){
    ASSERT(check_board(board));
    list->count = 0;
    int piece = EMPTY;
    int side = board->side;
    int cur_sq, temp_sq;

    if(side == WHITE){
        for(int i = 0; i < board->piece_num[wP];++i){
            cur_sq = board->piece_list[wP][i];
            ASSERT(!square_off_board(cur_sq));

            //Non capture moves
            if(board->pieces[cur_sq + 10] == EMPTY){
                add_white_pawn_move(board, cur_sq, cur_sq+10, list);
                if(ranks_board[cur_sq] == RANK_2 && board->pieces[cur_sq+20] == EMPTY){
                    add_quiet_move(board, create_move(cur_sq, cur_sq+20, EMPTY, EMPTY,get_en_passant_flag()), list);
                }
            }

            //Captures
            if(!square_off_board(cur_sq + 9) && piece_col[board->pieces[cur_sq+9]] == BLACK){
                add_white_pawn_capture_move(board, cur_sq, cur_sq+9, board->pieces[cur_sq+9], list);
            }
            if(!square_off_board(cur_sq + 11) && piece_col[board->pieces[cur_sq+11]] == BLACK){
                add_white_pawn_capture_move(board, cur_sq, cur_sq+11, board->pieces[cur_sq+11], list);
            }

            if(cur_sq + 9 == board->en_passant){
                add_capture_move(board, create_move(cur_sq, cur_sq+9, EMPTY, EMPTY, get_en_passant_flag()),list);
            }
            if(cur_sq + 11 == board->en_passant){
                add_capture_move(board, create_move(cur_sq, cur_sq+11, EMPTY, EMPTY, get_en_passant_flag()),list);
            }
        }
    } else {
        for(int i = 0; i < board->piece_num[bP];++i){
            cur_sq = board->piece_list[bP][i];
            ASSERT(!square_off_board(cur_sq));

            //Non capture moves
            if(board->pieces[cur_sq - 10] == EMPTY){
                add_black_pawn_move(board, cur_sq, cur_sq-10, list);
                if(ranks_board[cur_sq] == RANK_7 && board->pieces[cur_sq-20] == EMPTY){
                    add_quiet_move(board, create_move(cur_sq, cur_sq-20, EMPTY, EMPTY,get_en_passant_flag()), list);
                }
            }

            //Captures
            if(!square_off_board(cur_sq - 9) && piece_col[board->pieces[cur_sq - 9]] == WHITE){
                add_black_pawn_capture_move(board, cur_sq, cur_sq-9, board->pieces[cur_sq - 9], list);
            }
            if(!square_off_board(cur_sq - 11) && piece_col[board->pieces[cur_sq-11]] == WHITE){
                add_black_pawn_capture_move(board, cur_sq, cur_sq-11, board->pieces[cur_sq-11], list);
            }

            if(cur_sq - 9 == board->en_passant){
                add_capture_move(board, create_move(cur_sq, cur_sq-9, EMPTY, EMPTY, get_en_passant_flag()),list);
            }
            if(cur_sq - 11 == board->en_passant){
                add_capture_move(board, create_move(cur_sq, cur_sq-11, EMPTY, EMPTY, get_en_passant_flag()),list);
            }
        }
    }
}