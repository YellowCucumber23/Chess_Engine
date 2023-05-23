#include "../global/global.h"

#ifndef MAKEMOVE_H
#define MAKEMOVE_H

/*FUNCTION DECLARATION*/
static void hash_piece(BOARD *board, int piece, int sq);
static void hash_castle(BOARD *board);
static void hash_side(BOARD *board);
static void hash_en_passant(BOARD *board);

static void clear_piece(int sq, BOARD *board);
#endif