#pragma once

#include "sudoku.h"

typedef struct NakedTriple_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    Cell *p_cell3;
    int value1;
    int value2;
    int value3;
} NakedTriple;

void find_and_process_naked_triples(Cell **p_cells, NakedTriple *p_naked_triples, int *p_counter);
bool is_naked_triple(Cell *cell1, Cell *cell2, Cell *cell3, int value1, int value2, int value3);
int naked_triples(SudokuBoard *p_board);
