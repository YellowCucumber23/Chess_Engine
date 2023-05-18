

#ifndef BITBOARD_H
#define BITBOARD_H


/*FUNCTION DECLARATION*/
void print_bit_board(unsigned long long board);
int count_bits(unsigned long long board);
int pop_1st_bit(unsigned long long *board);
void set_bit(unsigned long long *board, int index);
void clear_bit(unsigned long long *board, int index);

#endif