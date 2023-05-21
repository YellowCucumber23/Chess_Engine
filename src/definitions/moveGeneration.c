#include "../global/global.h"
#include "../headers/moveGeneration.h"
#include "../headers/board.h"
#include "../headers/validate.h"
#include "../headers/output.h"
#include <stdio.h>
#include <stdlib.h>

int loop_slide_piece[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0};
int loop_slide_index[2] = {0,4};
int loop_no_slide_piece[6] = {wN, wK, 0, bN, bK, 0};
int loop_no_slide_index[2] = {0,3};

int piece_dir[13][8] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19, -21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19, -21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10, 1, 10, 0, 0, 0, 0 },
	{ -1, -10, 1, 10, -9, -11, 11, 9 },
	{ -1, -10, 1, 10, -9, -11, 11, 9 }
}; 

const int num_dir[13] = {0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};

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
    ASSERT(piece_valid_empty(cap));
    ASSERT(square_on_board(from));
    ASSERT(square_on_board(to));

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
    ASSERT(square_on_board(from));
    ASSERT(square_on_board(to));
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
    ASSERT(piece_valid_empty(cap));
    ASSERT(square_on_board(from));
    ASSERT(square_on_board(to));
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
    ASSERT(square_on_board(from));
    ASSERT(square_on_board(to));
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
    int cur_sq;

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

    //Sliding Pieces
    int dir, piece_index = 0;
    int slide_piece = 0;

    piece_index = loop_slide_index[side];
    slide_piece = loop_slide_piece[piece_index++];
    while(slide_piece != 0){
        ASSERT(piece_valid(slide_piece));
        printf("Sliders Piece Index: %d Piece: %d\n", piece_index, slide_piece);
        slide_piece = loop_slide_piece[piece_index++];
    }

    //Non-sliding piece
    int no_slide_piece = 0;

    piece_index = loop_no_slide_index[side];
    no_slide_piece = loop_no_slide_piece[piece_index++];
    while(no_slide_piece != 0){
        ASSERT(piece_valid(no_slide_piece));
        for(int i = 0; i < board->piece_num[no_slide_piece]; ++i){
            cur_sq = board->piece_list[no_slide_piece][i];
            ASSERT(square_on_board(cur_sq));
            printf("Piece:%c on Square:%s\n", piece_char[no_slide_piece],print_square(cur_sq));

            for(int j = 0; j < num_dir[no_slide_piece]; ++j){
                dir = piece_dir[no_slide_piece][j];

                if(square_off_board(dir + cur_sq)){
                    continue;
                }

                if(board->pieces[cur_sq + dir] != EMPTY){
                    if(piece_col[board->pieces[cur_sq + dir]] == (side ^ 1)){
                        printf("\tCapture on:%s\n", print_square(cur_sq+dir));
                    }
                    continue;
                }
                printf("\tNormal on:%s\n", print_square(cur_sq+dir));
            }
        }

        no_slide_piece = loop_no_slide_piece[piece_index++];
    }
}   