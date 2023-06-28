#include"../headers/output.h"
#include"../global/global.h"
#include "../headers/validate.h"
#include "../headers/moveGeneration.h"
#include <stdlib.h>
#include <stdio.h>

char *print_square(int sq){
    static char sq_char[3];

    int file = files_board[sq];
    int rank = ranks_board[sq];
    sprintf(sq_char, "%c%c", ('a'+file), ('1'+rank));

    return sq_char;
}

char *print_move(int move){
    static char moves[6];

    int file_from = files_board[get_from_move(move)];
    int rank_from = ranks_board[get_from_move(move)];
    int file_to = files_board[get_to_move(move)];
    int rank_to = ranks_board[get_to_move(move)];

    int promoted = get_promotion(move);
    if(promoted) {
        char pchar = 'q';
        if(is_knight[promoted]) {
            pchar = 'n';
        } else if(is_rook_queen[promoted] && !is_bishop_queen[promoted])  {
            pchar = 'r';
        } else if(!is_rook_queen[promoted] && is_bishop_queen[promoted])  {
            pchar = 'b';
        }
        sprintf(moves, "%c%c%c%c%c", ('a'+file_from), ('1'+rank_from), ('a'+file_to), ('1'+rank_to), pchar);
    } else {
        sprintf(moves, "%c%c%c%c", ('a'+file_from), ('1'+rank_from), ('a'+file_to), ('1'+rank_to));
    }

	return moves;

}

void print_move_list(MOVE_LIST *list){

    printf("MoveList: %2d\n", list->count);

    for(int i = 0; i < list->count; ++i){
        printf("Move: %d > %s (score: %d)\n", i+1, print_move(list->moves[i].move), list->moves[i].score);
    }
}

int parse_move(char *char_ptr, BOARD *board){
    if(char_ptr[1] > '8' || char_ptr[1] < '1') return NOMOVE;
    if(char_ptr[3] > '8' || char_ptr[3] < '1') return NOMOVE;
    if(char_ptr[0] > 'h' || char_ptr[0] < 'a') return NOMOVE;
    if(char_ptr[2] > 'h' || char_ptr[2] < 'a') return NOMOVE;

    int from = rank_file_to_square(char_ptr[1] - '1',char_ptr[0] - 'a');
    int to = rank_file_to_square(char_ptr[3] - '1',char_ptr[2] - 'a');

    printf("char: %s from: %d to: %d\n",char_ptr, from, to);
    ASSERT(square_on_board(from) && square_on_board(to));

    MOVE_LIST list[1];
    generate_all_moves(board, list);
    int move = 0;
    int prom_piece = EMPTY;

    for(int i = 0; i < list->count; ++i){
        move = list->moves[i].move;
        if(get_from_move(move) == from && get_to_move(move) == to){
            prom_piece = get_promotion(move);
            if(prom_piece != EMPTY){
                if(is_rook_queen[prom_piece] && !is_bishop_queen[prom_piece] && char_ptr[4] == 'r'){
                    return move;
                } else if(!is_rook_queen[prom_piece] && is_bishop_queen[prom_piece] && char_ptr[4] == 'b'){
                    return move;
                } else if(is_rook_queen[prom_piece] && is_bishop_queen[prom_piece] && char_ptr[4] == 'q'){
                    return move;
                } else if(is_knight[prom_piece] && char_ptr[4] == 'n'){
                    return move;
                }
                continue;
            }
            return move;
        }
    }
    return NOMOVE;
}