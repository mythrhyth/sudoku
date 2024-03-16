#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

// Function prototypes
bool findEmptyCell(char board[SIZE][SIZE], int *row, int *col);
bool isValidPlacement(char board[SIZE][SIZE], int row, int col, int num);
bool solveSudoku(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);

int main() {
    // Example Sudoku board
   /*  char board[SIZE][SIZE] = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    }; 
        1 2 0 0 5 0 7 0 9 
        0 0 6 0 8 0 1 0 0
        7 8 9 1 0 0 0 0 6
        0 0 0 3 6 5 0 0 0
        3 0 5 0 0 7 0 0 4
        0 9 0 0 0 0 3 6 0
        5 3 1 0 4 2 9 7 0
        6 0 2 9 7 8 0 3 1
        0 7 8 0 0 0 6 0 2
    */

    char board[SIZE][SIZE];

    // Input Sudoku board from the user
    printf("Enter the Sudoku puzzle (use '.' for empty cells):\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Enter row %d: ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            scanf(" %c", &board[i][j]);
        }
    }

    // Solve the Sudoku puzzle
    if (solveSudoku(board)) {
        printf("Solved Sudoku:\n");
        printBoard(board);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}

bool findEmptyCell(char board[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (board[*row][*col] == '.') {
                return true; // Found an empty cell
            }
        }
    }
    return false; // No empty cell found
}

bool isValidPlacement(char board[SIZE][SIZE], int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false; // Invalid placement
        }
    }
    
    // Check subgrid
    int subgridRowStart = (row / 3) * 3;
    int subgridColStart = (col / 3) * 3;
    for (int i = subgridRowStart; i < subgridRowStart + 3; i++) {
        for (int j = subgridColStart; j < subgridColStart + 3; j++) {
            if (board[i][j] == num) {
                return false; // Invalid placement
            }
        }
    }
    
    return true; // Valid placement
}

bool solveSudoku(char board[SIZE][SIZE]) {
    int row, col;
    if (!findEmptyCell(board, &row, &col)) {
        return true; // Puzzle solved
    }
    
    for (int num = 1; num <= SIZE; num++) {
        char numChar = num + '0';
        if (isValidPlacement(board, row, col, numChar)) {
            board[row][col] = numChar; // Try placing the number
            
            if (solveSudoku(board)) {
                return true; // Found a solution
            }
            
            board[row][col] = '.'; // Backtrack
        }
    }
    
    return false; // No solution found
}

void printBoard(char board[SIZE][SIZE]) {
    printf("-------------------------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("|"); 
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
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
