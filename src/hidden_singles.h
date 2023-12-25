#pragma once

#include "sudoku.h"
#include <stdlib.h>
typedef struct HiddenSingle_impl
{
    Cell *p_cell;
    int value;
} HiddenSingle;

// find hidden single values (the value that is unique among all the candidates for a row, a collumn, or a box)
int identify_unique_cadidates(Cell **p_cells, int *hidden_single_values);

// find hidden single cells in a row, in a collumn or in a box
void identify_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles,
                        int *p_counter);
int hidden_singles(SudokuBoard *p_board);

