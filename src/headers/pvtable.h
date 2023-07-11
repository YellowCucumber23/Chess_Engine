#include "../global/global.h"

#ifndef PVTABLE_H
#define PVTABLE_H
void init_pv_table(PV_TABLE *table);
void clear_pv_table(PV_TABLE *table);
void store_pv_move(BOARD *board, int move);
int probe_pv_table(BOARD *board);
#endif
