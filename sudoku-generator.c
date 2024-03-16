#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
#define EMPTY_CELL '0'

void printSudoku(char sudoku[SIZE][SIZE]) {
    printf("-------------------------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("|");
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", sudoku[i][j]);
            if((j+1) % 3 == 0){
                printf("|");
            }
        }
        printf("\n");
         if((i+1) % 3 == 0){
            printf("-------------------------------\n");
        }

    }
}

int isValid(char sudoku[SIZE][SIZE], int row, int col, char num) {
    // Check if num is present in current row or column
    for (int i = 0; i < SIZE; i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num) {
            return 0;
        }
    }

    // Check if num is present in current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }

    return 1;
}

int solveSudoku(char sudoku[SIZE][SIZE]) {
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
        return 1;
    }

    // Try numbers from 1 to 9
    for (num = '1'; num <= '9'; num++) {
        if (isValid(sudoku, row, col, num)) {
            sudoku[row][col] = num;

            // Recur to solve remaining Sudoku
            if (solveSudoku(sudoku)) {
                return 1;
            }

            // If recursion fails, backtrack
            sudoku[row][col] = EMPTY_CELL;
        }
    }

    // No solution found
    return 0;
}

void generateSudoku(char sudoku[SIZE][SIZE], int difficulty) {
    srand(time(NULL));

    // Initialize Sudoku grid with empty cells
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sudoku[i][j] = EMPTY_CELL;
        }
    }

    // Solve the empty Sudoku grid
    solveSudoku(sudoku);

    // Remove cells based on difficulty level
    int removeCount = 0;
    switch (difficulty) {
        case 1:
            removeCount = 20;  // Easy: Remove 20 cells
            break;
        case 2:
            removeCount = 40;  // Medium: Remove 40 cells
            break;
        case 3:
            removeCount = 60;  // Hard: Remove 60 cells
            break;
        default:
            removeCount = 40;  // Medium by default
    }

    while (removeCount > 0) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (sudoku[row][col] != EMPTY_CELL) {
            sudoku[row][col] = EMPTY_CELL;
            removeCount--;
        }
    }

    // Print the generated Sudoku
    printSudoku(sudoku);
}

int main() {
    char sudoku[SIZE][SIZE];
    int difficulty;

    // Choose the difficulty level
    printf("Choose difficulty level (1: Easy, 2: Medium, 3: Hard): ");
    scanf("%d", &difficulty);

    // Generate and print the partially filled Sudoku puzzle
    generateSudoku(sudoku, difficulty);

    return 0;
}
