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
#include "headers/search.h"

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN2 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define KNIGHTKING "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N w - - 0 1"


int board120[BOARD_SQUARE_NUM];
int board64[64];

int main(){
    init();
    BOARD board[1];
    MOVE_LIST list[1];
    char input[6];

    parse_fen(START_FEN, board);
    int move = NOMOVE;
    while(TRUE){
        print_board(board);
        printf("Enter a Move: ");
        fgets(input, 6, stdin);

        if(input[0] == 'q'){
            break;
        } else if(input[0] == 't'){
            take_move(board);
        } else{
            move = parse_move(input, board);
            if(move != NOMOVE){
                make_move(board, move);
                if(is_repetition(board)){
                    printf("REP SEEN\n");
                }
            } else {
                printf("Move Not Parsed:%s\n", input);
            }
        }
        fflush(stdin);

    }

    
    return 0;
}