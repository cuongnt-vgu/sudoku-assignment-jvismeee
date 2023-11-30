#pragma once

#include "sudoku.h"

typedef struct HiddenPair_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    int value1;
    int value2;
} HiddenPair;

int hidden_pairs(SudokuBoard *p_board);
void identify_hidden_pairs(Cell **p_cells, HiddenPair *p_hidden_pairs, int *p_counter);
int duplicate_hidden_pairs(HiddenPair *p_hidden_pairs, int counter);
