#include <stdio.h>
#include <stdlib.h>
#include "headers/bitBoard.h"
#include "headers/init.h"
#include "headers/hashkey.h"
#include "headers/board.h"
#include "global/global.h"
#include "headers/attack.h"
#include "headers/output.h"

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
    int prom = bK;
    int from = A2;
    int to = H7;
    int cap = wP;

    move = (from) | (to << 7) | (cap << 14) | (prom << 20);

    printf("from: %d to: %d capture: %d promote: %d\n", get_from_move(move), get_to_move(move), get_captures(move), get_promotion(move));

    printf("Algebraic From: %s\n", print_square(from));
    printf("Algebraic To: %s\n", print_square(to));
    printf("Move: %s\n", print_move(move));
    ASSERT(check_board(board));

    return 0;
}