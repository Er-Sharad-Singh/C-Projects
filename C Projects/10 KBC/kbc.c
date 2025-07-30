#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>   // For _getch() and _kbhit()
#include <windows.h> // For console functions and Sleep()
#include <time.h>

#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100

// ANSI Color codes - will work on modern Windows terminals
const char *COLOR_END = "\033[0m";
const char *RED = "\033[1;31m";
const char *GREEN = "\033[1;32m";
const char *YELLOW = "\033[1;33m";
const char *BLUE = "\033[1;34m";
const char *PINK = "\033[1;35m";
const char *AQUA = "\033[1;36m";

typedef struct
{
  char text[MAX_QUES_LEN];
  char options[4][MAX_OPTION_LEN];
  char correct_option;
  int timeout;
  int prize_money;
} Question;

int read_questions(char *file_name, Question **questions);
void print_formatted_question(Question question);
void play_game(Question *questions, int no_of_questions);
int use_lifeline(Question *question, int *lifeline);
void enable_virtual_terminal_processing();

int main()
{
  srand(time(NULL));
  enable_virtual_terminal_processing(); // Enable colors in Windows console
  printf("\t\t%sChalo Kehlte hain KAUN BANEGA CROREPATI !!!%s", PINK, COLOR_END);
  Question *questions;
  int no_of_questions = read_questions("questions.txt", &questions);
  if (no_of_questions > 0)
  {
    play_game(questions, no_of_questions);
    free(questions); // Free the allocated memory
  }
  return 0;
}

void play_game(Question *questions, int no_of_questions)
{
  int money_won = 0;
  int lifeline[] = {1, 1}; // {50/50, Skip}
  int timeout_happened = 0;

  for (int i = 0; i < no_of_questions; i++)
  {
    print_formatted_question(questions[i]);

    char ch = 0;
    timeout_happened = 1; // Assume timeout will occur
    clock_t start_time = clock();

    // Timeout loop using _kbhit()
    while (((double)(clock() - start_time) / CLOCKS_PER_SEC) < questions[i].timeout)
    {
      if (_kbhit())
      {                       // Check if a key has been pressed
        ch = _getch();        // Get the character without waiting for Enter
        timeout_happened = 0; // Key was pressed, so no timeout
        break;
      }
      Sleep(100); // Sleep for 100ms to prevent high CPU usage
    }

    if (timeout_happened)
    {
      printf("%s\n\nTime out!!!!!%s\n", RED, COLOR_END);
      break;
    }

    printf("%c", ch); // Manually echo the character
    ch = toupper(ch);

    if (ch == 'L')
    {
      int value = use_lifeline(&questions[i], lifeline);
      if (value != 2)
      {      // If lifeline was used but not 'Skip'
        i--; // Repeat the same question
      }
      continue;
    }

    if (ch == questions[i].correct_option)
    {
      printf("%s\nCorrect!%s", GREEN, COLOR_END);
      money_won = questions[i].prize_money;
      printf("\n%sYou have won: Rs %d%s", BLUE, money_won, COLOR_END);
    }
    else
    {
      printf("%s\nWrong! Correct answer is %c.%s", RED, questions[i].correct_option, COLOR_END);
      break;
    }
  }
  printf("\n\n%sGame Over! Your total winnings are: Rs %d%s\n", BLUE, money_won, COLOR_END);
}

int use_lifeline(Question *question, int *lifeline)
{
  printf("\n\n%sAvailable Lifelines:%s", PINK, COLOR_END);
  if (lifeline[0])
    printf("\n%s1. Fifty-Fifty (50/50)%s", PINK, COLOR_END);
  if (lifeline[1])
    printf("\n%s2. Skip the Question%s", PINK, COLOR_END);
  printf("\n%sChoose a lifeline or 0 to return: %s", PINK, COLOR_END);

  char ch = _getch(); // Use _getch for immediate input
  printf("%c", ch);

  switch (ch)
  {
  case '1':
    if (lifeline[0])
    {
      lifeline[0] = 0;
      int removed = 0;
      while (removed < 2)
      {
        int num = rand() % 4;
        if ((num + 'A') != question->correct_option &&
            question->options[num][0] != '\0')
        {
          question->options[num][0] = '\0';
          removed++;
        }
      }
      return 1;
    }
    break;
  case '2':
    if (lifeline[1])
    {
      lifeline[1] = 0;
      return 2;
    }
    break;
  default:
    printf("\n%sReturning to the Question.%s", PINK, COLOR_END);
    break;
  }
  return 0;
}

void print_formatted_question(Question question)
{
  printf("\n\n%s%s%s", YELLOW, question.text, COLOR_END);
  for (int i = 0; i < 4; i++)
  {
    if (question.options[i][0] != '\0')
    {
      printf("\n%s%c. %s%s", AQUA, ('A' + i), question.options[i], COLOR_END);
    }
  }
  printf("\n%sHurry!! You have only %d Seconds to answer..%s", YELLOW, question.timeout, COLOR_END);
  printf("\n%sEnter your answer (A, B, C, or D) or L for lifeline: %s", GREEN, COLOR_END);
}

int read_questions(char *file_name, Question **questions)
{
  FILE *file = fopen(file_name, "r");
  if (file == NULL)
  {
    printf("\nUnable to open the questions bank: %s", file_name);
    return 0; // Return 0 instead of exiting
  }
  char str[MAX_QUES_LEN];
  int no_of_lines = 0;
  while (fgets(str, MAX_QUES_LEN, file))
  {
    // Strip trailing newline characters
    str[strcspn(str, "\r\n")] = 0;
    no_of_lines++;
  }
  if (no_of_lines == 0)
  {
    fclose(file);
    return 0;
  }
  int no_of_questions = no_of_lines / 8;
  *questions = (Question *)malloc(no_of_questions * sizeof(Question));
  if (*questions == NULL)
  {
    printf("Memory allocation failed!\n");
    fclose(file);
    return 0;
  }
  rewind(file);
  for (int i = 0; i < no_of_questions; i++)
  {
    fgets((*questions)[i].text, MAX_QUES_LEN, file);
    (*questions)[i].text[strcspn((*questions)[i].text, "\r\n")] = 0;

    for (int j = 0; j < 4; j++)
    {
      fgets((*questions)[i].options[j], MAX_OPTION_LEN, file);
      (*questions)[i].options[j][strcspn((*questions)[i].options[j], "\r\n")] = 0;
    }
    char option[10];
    fgets(option, 10, file);
    (*questions)[i].correct_option = option[0];

    char timeout[10];
    fgets(timeout, 10, file);
    (*questions)[i].timeout = atoi(timeout);

    char prize_money[10];
    fgets(prize_money, 10, file);
    (*questions)[i].prize_money = atoi(prize_money);
  }
  fclose(file);
  return no_of_questions;
}

// This function enables ANSI escape codes for color in the Windows console.
void enable_virtual_terminal_processing()
{
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE)
  {
    return;
  }

  DWORD dwMode = 0;
  if (!GetConsoleMode(hOut, &dwMode))
  {
    return;
  }

  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  if (!SetConsoleMode(hOut, dwMode))
  {
    return;
  }
}