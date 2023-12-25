#include "hidden_triples.h"

// Helper function to check if a value exists in a cell's candidates
int is_value_in_candidates(Cell *cell, int value) {
    for (int i = 0; i < cell->num_candidates; ++i) {
        if (cell->candidates[i] == value) {
            return 1;
        }
    }
    return 0;
}

// Function to find hidden triples in a set of cells
int find_hidden_triples(Cell **cells, HiddenTriple *hidden_triples, int *counter) {
    int num_triples = 0;
    int hidden_triples_values[BOARD_SIZE] = {0};

    // Count the occurrences of candidates in the cells
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (cells[i]->num_candidates > 1) {
            for (int j = 0; j < cells[i]->num_candidates; ++j) {
                int candidate = cells[i]->candidates[j];
                hidden_triples_values[candidate - 1]++;
            }
        }
    }

    // Find hidden triples
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (hidden_triples_values[i] >= 2 && hidden_triples_values[i] <= 3) {
            for (int j = i + 1; j < BOARD_SIZE; ++j) {
                if (hidden_triples_values[j] >= 2 && hidden_triples_values[j] <= 3) {
                    for (int k = j + 1; k < BOARD_SIZE; ++k) {
                        if (hidden_triples_values[k] >= 2 && hidden_triples_values[k] <= 3) {
                            if (hidden_triples_values[i] + hidden_triples_values[j] + hidden_triples_values[k] == 3) {
                                HiddenTriple hidden_triple_obj;
                                hidden_triple_obj.value1 = i + 1;
                                hidden_triple_obj.value2 = j + 1;
                                hidden_triple_obj.value3 = k + 1;
                                hidden_triple_obj.p_cell1 = cells[i];
                                hidden_triple_obj.p_cell2 = cells[j];
                                hidden_triple_obj.p_cell3 = cells[k];
                                hidden_triples[(*counter)++] = hidden_triple_obj;
                                num_triples++;
                            }
                        }
                    }
                }
            }
        }
    }

    return num_triples;
}

// Function to remove overlapping candidates in hidden triples
int remove_overlaps(HiddenTriple *hidden_triples, int counter) {
    int overlap = 0;

    for (int i = 0; i < counter; ++i) {
        Cell *cell1 = hidden_triples[i].p_cell1;
        Cell *cell2 = hidden_triples[i].p_cell2;
        Cell *cell3 = hidden_triples[i].p_cell3;

        for (int val = 1; val <= BOARD_SIZE; ++val) {
            if (val != hidden_triples[i].value1 && val != hidden_triples[i].value2 && val != hidden_triples[i].value3) {
                if (is_value_in_candidates(cell1, val) || is_value_in_candidates(cell2, val) || is_value_in_candidates(cell3, val)) {
                    unset_candidate(cell1, val);
                    unset_candidate(cell2, val);
                    unset_candidate(cell3, val);
                    overlap++;
                }
            }
        }
    }

    return overlap;
}

// Main function to find hidden triples in a Sudoku board
int hidden_triples(SudokuBoard *p_board) {
    HiddenTriple hidden_triples[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        counter += find_hidden_triples(p_board->p_rows[i], hidden_triples, &counter);
        counter += find_hidden_triples(p_board->p_cols[i], hidden_triples, &counter);
        counter += find_hidden_triples(p_board->p_boxes[i], hidden_triples, &counter);
    }

    int overlap = remove_overlaps(hidden_triples, counter);
    return (counter - overlap);
}
