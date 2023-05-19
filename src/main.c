#include <stdio.h>
#include <stdlib.h>
#include "headers/bitBoard.h"
#include "headers/init.h"
#include "headers/hashkey.h"
#include "headers/board.h"
#include "global/global.h"
#include "headers/attack.h"
#include "headers/output.h"
#include "headers/moveGeneration.h"

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN2 "r2k3r/p1pp1Pb1/bn3np1/2q1N3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQ - 1 3"

int board120[BOARD_SQUARE_NUM];
int board64[64];

void print_bin(int temp){
    printf("\nAs Binary: ");

    for(int i = 28; i >= 0; --i){
        if((1<<i) & temp) printf("1");
        else printf("0");
        if(i !=28 && i%4 ==0) printf(" ");
    }
    printf("\n");
}


int main(){
    init();
    BOARD board[1];
    MOVE_LIST list[1];
    parse_fen(FEN2, board);
    print_board(board);

    generate_all_moves(board,list);
    print_move_list(list);

    ASSERT(check_board(board));

    return 0;
}