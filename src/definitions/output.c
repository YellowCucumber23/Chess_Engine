#include"../headers/output.h"
#include"../global/global.h"
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
        printf("Move: %d > %s (score: %d)\n", i+1, print_move(list->move[i].move), list->move[i].score);
    }
}