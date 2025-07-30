#include <stdio.h>

int puzzle[9][9] = {
    {0, 4, 8, 2, 0, 0, 0, 0, 1},
    {1, 0, 0, 3, 8, 4, 7, 2, 6},
    {3, 0, 0, 7, 0, 1, 9, 4, 8},
    {0, 7, 2, 6, 4, 5, 1, 8, 0},
    {8, 0, 0, 0, 0, 2, 4, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 7},
    {0, 8, 4, 0, 0, 0, 3, 0, 0},
    {6, 0, 0, 4, 1, 0, 0, 0, 2},
    {0, 0, 3, 0, 0, 0, 0, 7, 4}};
// int puzzle[9][9] ={0};

void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int col, int val);
int solve_puzzle(int puzzle[9][9], int row, int col);

int main()
{
  printf("\n     Welcome To SUDOKU Solver!!    \n");
  printf("Original Puzzle:-\n");
  print_puzzle(puzzle);

  if (solve_puzzle(puzzle, 0, 0))
  {
    printf("\n\nSolved Puzzle:-\n");
    print_puzzle(puzzle);
  }
  else
  {
    printf("\n\nNo Solution Exists\n");
  }

  return 0;
}

int solve_puzzle(int puzzle[9][9], int row, int col)
{
  // If we've reached the end of the puzzle, we're done!

  if (col == 9)
  {
    if (row == 8)
    {
      return 1;
    }
    row++;
    col = 0;
  }

  if (puzzle[row][col] > 0)
  {
    return solve_puzzle(puzzle, row, col + 1);
  }
  for (int i = 0; i <= 9; i++)
  {
    if (valid_move(puzzle, row, col, i))
    {
      puzzle[row][col] = i;
      if (solve_puzzle(puzzle, row, col + 1))
      {
        return 1;
      }
      puzzle[row][col] = 0;
    }
  }
  return 0;
}

int valid_move(int puzzle[9][9], int row, int col, int val)
{
  int num, i, j;
  // check row
  for (i = 0; i < 9; i++)
  {
    if (puzzle[row][i] == val)
      return 0;
  }
  // check column
  for (i = 0; i < 9; i++)
  {
    if (puzzle[i][col] == val)
      return 0;
  }
  // check box
  int r = row - row % 3;
  int c = col - col % 3;

  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      if (puzzle[r + i][c + j] ==
          val)
        return 0;
    }
  }
  return 1;
}

void print_puzzle(int puzzle[9][9])
{
  printf("\n +-------+-------+-------+");
  int row, col;
  for (row = 0; row < 9; row++)
  {
    printf("\n ");
    for (col = 0; col < 9; col++)
    {
      if (col % 3 == 0)
      {
        printf("| ");
      }
      if (puzzle[row][col] != 0)
      {
        printf("%d ", puzzle[row][col]);
      }
      else
      {
        printf("  ");
      }
    }
    printf("| ");
    if ((row + 1) % 3 == 0 && row < 8)
    {
      printf("\n |-------+-------+-------|");
    }
  }
  printf("\n +-------+-------+-------+");
}