#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.c"

int main()
{
  srand(time(NULL));
  int a;
  printf("Welcome to the Sudoku game\n");
  printf("Press 1:To generate a Sudoku game and play it\nPress 2: To solve given sudoku\n");
  scanf("%d", &a);
  if (a == 1)
  {
    int difficulty;
    printf("Choose difficulty level (1: Easy, 2: Medium, 3: Hard): \n");
    scanf("%d", &difficulty);
    char sudoku[9][9] = {'.'};
    char r[9][9];
    generateSudoku(sudoku, difficulty, r);
    printf("Enter your answer in solution.txt without distubing format\n");
    char answer[9][9];
    int temp;
  label:
    printf("After writing solution in solutio.txt enter 1\n");
    scanf("%d", &a);
    FILE* solution=fopen("solution.txt","r");
    read_file_into_matrix(solution,answer);
    if (areArraysEqual(answer, r))
    {
      printf("Wow Correct answer!");
    }
    else
    {

      printf("Sorry! Try again\n");
      printf("\n");
      printf("Press 1 to try again the same problem press 2 to see the see solution\n");
      scanf("%d", &a);
      if (a == 2)
      {
        printf("the required sudoku pattern was:\n");
        printSudoku(r);
      }
      else
      {
        goto label;
      }
    }
  }
  else if (a == 2)
  {
    char input[9][9];
    FILE *question = fopen("question.txt", "w");
    fprintemptysudoku(question);
    printf("Write you question in question.txt replace the . with given numbers\n");

    int temp;
    printf("After entering press 1\n");
    scanf("%d", &temp);
    question = fopen("question.txt", "r");

    read_file_into_matrix(question, input);
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
