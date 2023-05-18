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