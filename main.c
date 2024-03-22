#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.c"

int main()
{
  int a;
  printf("Welcome to the Sudoku game\n");
  printf("Press 1:to generate a Sudoku game and play it\n 2: to solve given sudoku");
  scanf("%d", &a);
  if (a == 1)
  {
    int difficulty;
    printf("Choose difficulty level (1: Easy, 2: Medium, 3: Hard): ");
    scanf("%d", &difficulty);
    char sudoku[9][9] = {'.'};
    char r[9][9];
    generateSudoku(sudoku, difficulty, r);
    printf("Enter your answer in solution.txt without distubing format\n");
    char answer[9][9];
    int temp;
    printf("After writing solution in solutio.txt enter 1\n");
    scanf("%d",&a);


        read_file_into_matrix(answer);
    if (areArraysEqual(answer, r))
    {
      printf("Wow Correct answer!");
    }
    else
    {

      printf("Sorry! Try again");
      printf("\n");
      printf("the required sudoku pattern was:\n");
      printSudoku(r);
    }
  }
  else if (a == 2)
  {
    char input[9][9];
    read_sudoku(input);
    if (solveSudoku(input))
    {
      printSudoku(input);
    }
    else
    {
      printf("Solution doesn't exist");
    }
  }

  return 0;
}
