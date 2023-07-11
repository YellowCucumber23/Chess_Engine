#include "../headers/pvtable.h"
#include <stdio.h>

const int pv_size = 0x100000 * 2; //2 bytes

void init_pv_table(PV_TABLE *table){
    table->num_entries = pv_size / sizeof(PV_ENTRY);
    table->num_entries -= 2;

    // if(table->pv_table != NULL){
    //     free(table->pv_table);
    // }

    table->pv_entry = (PV_ENTRY *) malloc(table->num_entries * sizeof(PV_ENTRY));
    clear_pv_table(table);
    printf("Made PVTABLE with %d entries\n", table->num_entries);
}

void clear_pv_table(PV_TABLE *table){
    for(PV_ENTRY* i = table->pv_entry; i < table->pv_entry +  table->num_entries; ++i){
        i->move = NOMOVE;
        i->position_key = 0ULL;
    }
}

void store_pv_move(BOARD *board, int move){
    int index = board->position_key % board->pv_table->num_entries;
    ASSERT(index >= 0 && index <= board->pv_table->num_entries);

    board->pv_table->pv_entry[index].move = move;
    board->pv_table->pv_entry[index].position_key = board->position_key;
}

int probe_pv_table(BOARD *board){
    int index = board->position_key % board->pv_table->num_entries;
    ASSERT(index >= 0 && index <= board->pv_table->num_entries);

    if(board->pv_table->pv_entry[index].position_key == board->position_key){
        return board->pv_table->pv_entry[index].move;
    }

    return NOMOVE;
}