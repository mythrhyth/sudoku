#include <stdio.h>
#include <stdbool.h>

#define SIZE 9
#define EMPTY_CELL '0'

void printSudoku(char sudoku[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", sudoku[i][j]);
        }
        printf("\n");
    }
}

bool isValid(char sudoku[SIZE][SIZE], int row, int col, char num) {
    // Check if num is present in current row or column
    for (int i = 0; i < SIZE; i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num) {
            return false;
        }
    }

    // Check if num is present in current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(char sudoku[SIZE][SIZE]) {
    int row, col;
    char num;

    // Find an empty cell
    int foundEmptyCell = 0;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (sudoku[row][col] == EMPTY_CELL) {
                foundEmptyCell = 1;
                break;
            }
        }
        if (foundEmptyCell) {
            break;
        }
    }

    // If no empty cell found, Sudoku is solved
    if (!foundEmptyCell) {
        return true;
    }

    // Try numbers from 1 to 9
    for (num = '1'; num <= '9'; num++) {
        if (isValid(sudoku, row, col, num)) {
            sudoku[row][col] = num;

            // Recur to solve remaining Sudoku
            if (solveSudoku(sudoku)) {
                return true;
            }

            // If recursion fails, backtrack
            sudoku[row][col] = EMPTY_CELL;
        }
    }

    // No solution found
    return false;
}

int main() {
    char sudoku[SIZE][SIZE];

    // Input values for the partially filled Sudoku puzzle
    printf("Enter the partially filled Sudoku puzzle:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf(" %c", &sudoku[i][j]);
        }
    }

    // Solve the Sudoku puzzle
    if (!solveSudoku(sudoku)) {
        printf("Invalid Sudoku pattern!\n");
    } else {
        printf("Valid Sudoku pattern!\n");
    }

    return 0;
}
