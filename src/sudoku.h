#pragma once

#include <stdbool.h>

#define BOARD_SIZE 9

<<<<<<< HEAD
<<<<<<< HEAD
struct Cell_impl
{
=======
struct Cell_impl {
>>>>>>> efe80b5 (added hidden single description)
=======
struct Cell_impl
{
>>>>>>> 22f6780 (updated loop)
    int row_index;
    int col_index;
    int box_index;
    int num_candidates;
    int candidates[BOARD_SIZE];
<<<<<<< HEAD
<<<<<<< HEAD
    int value; // solved or 0
<<<<<<< HEAD
=======
    int value;  // solved or 0
>>>>>>> efe80b5 (added hidden single description)
=======
    int value; // solved or 0
>>>>>>> 22f6780 (updated loop)
=======
    bool fixed;
>>>>>>> 13249bc (added tests)
};

typedef struct Cell_impl Cell;

<<<<<<< HEAD
<<<<<<< HEAD
struct SudokuBoard_impl
{
    int solved_counter;
    Cell **data; // 9x9 cell board

    Cell **p_rows[BOARD_SIZE];  // rows pointers
    Cell **p_cols[BOARD_SIZE];  // cols pointers
    Cell **p_boxes[BOARD_SIZE]; // boxes pointers
    Cell *solved_cells[BOARD_SIZE *
                       BOARD_SIZE]; // solved cell pointers (maximum)
=======
struct SudokuBoard_impl {
=======
struct SudokuBoard_impl
{
>>>>>>> 22f6780 (updated loop)
    int solved_counter;
    Cell **data; // 9x9 cell board

    Cell **p_rows[BOARD_SIZE];  // rows pointers
    Cell **p_cols[BOARD_SIZE];  // cols pointers
    Cell **p_boxes[BOARD_SIZE]; // boxes pointers
    Cell *solved_cells[BOARD_SIZE *
<<<<<<< HEAD
                       BOARD_SIZE];  // solved cell pointers (maximum)
>>>>>>> efe80b5 (added hidden single description)
=======
                       BOARD_SIZE]; // solved cell pointers (maximum)
>>>>>>> 22f6780 (updated loop)
};

typedef struct SudokuBoard_impl SudokuBoard;

void init_sudoku(SudokuBoard *p_board);
void load_sudoku(SudokuBoard *p_board, char *input_text);
bool apply_constraint(Cell **p_cells, int value);
bool is_in_list(Cell **p_array, int size, Cell *p);
void print_candidate_num(SudokuBoard *p_board);
void print_solution(SudokuBoard *p_board);
bool is_candidate(Cell *cell, int value);
void set_candidate(Cell *cell, int value);
void unset_candidate(Cell *cell, int value);
void set_candidates(Cell *cell, int *candidates, int size);
int *get_candidates(Cell *cell);

int check_solved_cells(SudokuBoard *p_board, Cell ***p_solved_cells);
bool show_possible(SudokuBoard *p_board, Cell **p_solved_cells, int counter);
void free_sudoku(SudokuBoard *p_board);
