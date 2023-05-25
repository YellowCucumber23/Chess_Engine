#include "../global/global.h"
#include "../headers/board.h"
#include "../headers/hashkey.h"
#include "../headers/bitBoard.h"
#include <stdio.h>
//reset the board to starting positions
void reset_board(BOARD *board){
    for(int i = 0; i < BOARD_SQUARE_NUM; ++i){
        board->pieces[i] = OFF_BOARD;
    }      

    for(int i = 0; i < 64; ++i){
        board->pieces[board64[i]] = EMPTY;
    }
    for(int i = 0; i < 3;++i){
        board->pawns[i] = 0ULL;
        if(i < 2){
            board->big_piece[i] = 0;
            board->major_piece[i] = 0;
            board->minor_piece[i] = 0;
            board->material[i] = 0;
        }
    }

    board->king_square[0] = 0;
    board->king_square[1] = 0;
    board->side = BOTH;
    board->en_passant = NO_SQ;
    board->fifty_move = 0;
    board->ply = 0;
    board->ply_history = 0;
    board->castle_perm = FALSE;
    board->position_key = 0;
    for(int i = 0; i < 13;++i){
        board->piece_num[i] = 0;
    }
}

//parses a fen value
int parse_fen(char *fen, BOARD *board){
    ASSERT(fen != NULL);
    ASSERT(board != NULL);

    int rank = RANK_8;
    int file = FILE_A;
    int piece = 0;
    int count = 0;
    int sq64 = 0;
    int sq120 = 0;

    reset_board(board);

    //Parse the board positions
    while(*fen && rank >= RANK_1){
        count = 1;
        if (*fen == 'p') piece = bP;
        else if (*fen == 'r') piece = bR;
        else if (*fen == 'n') piece = bN;
        else if (*fen == 'b') piece = bB;
        else if (*fen == 'k') piece = bK;
        else if (*fen == 'q') piece = bQ;
        else if (*fen == 'P') piece = wP;
        else if (*fen == 'R') piece = wR;
        else if (*fen == 'N') piece = wN;
        else if (*fen == 'B') piece = wB;
        else if (*fen == 'K') piece = wK;
        else if (*fen == 'Q') piece = wQ;
        else if (*fen >= '1' && *fen <= '8'){
            piece = EMPTY;
            count = *fen - '0';
        }else if (*fen == '/' || *fen == ' ') {
            rank--;
            file = FILE_A;
            fen++;
            continue;
        }   

        for(int j = 0; j < count; ++j){
            sq64 = 8*rank + file;      //48
            sq120 = board64[sq64];   //81
            if(piece != EMPTY){
                board->pieces[sq120] = piece;
            }
            file++;
        }
        fen++;
    }

    ASSERT(*fen == 'w' || *fen == 'b');

    //parse the permissions
    if(*fen == 'w'){
        board->side = WHITE;
    } else {
        board->side = BLACK;
    }
    fen += 2;

    for(int i = 0; i < 4;++i){
        if(*fen == ' ') break;
        if(*fen == 'K') board->castle_perm |= WK_CASTLE;
        if(*fen == 'Q') board->castle_perm |= WQ_CASTLE;
        if(*fen == 'k') board->castle_perm |= BK_CASTLE;
        if(*fen == 'q') board->castle_perm |= BQ_CASTLE;
        fen++;
    }
    fen++;

    ASSERT(board->castle_perm>=0 && board->castle_perm <= 15);
    if(*fen != '-'){
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file>=FILE_A && file <= FILE_H);
		ASSERT(rank>=RANK_1 && rank <= RANK_8);
        board->en_passant = rank_file_to_square(rank, file);
    }

    board->position_key = generate_key(board);
    update_material_list(board);

    return 0;
}


void print_board(const BOARD *board){
    int cur_sq = 0;
    int piece = 0;
    for(int i = RANK_8; i >= RANK_1; --i){
        printf("%3d", i+1);
        for(int j = FILE_A; j <= FILE_H; ++j){
            cur_sq = rank_file_to_square(i,j);  //91
            piece = board->pieces[cur_sq];    
            printf("%3c", piece_char[piece]);
        }
        printf("\n");
    }
    printf("\n   ");
    for(int i = FILE_A; i <= FILE_H; ++i){
        printf("%3c", 'a'+i);
    }
	printf("\n");
	printf("side:%c\n",side_char[board->side]);
	printf("enPas:%d\n",board->en_passant);
	printf("castle:%c%c%c%c\n",
			board->castle_perm & WK_CASTLE ? 'K' : '-',
			board->castle_perm & WQ_CASTLE ? 'Q' : '-',
			board->castle_perm & BK_CASTLE ? 'k' : '-',
			board->castle_perm & BQ_CASTLE ? 'q' : '-'
			);
	printf("PosKey:%llX\n",board->position_key);
}

