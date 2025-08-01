#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
const int BAR_LENGTH = 50;
const int MAX_TASK = 5;
typedef struct
{
  int id;
  int progress;
  int step;
} Task;

void print_bar(Task task);
void clear_screen();
int main()
{
  srand(time(NULL));
  Task tasks[MAX_TASK];
  // Initialization
  for (int i = 0; i < MAX_TASK; i++)
  {
    tasks[i].id = i + 1;
    tasks[i].progress = 0;
    tasks[i].step = rand() % 5 + 1;
  }

  int tasks_incomplete = 1;
  while (tasks_incomplete)
  {
    tasks_incomplete = 0;
    clear_screen();
    for (int i = 0; i < MAX_TASK; i++)
    {
      tasks[i].progress += tasks[i].step;
      if (tasks[i].progress > 100)
      {
        tasks[i].progress = 100;
      }
      else if (tasks[i].progress < 100)
      {
        tasks_incomplete = 1;
      }

      print_bar(tasks[i]);
    }

    sleep(1); // Sleep for 1 Second
  }

  printf("\nAll Task Completed");

  return 0;
}

void clear_screen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void print_bar(Task task)
{
  int bars_to_show = (task.progress * BAR_LENGTH) / 100;
  printf("\nTask %d: [", task.id);
  for (int i = 0; i < BAR_LENGTH; i++)
  {
    if (i < bars_to_show)
    {
      printf("=");
    }
    else
    {
      printf(" ");
    }
  }
  printf("] %d%%", task.progress);
}