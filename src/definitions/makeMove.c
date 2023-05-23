#include "../global/global.h"
#include "../headers/makeMove.h"
#include "../headers/validate.h"
#include <stdio.h>

static void hash_piece(BOARD *board, int piece, int sq){(board->position_key^= (piece_key[piece][sq]));}
static void hash_castle(BOARD *board){(board->position_key ^= (castle_key[board->castle_perm]));}
static void hash_side(BOARD *board){(board->position_key ^= (side_key));}
static void hash_en_passant(BOARD *board){(board->position_key ^= (piece_key[EMPTY][board->en_passant]));}

const int CastlePerm[120] = {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15,  7, 15, 15, 15,  3, 15, 15, 11, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

static void clear_piece(int sq, BOARD *board){
    ASSERT(square_on_board(sq));

    int piece = board->pieces[sq];

    ASSERT(piece_valid(piece));

    int colour = piece_col[piece];
    int temp_piece_num = -1;

    hash_piece(board, piece, sq);

    board->pieces[sq] = EMPTY;
    board->material[colour] -= piece_val[piece];

    if(piece_big[piece]){
        board->big_piece[colour]--;
        if(piece_maj[piece]){
            board->major_piece[colour]--;
        } else {
            board->minor_piece[colour]--;
        }
    }

    for(int i = 0; i < board->piece_num[piece];++i){
        if(board->piece_list[piece][i] == sq){
            temp_piece_num = i;
            break;
        }
    }
    ASSERT(temp_piece_num != -1);

    board->piece_num[piece]--;
    board->piece_list[piece][temp_piece_num] = board->piece_list[piece][board->piece_num[piece]];
}