#pragma once

#include "sudoku.h"

typedef struct HiddenTriple_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    Cell *p_cell3;
    int value1;
    int value2;
    int value3;
} HiddenTriple;

int hidden_triples(SudokuBoard *p_board);
int is_value_in_candidates(Cell *cell, int value);
int find_hidden_triples(Cell **cells, HiddenTriple *hidden_triples, int *counter);
int remove_overlaps(HiddenTriple *hidden_triples, int counter);
