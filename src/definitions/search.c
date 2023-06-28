#include "../headers/search.h"
#include <stdio.h>

int is_repetition(BOARD *board){
    for(int i = board->ply_history - board->fifty_move; i < board->ply_history;++i){
        if(board->position_key == board->history[i].position_key){
            return TRUE;
        }
    }
    return FALSE;
}

void search_position(BOARD *board){

}