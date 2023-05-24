#include "../global/global.h"
#include "../headers/makeMove.h"
#include "../headers/validate.h"
#include "../headers/bitBoard.h"
#include "../headers/board.h"
#include "../headers/attack.h"
#include <stdio.h>

static void hash_piece(BOARD *board, int piece, int sq){(board->position_key^= (piece_key[piece][sq]));}
static void hash_castle(BOARD *board){(board->position_key ^= (castle_key[board->castle_perm]));}
static void hash_side(BOARD *board){(board->position_key ^= (side_key));}
static void hash_en_passant(BOARD *board){(board->position_key ^= (piece_key[EMPTY][board->en_passant]));}

const int castle_perm[120] = {
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
    } else{
        clear_bit(&board->pawns[colour], board120[sq]);
        clear_bit(&board->pawns[BOTH], board120[sq]);
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

static void add_piece(BOARD *board, int sq, int piece){
    ASSERT(piece_valid(piece));
    ASSERT(square_on_board(sq));
    int colour = piece_col[piece];
    hash_piece(board, piece, sq);

    board->pieces[sq] = piece;
    board->material[colour] += piece_val[piece];

    if(piece_big[piece]){
        board->big_piece[colour]++;
        if(piece_maj[piece]){
            board->major_piece[colour]++;
        } else {
            board->minor_piece[colour]++;
        }
    } else {
        set_bit(&board->pawns[colour], board120[sq]);
        set_bit(&board->pawns[BOTH], board120[sq]);
    }

    board->material[colour] += piece_val[piece];
    board->piece_list[piece][board->piece_num[piece]++] = sq;
}

static void move_piece(BOARD *board, int from, int to){
    ASSERT(square_on_board(from));
    ASSERT(square_on_board(to));
    int piece = board->pieces[from];
    int colour = piece_col[piece];

#ifdef DEBUG
    int temp_piece_num = EMPTY;
#endif
    hash_piece(board, piece, from);
    board->pieces[from] = EMPTY;

    hash_piece(board, piece, to);
    board->pieces[to] = piece;

    if(!piece_big[piece]){
        clear_bit(&board->pawns[colour], from);
        clear_bit(&board->pawns[BOTH], from);
        set_bit(&board->pawns[colour], to);
        set_bit(&board->pawns[BOTH], to);
    }

    for(int i = 0; i < board->piece_num[piece]; ++i){
        if(board->piece_list[piece][i] == from){
            board->piece_list[piece][i] = to;
#ifdef DEBUG
            temp_piece_num = TRUE;
#endif

            break;
        }
    }

    ASSERT(temp_piece_num);
}

int make_move(BOARD *board, int move){
    ASSERT(check_board(board));

    int from = get_from_move(move);
    int to = get_to_move(move);
    int side = board->side;

    ASSERT(square_on_board(from));
    ASSERT(square_on_board(to));
    ASSERT(side_valid(side));
    ASSERT(piece_valid(board->pieces[from]));

    board->history[board->ply_history].position_key = board->position_key;

    if(move & get_en_passant_flag()){
        if(side == WHITE){
            clear_piece(to-10,board);
        } else{
            clear_piece(to+10, board);
        }
    } else if(move & get_castle_perm_flag()){
        if(to == C1){
            move_piece(board, A1, D1);
        } else if(to == C8){
            move_piece(board, A8, D8);
        } else if(to == G1){
            move_piece(board, H1, F1);
        } else if(to == G8){
            move_piece(board, A8, D8);
        } else {
            ASSERT(FALSE);
        }
    }
    if(board->en_passant != NO_SQ){hash_en_passant(board);}

    hash_castle(board);

    board->history[board->ply_history].move = move;
    board->history[board->ply_history].fifty_move = board->fifty_move;
    board->history[board->ply_history].en_passant = board->en_passant;
    board->history[board->ply_history].castle_perm = board->castle_perm;

    board->castle_perm &= castle_perm[from];
    board->castle_perm &= castle_perm[to];
    board->en_passant = NO_SQ;

    hash_castle(board);

    int capture = get_captures(move);
    board->fifty_move++;

    if(capture != EMPTY){
        ASSERT(piece_valid(capture));
        clear_piece(to, board);
        board->fifty_move = 0;
    }

    board->ply_history++;
    board->ply++;
    
    if(piece_pawn[board->pieces[from]]){
        board->fifty_move = 0;
        if(move & get_pawn_start_flag()){
            if(side == WHITE){
                board->en_passant = from + 10;
                ASSERT(ranks_board[board->en_passant] == RANK_3);
            } else {
                board->en_passant = from - 10;
                ASSERT(ranks_board[board->en_passant] == RANK_6);
            }
            hash_en_passant(board);
        } 
    }
    move_piece(board, from, to);

    int promote = get_promotion(move);
    if(promote != EMPTY){
        ASSERT(piece_valid(promote) && !piece_pawn[promote]);
        clear_piece(to, board);
        add_piece(board, to, promote);
    }

    if(is_king[board->pieces[to]]){
        board->king_square[board->side] = to;
    }

    board->side ^= 1;
    hash_side(board);

    ASSERT(check_board(board));

    if(square_attack(board, board->side, board->king_square[side])){
        // take_move(board);
        return FALSE;
    }

    return TRUE;
}

void take_move(BOARD *board){
    ASSERT(check_board(board));
    board->ply--;
    board->ply_history--;

    int move = board->history[board->ply_history].move;
    int to = get_to_move(move);
    int from = get_from_move(move);

    ASSERT(square_on_board(from));
    ASSERT(square_on_board(to));

    if(board->en_passant != NO_SQ){
        hash_en_passant(board);
    }
    hash_castle(board);

    board->castle_perm = board->history[board->ply_history].castle_perm;
    board->fifty_move = board->history[board->ply_history].fifty_move;
    board->en_passant = board->history[board->ply_history].en_passant;

    if(board->en_passant != NO_SQ){
        hash_en_passant(board);
    }
    hash_castle(board);

    board->side ^= 1;
    hash_side(board);

    if(get_en_passant_flag() & move){
        if(board->side == WHITE){
            add_piece(board, to - 10, bP);
        } else {
            add_piece(board, to + 10, wP);
        }
    } else if(move & get_castle_perm_flag()){
        if(to == C1){
            move_piece(board, A1, D1);
        } else if(to == C8){
            move_piece(board, A8, D8);
        } else if(to == G1){
            move_piece(board, H1, F1);
        } else if(to == G8){
            move_piece(board, A8, D8);
        } else {
            ASSERT(FALSE);
        }
    }
    move_piece(board, from, to);

    if(is_king[board->pieces[from]]){
        board->king_square[board->side] = from;
    }

    int capture = get_captures(move);
    if(capture != EMPTY){
        ASSERT(piece_valid(capture));
        add_piece(board, to, capture);
    }

    int promote = get_promotion(move);

    if(promote != EMPTY){
        ASSERT(piece_valid(promote) && !piece_pawn[promote]);
        clear_piece(from, board);
        add_piece(board, from, (piece_col[promote] == WHITE) ? wP : bP);
    }

    ASSERT(check_board);

}