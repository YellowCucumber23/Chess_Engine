#include "../headers/pvtable.h"
#include <stdio.h>

const int pv_size = 0x100000 * 2; //2 bytes

void init_pv_table(PV_TABLE *table){
    table->num_entries = pv_size / sizeof(PV_ENTRY);
    table->num_entries -= 2;

    // if(table->pv_table != NULL){
    //     free(table->pv_table);
    // }

    table->pv_table = (PV_ENTRY *) malloc(table->num_entries * sizeof(PV_ENTRY));
    clear_pv_table(table);
    printf("Made PVTABLE with %d entries\n", table->num_entries);
}

void clear_pv_table(PV_TABLE *table){
    for(PV_ENTRY* i = table->pv_table; i < table->pv_table +  table->num_entries; ++i){
        i->move = NOMOVE;
        i->position_key = 0ULL;
    }
}