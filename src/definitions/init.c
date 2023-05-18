#include "../global/global.h"
#include "../headers/init.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long long set_mask[64];
unsigned long long clear_mask[64];

unsigned long long piece_key[13][120];
unsigned long long castle_key[16];
unsigned long long side_key;

int ranks_board[BOARD_SQUARE_NUM];
int files_board[BOARD_SQUARE_NUM];
/*FUNCTION DEFINITION*/
//Initialize main.c
void init(){
    init_board();
    init_hash_key();
    init_bit_mask();
    init_files_ranks();
}

//Initialize board
void init_board(){
    for(int i = 0; i < BOARD_SQUARE_NUM; ++i){board120[i] = 65;}   //set 64 square and 120 square boards to values
    for(int i = 0; i < 64; ++i){board64[i] = 120;}                 //see boards.txt for example initialization

    int temp;
    int counter = 0;
    for(int i = RANK_1; i <= RANK_8; ++i){
        for(int j = FILE_A; j <= FILE_H; ++j){
            temp = rank_file_to_square(i,j);
            board120[temp] = counter;
            board64[counter] = temp;
            counter++;
        }
    }
}

void init_bit_mask(){
    for(int i = 0; i < 64; ++i){
        set_mask[i] = 0ULL;
        clear_mask[i] = 0ULL;
    }

    for(int i = 0; i < 64; ++i){
        set_mask[i] |= (1ULL << i);
        clear_mask[i] = ~set_mask[i];
    }
}

//sets each index to a random value for hashing
void init_hash_key(){
    for(int i = 0; i < 13;++i){
        for(int j = 0; j < 120;++j){
            piece_key[i][j] = rand64();
        }
    }

    for(int i = 0; i < 16; ++i){
        castle_key[i] = rand64();
    }
}

//initialize files and ranks
void init_files_ranks(){
    int sq = 0;
    for(int i = 0; i < BOARD_SQUARE_NUM; ++i){
        files_board[i] = OFF_BOARD;
        ranks_board[i] = OFF_BOARD;
    }
    for(int i = RANK_8; i >= RANK_1; --i){
        for(int j = FILE_A; j <= FILE_H; ++j){
            sq = rank_file_to_square(i,j);
            files_board[sq] = j;
            ranks_board[sq] = i;
        }
    }

}