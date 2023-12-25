#include "naked_triples.h"

bool is_naked_triple(Cell *cell1, Cell *cell2, Cell *cell3, int value1, int value2, int value3) {

    if ((cell1->num_candidates <= 3) && (cell2->num_candidates <= 3) && (cell3->num_candidates <= 3) &&
        (cell1->num_candidates >= 2) && (cell2->num_candidates >= 2) && (cell3->num_candidates >= 2)) {

        if ((is_candidate(cell1, value1) || is_candidate(cell1, value2) || is_candidate(cell1, value3)) &&
            (is_candidate(cell2, value1) || is_candidate(cell2, value2) || is_candidate(cell2, value3)) &&
            (is_candidate(cell3, value1) || is_candidate(cell3, value2) || is_candidate(cell3, value3))) {

            // Check if no other values are candidates in these cells
            for (int candidate = 1; candidate <= 9; ++candidate) {
                if ((candidate != value1) && (candidate != value2) && (candidate != value3)) {
                    if (is_candidate(cell1, candidate) || is_candidate(cell2, candidate) || is_candidate(cell3, candidate)) {
                        return false;  // Other value found, not a naked triple
                    }
                }
            }

            return true;  // Naked triple found
        }
    }

    return false;  // No naked triple found
}

void find_and_process_naked_triples(Cell **p_cells, NakedTriple *p_naked_triples, int *p_counter) {
    int naked_triples_values[BOARD_SIZE] = {0};
    int triple_candidates = 0;

    // Count the occurrences of candidates in the cells, avoiding duplicates
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (p_cells[i]->num_candidates > 1) {
            int *candidates = get_candidates(p_cells[i]);
            for (int j = 0; j < p_cells[i]->num_candidates; ++j) {
                int candidate = candidates[j];
                naked_triples_values[candidate - 1]++;
            }
            free(candidates);
        }
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (naked_triples_values[i] >= 2) {
            naked_triples_values[triple_candidates++] = i + 1;
        }
    }

    // Iterate through possible naked triples
    for (int i = 0; i < triple_candidates - 2; ++i) {
        for (int k = i + 1; k < triple_candidates - 1; ++k) {
            for (int l = k + 1; l < triple_candidates; ++l) {
                for (int j = 0; j < BOARD_SIZE - 2; ++j) {
                    for (int h = j + 1; h < BOARD_SIZE - 1; ++h) {
                        for (int g = h + 1; g < BOARD_SIZE; ++g) {
                            // Check if values form a naked triple
                            if (is_naked_triple(p_cells[j], p_cells[h], p_cells[g],
                                                naked_triples_values[i], naked_triples_values[k], naked_triples_values[l])) {
                                NakedTriple naked_triple_obj;
                                naked_triple_obj.value1 = naked_triples_values[i];
                                naked_triple_obj.value2 = naked_triples_values[k];
                                naked_triple_obj.value3 = naked_triples_values[l];
                                naked_triple_obj.p_cell1 = p_cells[j];
                                naked_triple_obj.p_cell2 = p_cells[h];
                                naked_triple_obj.p_cell3 = p_cells[g];

                                // Check if the naked triple is a duplicate
                                int duplicate = 0;
                                for (int m = 0; m < *p_counter; ++m) {
                                    if (naked_triple_obj.value1 == p_naked_triples[m].value1 &&
                                        naked_triple_obj.value2 == p_naked_triples[m].value2 &&
                                        naked_triple_obj.value3 == p_naked_triples[m].value3 &&
                                        naked_triple_obj.p_cell1 == p_naked_triples[m].p_cell1 &&
                                        naked_triple_obj.p_cell2 == p_naked_triples[m].p_cell2 &&
                                        naked_triple_obj.p_cell3 == p_naked_triples[m].p_cell3) {
                                        duplicate = 1;
                                        break;
                                    }
                                }

                                if (!duplicate) {
                                    p_naked_triples[(*p_counter)++] = naked_triple_obj;

                                    // Process the naked triple (unset candidates)
                                    // Code for unsetting candidates in the same row, column, and box
                                    // ...
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int naked_triples(SudokuBoard *p_board) {
    NakedTriple naked_triples[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;

    // Iterate over rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_and_process_naked_triples(p_board->p_rows[i], naked_triples, &counter);
        find_and_process_naked_triples(p_board->p_cols[i], naked_triples, &counter);
        find_and_process_naked_triples(p_board->p_boxes[i], naked_triples, &counter);
    }

    return counter;
}