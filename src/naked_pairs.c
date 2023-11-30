#include <stdlib.h>
#include <stdio.h>
#include "naked_pairs.h"


int naked_pairs(SudokuBoard *p_board) {
    NakedPair naked_pairs[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;
    int unique_counter = 0;
    int naked_pairs_values[BOARD_SIZE] = {0};

    for (int i = 0; i < BOARD_SIZE; ++i) {
        // Find naked pairs values in rows, columns, and boxes
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (p_board->p_rows[i][j]->num_candidates > 1) {
                int *candidates = get_candidates(p_board->p_rows[i][j]);
                for (int k = 0; k < p_board->p_rows[i][j]->num_candidates; ++k) {
                    int candidate = candidates[k];
                    naked_pairs_values[candidate - 1]++;
                }
                free(candidates);
            }
            for (int k = 0; k < BOARD_SIZE - 1; ++k) {
                for (int l = k + 1; l < BOARD_SIZE; ++l) {
                    if (naked_pairs_values[k] >= 2 && naked_pairs_values[l] >= 2) {
                        for (int m = 0; m < BOARD_SIZE; ++m) {
                            for (int n = m + 1; n < BOARD_SIZE; ++n) {
                                if (p_board->p_rows[i][m]->num_candidates == 2 &&
                                    p_board->p_rows[i][n]->num_candidates == 2 &&
                                    is_candidate(p_board->p_rows[i][m], k + 1) &&
                                    is_candidate(p_board->p_rows[i][m], l + 1) &&
                                    is_candidate(p_board->p_rows[i][n], k + 1) &&
                                    is_candidate(p_board->p_rows[i][n], l + 1)) {
                                    NakedPair naked_pair_obj;
                                    naked_pair_obj.value1 = k + 1;
                                    naked_pair_obj.value2 = l + 1;
                                    naked_pair_obj.p_cell1 = p_board->p_rows[i][m];
                                    naked_pair_obj.p_cell2 = p_board->p_rows[i][n];
                                    naked_pairs[counter++] = naked_pair_obj;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (p_board->p_cols[i][j]->num_candidates > 1) {
                int *candidates = get_candidates(p_board->p_cols[i][j]);
                for (int k = 0; k < p_board->p_cols[i][j]->num_candidates; ++k) {
                    int candidate = candidates[k];
                    naked_pairs_values[candidate - 1]++;
                }
                free(candidates);
            }
            for (int k = 0; k < BOARD_SIZE - 1; ++k) {
                for (int l = k + 1; l < BOARD_SIZE; ++l) {
                    if (naked_pairs_values[k] >= 2 && naked_pairs_values[l] >= 2) {
                        for (int m = 0; m < BOARD_SIZE; ++m) {
                            for (int n = m + 1; n < BOARD_SIZE; ++n) {
                                if (p_board->p_cols[i][m]->num_candidates == 2 &&
                                    p_board->p_cols[i][n]->num_candidates == 2 &&
                                    is_candidate(p_board->p_cols[i][m], k + 1) &&
                                    is_candidate(p_board->p_cols[i][m], l + 1) &&
                                    is_candidate(p_board->p_cols[i][n], k + 1) &&
                                    is_candidate(p_board->p_cols[i][n], l + 1)) {
                                    NakedPair naked_pair_obj;
                                    naked_pair_obj.value1 = k + 1;
                                    naked_pair_obj.value2 = l + 1;
                                    naked_pair_obj.p_cell1 = p_board->p_cols[i][m];
                                    naked_pair_obj.p_cell2 = p_board->p_cols[i][n];
                                    naked_pairs[counter++] = naked_pair_obj;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (p_board->p_boxes[i][j]->num_candidates > 1) {
                int *candidates = get_candidates(p_board->p_boxes[i][j]);
                for (int k = 0; k < p_board->p_boxes[i][j]->num_candidates; ++k) {
                    int candidate = candidates[k];
                    naked_pairs_values[candidate - 1]++;
                }
                free(candidates);
            }
            for (int k = 0; k < BOARD_SIZE - 1; ++k) {
                for (int l = k + 1; l < BOARD_SIZE; ++l) {
                    if (naked_pairs_values[k] >= 2 && naked_pairs_values[l] >= 2) {
                        for (int m = 0; m < BOARD_SIZE; ++m) {
                            for (int n = m + 1; n < BOARD_SIZE; ++n) {
                                if (p_board->p_boxes[i][m]->num_candidates == 2 &&
                                    p_board->p_boxes[i][n]->num_candidates == 2 &&
                                    is_candidate(p_board->p_boxes[i][m], k + 1) &&
                                    is_candidate(p_board->p_boxes[i][m], l + 1) &&
                                    is_candidate(p_board->p_boxes[i][n], k + 1) &&
                                    is_candidate(p_board->p_boxes[i][n], l + 1)) {
                                    NakedPair naked_pair_obj;
                                    naked_pair_obj.value1 = k + 1;
                                    naked_pair_obj.value2 = l + 1;
                                    naked_pair_obj.p_cell1 = p_board->p_boxes[i][m];
                                    naked_pair_obj.p_cell2 = p_board->p_boxes[i][n];
                                    naked_pairs[counter++] = naked_pair_obj;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Identify naked pairs
        for (int x = 0; x < BOARD_SIZE; ++x) {
            naked_pairs_values[x] = 0;
        }
    }

    int unique_pairs[BOARD_SIZE][BOARD_SIZE] = {0};
    for (int i = 0; i < counter; ++i) {
        Cell *naked_pair_cell1 = naked_pairs[i].p_cell1;
        Cell *naked_pair_cell2 = naked_pairs[i].p_cell2;
        int value1 = naked_pairs[i].value1;
        int value2 = naked_pairs[i].value2;

        if (unique_pairs[naked_pair_cell1->row_index][naked_pair_cell1->col_index] == 1) {
            continue;
        }

        for (int j = 0; j < BOARD_SIZE; ++j) {
            Cell *current_cell_row = p_board->p_rows[naked_pair_cell1->row_index][j];
            Cell *current_cell_col = p_board->p_cols[naked_pair_cell1->col_index][j];
            Cell *current_cell_box = p_board->p_boxes[naked_pair_cell1->box_index][j];
            if (naked_pair_cell1->row_index == naked_pair_cell2->row_index){

                if (current_cell_row != naked_pair_cell1 && current_cell_row != naked_pair_cell2) {
                    if (is_candidate(current_cell_row, value1)) {
                        unset_candidate(current_cell_row, value1);
                    }
                    if (is_candidate(current_cell_row, value2)) {
                        unset_candidate(current_cell_row, value2);
                    }
                }
            }

            if (naked_pair_cell1->col_index == naked_pair_cell2->col_index){
                if (current_cell_col != naked_pair_cell1 && current_cell_col != naked_pair_cell2) {
                    if (is_candidate(current_cell_col, value1)) {
                        unset_candidate(current_cell_col, value1);
                    }
                    if (is_candidate(current_cell_col, value2)) {
                        unset_candidate(current_cell_col, value2);
                    }
                }
            }

            if (naked_pair_cell1->box_index == naked_pair_cell2->box_index){
                if (current_cell_box != naked_pair_cell1 && current_cell_box != naked_pair_cell2) {
                    if (is_candidate(current_cell_box, value1)) {
                        unset_candidate(current_cell_box, value1);
                    }
                    if (is_candidate(current_cell_box, value2)) {
                        unset_candidate(current_cell_box, value2);
                    }
                }
            }
        }
        unique_pairs[naked_pair_cell1->row_index][naked_pair_cell1->col_index] = 1;
        unique_counter++;
    }

    return unique_counter;
}
