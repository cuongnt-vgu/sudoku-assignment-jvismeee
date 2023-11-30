#pragma once

#include "sudoku.h"

typedef struct NakedPair_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    int value1;
    int value2;
} NakedPair;

int naked_pairs(SudokuBoard *p_board);
// int find_naked_pairs_values(Cell **p_cells, int *naked_pairs_values);
// bool is_naked_pair(Cell *cell1, Cell *cell2, int value1, int value2);
// void find_naked_pairs(Cell **p_cells, NakedPair *p_naked_pairs, int *p_counter);
