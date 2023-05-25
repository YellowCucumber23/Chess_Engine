#include "../global/global.h"
#include "../headers/hashkey.h"
#include "../headers/validate.h"
#include <stdio.h>

unsigned long long piece_key[13][120]; //13 for number of pieces, 120 for the number of positions
unsigned long long castle_key[16]; //15 castle keys for since represented by castle enum
unsigned long long side_key;

unsigned long long generate_key(const BOARD *board){
    unsigned long long final_key = 0;
    int piece = EMPTY;

    for(int i = 0; i < BOARD_SQUARE_NUM; ++i){   //Iterate through the board and hash each non-empty square
        piece = board->pieces[i];
        if(piece != EMPTY && piece != NO_SQ && piece != OFF_BOARD){
            final_key ^= piece_key[piece][i];
        }
    }

    if(board->side == WHITE){ //Hash if it is white move
            final_key ^= side_key;
    }

    if(board->en_passant != NO_SQ){  //hash if en passant available, stored in 0 index
        ASSERT(board->en_passant >= 0 && board->en_passant < BOARD_SQUARE_NUM);
		ASSERT(square_on_board(board->en_passant));
		ASSERT(ranks_board[board->en_passant] == RANK_3 || ranks_board[board->en_passant] == RANK_6);
        final_key ^= piece_key[EMPTY][board->en_passant];
    }

    final_key ^= castle_key[board->castle_perm];

    return final_key;
}