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
    parse_fen(START_FEN, board);
    int move = 0;
    int from = 6;
    int to = 12;
    int capture = wR;
    int promote = bR;

    move = (from) | (to << 7) | (capture << 14) | (promote << 20);

    printf("\ndec:%d hex:%X\n", move, move);
    print_bin(move);

    printf("from:");
    printf("%2d",get_from_move(move));
    printf("\n");

    printf("to:");
    printf("%2d",get_to_move(move));
    printf("\n");

    printf("capture:");
    printf("%2d",get_captures(move));
    printf("\n");

    printf("promote:");
    printf("%2d",get_promotion(move));
    printf("\n");
    
    ASSERT(check_board(board));

    return 0;
}