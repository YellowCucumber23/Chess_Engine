#include <stdio.h>
#include <stdlib.h>
#include "headers/bitBoard.h"
#include "headers/init.h"
#include "headers/hashkey.h"
#include "headers/board.h"
#include "global/global.h"
#include "headers/attack.h"

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN2 "7k/8/3q4/8/4Q3/8/8/K7 b - - 3 2"

int board120[BOARD_SQUARE_NUM];
int board64[64];


void show_attacks(int side, BOARD *board){
    int cur_sq;
    for(int i = RANK_8; i >= RANK_1; --i){
        for(int j = FILE_A; j <= FILE_H; ++j){
            cur_sq = rank_file_to_square(i,j);
            if(square_attack(board, side, cur_sq) == TRUE){
                printf("X");
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
}


int main(){
    init();
    BOARD board[1];
;
    parse_fen(START_FEN, board);
    // print_board(board);
    show_attacks(WHITE, board);
    // print_board(board);
    printf("\n\n");
    show_attacks(BLACK, board);

    // printf("%d", rank_file_to_square(7,7));
    // square_attack(board, WHITE,61);
    ASSERT(check_board(board));

    return 0;
}