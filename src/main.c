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
#include "headers/makeMove.h"
#include "headers/perft.h"

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN2 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define KNIGHTKING "3rk2r/8/8/8/8/8/6p1/R3K2R b KQk - 0 1"


int board120[BOARD_SQUARE_NUM];
int board64[64];


int main(){
    init();
    BOARD board[1];
    MOVE_LIST list[1];
    parse_fen(START_FEN, board);
    perft_test(board, 3);

    
    ASSERT(check_board(board));
    return 0;
}