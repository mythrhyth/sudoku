// functions.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

void printSudoku(char sudoku[9][9]) {
    printf("-------------------------------\n");
    for (int i = 0; i < 9; i++) {
        printf("|");
        for (int j = 0; j < 9; j++) {
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
void read_sudoku(char a[9][9])
{
    for (int i = 0; i < 9; i++) {
        printf("Enter row %d: ", i + 1);
        for (int j = 0; j < 9; j++) {
            scanf(" %c", &a[i][j]);
        }
    }
}

int isValid(char sudoku[9][9], int row, int col, char num) {
    // Check if num is present in current row or column
    for (int i = 0; i < 9; i++) {
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

int solveSudoku(char sudoku[9][9]) {
    int row, col;
    
    // Find an empty cell
    int foundEmptyCell = 0;
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (sudoku[row][col] == '.') {
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

    // Generate random numbers for filling the empty cell
    srand(time(NULL));
    char numbers[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 9; i++) {
        int j = rand() % (9 - i) + i;
        char temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // Try numbers from 1 to 9
    for (int x = 0; x < 9; x++) {
        if (isValid(sudoku, row, col, numbers[x])) {
            sudoku[row][col] = numbers[x];

            // Recur to solve remaining Sudoku
            if (solveSudoku(sudoku)) {
                return 1;
            }

            // If recursion fails, backtrack
            sudoku[row][col] = '.';
        }
    }

    // No solution found
    return 0;
}
void fprintSudoku(FILE* fp,char sudoku[9][9]){
  fprintf(fp,"-------------------------------\n");
    for (int i = 0; i < 9; i++) {
        fprintf(fp,"|");
        for (int j = 0; j < 9; j++) {
            fprintf(fp, "%c", sudoku[i][j]);
            if((j+1) % 3 == 0){
                fprintf(fp,"|");
            }
        }
        fprintf(fp,"\n");
         if((i+1) % 3 == 0){
            fprintf(fp,"-------------------------------\n");
        }
    }
}
void read_file_into_matrix(char matrix[9][9]) {
    FILE *file;
    char character;
    int row = 0, col = 0;

    file = fopen("solution.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }


    while ((character = fgetc(file)) != EOF && row < 9) {
        if ((character >= '0' && character <= '9') || character == '.') {
            matrix[row][col] = character;
            col++;
            if (col == 9) {
                col = 0;
                row++;
            }
        }
    }

    fclose(file);
}





void generateSudoku(char sudoku[9][9], int difficulty,char r[9][9]) {
    // Initialize Sudoku grid with empty cells
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = '.';
        }
    }

    // Solve the empty Sudoku grid
    solveSudoku(sudoku);
    //printSudoku(sudoku);
    //copied the solution to the next arry
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            r[i][j]=sudoku[i][j];
        }
    }
    printSudoku(sudoku);

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
        int row = rand() % 9;
        int col = rand() % 9;
        if (sudoku[row][col] != '.') {
            sudoku[row][col] = '.';
            removeCount--;
        }
    }

    // Print the generated Sudoku
    printf("The . denotes the space to be filled\n");
    printSudoku(sudoku);

  FILE* fp=fopen("rhythm.txt","w");
  FILE* c=fopen("solution.txt","w");
  fprintSudoku(fp,sudoku);
  fprintSudoku(c,sudoku);
  fclose(fp);
  fclose(c);

}
bool areArraysEqual(char array1[9][9], char array2[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (array1[i][j] != array2[i][j]) {
                return false; // If any element is different, arrays are not equal
            }
        }
    }
    return true; // All elements are equal
}
