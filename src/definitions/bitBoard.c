#include "../global/global.h"
#include "../headers/bitBoard.h"
#include <stdio.h>

int BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

//Print bit board
void print_bit_board(unsigned long long board){
    unsigned long long mask = 1ULL;

    for(int i = RANK_8; i >= RANK_1; --i){
        for(int j = FILE_A; j <= FILE_H; ++j){
            int sq120 = rank_file_to_square(i,j);
            int sq64 = board120[sq120];

            if((mask << sq64) & board){
                printf("X");
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
}

//Count number of bits on the board(each bit is a piece)
int count_bits(unsigned long long board){
    unsigned long long mask = 1ULL << 63;
    int num_bits = 0;
    while(mask){
        if(mask & board){
            num_bits++;
        }
        mask = mask >> 1;
    }

    return num_bits;
}

int pop_1st_bit(unsigned long long *board) {
  unsigned long long b = *board ^ (*board - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *board &= (*board - 1);
  return BitTable[(fold * 0x783a9b23) >> 26];
}

void set_bit(unsigned long long *board, int index){*board |= set_mask[index];}
void clear_bit(unsigned long long *board, int index){*board &= clear_mask[index];}
