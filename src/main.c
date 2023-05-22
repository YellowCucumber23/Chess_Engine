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
#define FEN2 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

int board120[BOARD_SQUARE_NUM];
int board64[64];


int main(){
    init();
    BOARD board[1];
    MOVE_LIST list[1];
    parse_fen(FEN2, board);
    generate_all_moves(board,list);
    print_move_list(list);

    ASSERT(check_board(board));

    return 0;
}