void update_material_list(BOARD *board){
    int piece = 0;
    int colour = 0;
    for(int i = 0; i < BOARD_SQUARE_NUM; ++i){
        piece = board->pieces[i];

        if(piece != OFF_BOARD && piece != EMPTY){
            colour = piece_col[piece];
            if(piece_big[piece] == TRUE) board->big_piece[colour]++;
            if(piece_maj[piece] == TRUE) board->major_piece[colour]++;
            if(piece_min[piece] == TRUE) board->minor_piece[colour]++;
            board->material[colour] += piece_val[piece];

            //Piece List
            board->piece_list[piece][board->piece_num[piece]] = i;
            board->piece_num[piece]++;

            if(piece == wK) board->king_square[WHITE] = i;
            if(piece == bK) board->king_square[BLACK] = i;

            if(piece == wP){
                set_bit(&board->pawns[WHITE], board120[i]);
                set_bit(&board->pawns[BOTH], board120[i]);
            }else if(piece == bP){  //81
                set_bit(&board->pawns[BLACK], board120[i]);
                set_bit(&board->pawns[BOTH], board120[i]);
            }
        }

    }
}

int check_board(BOARD *board) {

	int t_pceNum[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int t_bigPce[2] = { 0, 0};
	int t_majPce[2] = { 0, 0};
	int t_minPce[2] = { 0, 0};
	int t_material[2] = { 0, 0};

	int sq64,t_piece,t_pce_num,sq120,colour,pcount;

	unsigned long long t_pawns[3] = {0ULL, 0ULL, 0ULL};

	t_pawns[WHITE] = board->pawns[WHITE];
	t_pawns[BLACK] = board->pawns[BLACK];
	t_pawns[BOTH] = board->pawns[BOTH];

	// check piece lists
	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		for(t_pce_num = 0; t_pce_num < board->piece_num[t_piece]; ++t_pce_num) {
			sq120 = board->piece_list[t_piece][t_pce_num];
			ASSERT(board->pieces[sq120]==t_piece);
		}
	}

	// check piece count and other counters
	for(sq64 = 0; sq64 < 64; ++sq64) {
		sq120 = board64[sq64];
		t_piece = board->pieces[sq120];
		t_pceNum[t_piece]++;
		colour = piece_col[t_piece];

		if( piece_big[t_piece] == TRUE) t_bigPce[colour]++;
		if( piece_min[t_piece] == TRUE) t_minPce[colour]++;
		if( piece_maj[t_piece] == TRUE) t_majPce[colour]++;

		t_material[colour] += piece_val[t_piece];
	}

	for(t_piece = wP; t_piece <= bK; ++t_piece) {
        ASSERT(t_pceNum[t_piece]==board->piece_num[t_piece]);
	}

	// check bitboards count
	pcount = count_bits(t_pawns[WHITE]);
	ASSERT(pcount == board->piece_num[wP]);
	pcount = count_bits(t_pawns[BLACK]);
	ASSERT(pcount == board->piece_num[bP]);
	pcount = count_bits(t_pawns[BOTH]);
	ASSERT(pcount == (board->piece_num[bP] + board->piece_num[wP]));

	// check bitboards squares
	while(t_pawns[WHITE]) {
		sq64 = pop_1st_bit(&t_pawns[WHITE]);
		ASSERT(board->pieces[board64[sq64]] == wP);
	}

	while(t_pawns[BLACK]) {
		sq64 = pop_1st_bit(&t_pawns[BLACK]);
		ASSERT(board->pieces[board64[sq64]] == bP);
	}

	while(t_pawns[BOTH]) {
		sq64 = pop_1st_bit(&t_pawns[BOTH]);
		ASSERT( (board->pieces[board64[sq64]] == bP) || (board->pieces[board64[sq64]] == wP) );
	}

	ASSERT(t_material[WHITE]==board->material[WHITE] && t_material[BLACK]==board->material[BLACK]);

	ASSERT(t_minPce[WHITE]==board->minor_piece[WHITE] && t_minPce[BLACK]==board->minor_piece[BLACK]);
	ASSERT(t_majPce[WHITE]==board->major_piece[WHITE] && t_majPce[BLACK]==board->major_piece[BLACK]);
	ASSERT(t_bigPce[WHITE]==board->big_piece[WHITE] && t_bigPce[BLACK]==board->big_piece[BLACK]);

	ASSERT(board->side==WHITE || board->side==BLACK);

	// ASSERT(generate_key(board)==board->position_key);

	ASSERT(board->en_passant==NO_SQ || ( ranks_board[board->en_passant]==RANK_6 && board->side == WHITE)
		 || ( ranks_board[board->en_passant]==RANK_3 && board->side == BLACK));

	ASSERT(board->pieces[board->king_square[WHITE]] == wK);
	ASSERT(board->pieces[board->king_square[BLACK]] == bK);

	ASSERT(board->castle_perm >= 0 && board->castle_perm <= 15);

	return TRUE;
}
