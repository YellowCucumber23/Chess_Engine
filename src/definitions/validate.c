#include "../headers/validate.h"
#include "../global/global.h"


int square_on_board(int sq){
    return files_board[sq] == OFF_BOARD ? 0 : 1;
}
int side_valid(int side){
    return (side == WHITE || side == BLACK) ? 1 : 0;
}
int file_rank_valid(int fr){
    return (fr >= 1 && fr <= 7) ? 1 : 0;
}
int piece_valid_empty(int piece){
    return(piece >= EMPTY && piece <= bK) ? 1 : 0;
}
int piece_valid(int piece){
    return(piece >= wP && piece <= bK) ? 1 : 0;
}
