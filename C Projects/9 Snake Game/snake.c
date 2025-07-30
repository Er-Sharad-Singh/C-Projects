#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Windows-specific headers for non-blocking input and console control.
#include <conio.h>
#include <windows.h>

/*
--- GAME CONTROLS ---
 W: Move Up
 A: Move Left
 S: Move Down
 D: Move Right
 X: Quit Game
*/

// Game board dimensions
const int width = 60;
const int height = 20;

// Game state variables
int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection
{
  STOP = 0,
  LEFT,
  RIGHT,
  UP,
  DOWN
};
enum eDirection dir;

void Setup();
void Draw();
void Input();
void Logic();

int main()
{
  Setup();
  while (!gameOver)
  {
    Draw();
    Input();
    Logic();
    Sleep(100); // Controls the speed of the game.
  }
  printf("\nGame Over! Your final score is: %d\n", score);
  return 0;
}

// Initializes the game state.
void Setup()
{
  gameOver = 0;
  dir = STOP;
  x = width / 2;
  y = height / 2;
  srand(time(NULL));
  fruitX = rand() % width;
  fruitY = rand() % height;
  score = 0;
  nTail = 0;
}

// Renders the game frame to the console.
void Draw()
{
  system("cls");
  printf("\t\tWelcome To Play Snake Game!!!\n");
  for (int i = 0; i < width + 2; i++)
    printf("#");
  printf("\n");

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (j == 0)
        printf("#");

      if (i == y && j == x)
      {
        printf("O");
      }
      else if (i == fruitY && j == fruitX)
      {
        printf("F");
      }
      else
      {
        int isTailSegment = 0;
        for (int k = 0; k < nTail; k++)
        {
          if (tailX[k] == j && tailY[k] == i)
          {
            printf("o");
            isTailSegment = 1;
          }
        }
        if (!isTailSegment)
          printf(" ");
      }

      if (j == width - 1)
        printf("#");
    }
    printf("\n");
  }

  for (int i = 0; i < width + 2; i++)
    printf("#");
  printf("\n");
  printf("Score: %d\n", score);
  printf("Press A(left),D(Right),W(Up),S(Down),X(Exit)");
}

// Handles user input for controlling the snake.
void Input()
{
  if (_kbhit())
  { // Check if a key has been pressed
    switch (_getch())
    {
    case 'a':
      if (dir != RIGHT)
        dir = LEFT;
      break;
    case 'd':
      if (dir != LEFT)
        dir = RIGHT;
      break;
    case 'w':
      if (dir != DOWN)
        dir = UP;
      break;
    case 's':
      if (dir != UP)
        dir = DOWN;
      break;
    case 'x':
      gameOver = 1;
      break;
    }
  }
}

// Updates the game state on each frame.
void Logic()
{
  // The tail follows the path of the head.
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = x;
  tailY[0] = y;
  for (int i = 1; i < nTail; i++)
  {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  // Move the snake's head based on the current direction.
  switch (dir)
  {
  case LEFT:
    x--;
    break;
  case RIGHT:
    x++;
    break;
  case UP:
    y--;
    break;
  case DOWN:
    y++;
    break;
  default:
    break;
  }

  // Check for wall collision.
  if (x < 0 || x >= width || y < 0 || y >= height)
  {
    gameOver = 1;
    return;
  }

  // Check for self-collision.
  for (int i = 0; i < nTail; i++)
  {
    if (tailX[i] == x && tailY[i] == y)
    {
      gameOver = 1;
      return;
    }
  }

  // Check for fruit collision.
  if (x == fruitX && y == fruitY)
  {
    score += 10;
    nTail++;
    fruitX = rand() % width;
    fruitY = rand() % height;
  }
}