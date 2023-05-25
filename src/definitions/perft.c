#include"../headers/perft.h"
#include"../global/global.h"
#include "../headers/moveGeneration.h"
#include "../headers/board.h"
#include "../headers/makeMove.h"
#include "../headers/output.h"
#include <stdio.h>

long leaf_node = 0;

void perft(BOARD *board, int depth){
    if(depth == 0){
        leaf_node++;
        return;
    }

    MOVE_LIST list[1];
    generate_all_moves(board, list);

    for(int i = 0; i <list->count; ++i){
        if(!make_move(board, list->moves[i].move)){
            continue;
        }
        perft(board, depth-1);
        take_move(board);
    }

    return;
    
}

void perft_test(BOARD *board, int depth) {
    ASSERT(check_board(board));

    print_board(board);
    printf("\nStarting Test To Depth:%d\n", depth);

    leaf_node = 0;

    MOVE_LIST list[1];
    generate_all_moves(board, list);

    int move;

    for(int i = 0; i < list->count; ++i){
        move = list->moves[i].move;
        if(!make_move(board, move)){
            continue;
        }

        long nodes = leaf_node;
        perft(board, depth-1);
        take_move(board);
        long old_node = leaf_node - nodes;
        printf("move %d : %s : %ld\n", i+1, print_move(move), old_node);
    }

    printf("\nTest Complete : %ld nodes visited\n", leaf_node);
}
