#include "global.h"

//return 120 based index
int rank_file_to_square(int rank, int file){
    return ((file+21) + (rank*10));
}

unsigned long long rand64(){
    return ((unsigned long long)rand() |
            ((unsigned long long)rand() << 15) |
            ((unsigned long long)rand() << 30) |
            ((unsigned long long)rand() << 45) |
            (((unsigned long long)rand() & 0xf) << 60)
    );
}

int get_from_move(int move){return(move & 0x7F);}
int get_to_move(int move){return ((move >> 7) & 0x7F);}
int get_captures(int move){return ((move >> 14) & 0xF);}
int get_promotion(int move){return ((move >> 20) & 0xF);}
int get_en_passant_flag(){return 0x40000;}
int get_pawn_start_flag(){return 0x80000;}
int get_castle_perm_flag(){return 0x1000000;} 
int get_promotion_flag(){return 0xF00000;}
int get_capture_flag(){return 0x7C000;}