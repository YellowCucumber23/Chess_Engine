#include "../global/global.h"
#include "../headers/attack.h"
#include <stdio.h>

const int knight_dir[8] = { -8, -19, -21, -12, 8, 19, 21, 12 };
const int rook_dir[4] = { -1, -10,	1, 10 };
const int bishop_dir[4] = { -9, -11, 11, 9 };
const int king_dir[8] = { -1, -10,	1, 10, -9, -11, 11, 9 };

int square_attack(BOARD *board, int side, int sq){
    // if(side == WHITE){
    //     if(board->pieces[sq-9] == wP|| board->pieces[sq-11] == wP){
    //         return TRUE;
    //     }


    // }else{
    //     if(board->pieces[sq+9] == bP || board->pieces[sq+11] == bP){
    //         return TRUE;
    //     }
    // }

    int cur_sq, cur_piece;
    // //knights
    for(int i = 0; i < 8; ++i){
        cur_sq = knight_dir[i] + sq;
        cur_piece = board->pieces[cur_sq];
        if(cur_piece != OFF_BOARD && is_knight[cur_piece] && piece_col[cur_piece] == side){
            return TRUE;
        }
    }

    // // rooks and queens
    for(int i = 0; i < 4; ++i){
        cur_sq = rook_dir[i] + sq;
        cur_piece = board->pieces[cur_sq];
        while(cur_piece != OFF_BOARD){
            if(cur_piece != EMPTY){
                if(is_rook_queen[cur_piece] && piece_col[cur_piece] == side){
                    return TRUE;
                }
                break;
            }
            cur_sq += rook_dir[i];
            cur_piece = board->pieces[cur_sq];
        }
    }

    // //bishops and queens
    //bishop_dir[4] = { -9, -11, 11, 9 };
    for(int i = 0; i < 4; ++i){
        cur_sq = bishop_dir[i] + sq;
        cur_piece = board->pieces[cur_sq];
        while(cur_piece != OFF_BOARD){
            if(cur_piece != EMPTY){
                if(is_bishop_queen[cur_piece] && piece_col[cur_piece] == side){
                    return TRUE;
                }
                break;
            }
            cur_sq += bishop_dir[i];
            cur_piece = board->pieces[cur_sq];
        }
    }

    //kings
    for(int i = 0; i < 8; ++i){
        cur_sq = king_dir[i] + sq;
        cur_piece = board->pieces[cur_sq];
        if(cur_piece != OFF_BOARD && is_king[cur_piece] && piece_col[cur_piece] == side){
            return TRUE;
        }
    }

    return FALSE;
} 