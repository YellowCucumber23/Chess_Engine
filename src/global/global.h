#include <stdlib.h>

#ifndef DEFINITION_H
#define DEFINITION_H

#define NAME "tempName"
#define BOARD_SQUARE_NUM 120
#define MAX_GAME_MOVES 2048
#define MAX_POSITION_MOVES 256
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define NOMOVE 0

/*DEBUG MACRO*/
#define DEBUG
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
    if(!(n)) { \
        printf("%s - Failed",#n); \
        printf("On %s ",__DATE__); \
        printf("At %s ",__TIME__); \
        printf("In File %s ",__FILE__); \
        printf("At Line %d\n",__LINE__); \
        exit(1);}
#endif

/*GLOBAL VARIABLES*/
extern int board120[BOARD_SQUARE_NUM];
extern int board64[64];
extern unsigned long long set_mask[64];  //each index is a square on the board
extern unsigned long long clear_mask[64];

extern unsigned long long piece_key[13][120]; //13 for number of pieces, 120 for the number of positions
extern unsigned long long castle_key[16]; //15 castle keys for since represented by castle enum
extern unsigned long long side_key;

extern char piece_char[];
extern char side_char[];
extern char file_char[];
extern char rank_char[];

extern int piece_big[];
extern int piece_maj[];
extern int piece_min[];
extern int piece_val[];
extern int piece_col[];
extern int piece_pawn[];

extern int files_board[BOARD_SQUARE_NUM];
extern int ranks_board[BOARD_SQUARE_NUM];

extern int is_knight[13];
extern int is_king[13];
extern int is_rook_queen[13];
extern int is_bishop_queen[13];
extern int piece_slide[13];

/*ENUMS to make code readable*/
enum pieces {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};
enum files { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum ranks { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };

enum colors {WHITE, BLACK, BOTH};

enum board_coord{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFF_BOARD
};

enum {FALSE, TRUE};

enum castle {WK_CASTLE = 1, WQ_CASTLE = 2, BK_CASTLE = 4, BQ_CASTLE = 8};

/*MOVE DEFINITION*/
typedef struct{
    int move;
    int score;
} MOVE;

/*HISTORY DEFINITION*/
typedef struct{
    int en_passant;
    int move;
    int castle_perm;
    int fifty_move;
    unsigned long long position_key;

}HISTORY;


typedef struct{
    MOVE moves[MAX_POSITION_MOVES];
    int count;  //number of moves on the move list

}MOVE_LIST;

/* BOARD DEFINITIONS */
typedef struct {
    int pieces[BOARD_SQUARE_NUM];  //120 board representation
    unsigned long long pawns[3];   //WHITE,BLACK,BOTH where each bit is set to 1 for pawn and 0 for no pawn

    int king_square[2];  //keeps track of where the king is
    int side;         //keeps track of who's move it is
    int en_passant;   //if en passant is available
    int fifty_move;   //draw if fifty  moves
    int ply;          //number of half moves into search
    int ply_history;       //how many half moves made
    int castle_perm;  //if castle available

    unsigned long long position_key;  //unique key for each board state

    int piece_num[13]; //know number of pieces on the board

    int big_piece[2];     //not pawns
    int major_piece[2];   //Rook and queen
    int minor_piece[2];   //Bishop and knights
    int material[2];

    HISTORY history[MAX_GAME_MOVES];


    int piece_list[13][10];

}BOARD;

/*GLOBAL FUNCTIONS*/
// Convert 64 coordinates to 120
int rank_file_to_square(int rank, int file);

//fills a 64 bit integer
unsigned long long rand64();

/*
000g ffff edcc ccbb bbbb baaa aaaa
a - from move  (0x7F)
b - to move   (0x7F <<  7)
c - captures   (0xF << 14)
d - en passant (0x40000)
e - pawn start (0x80000)
f - promotion  (0xF00000) or (0xF << 20)
g - castle permission (0x1000000)
*/
int get_from_move(int move);
int get_to_move(int move);
int get_captures(int move);
int get_en_passant_flag();
int get_pawn_start_flag();
int get_promotion(int move);
int get_castle_perm_flag(); 
int get_promotion_flag();
int get_capture_flag();
int create_move(int from, int to, int cap, int prom, int fl);
int square_off_board(int sq);
#endif