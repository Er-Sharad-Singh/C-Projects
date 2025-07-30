#include <stdio.h>
#include<time.h>
#include<stdlib.h>

int main()
{
  int random, guess;
  int no_of_guess=0;
  srand(time(NULL));
  printf("Welcome To The World of Guessing Numbers\n");
  random=rand()%100 + 1; //generating random number between 1 and 100
  do
  {
    printf("Guess a number between 1 and 100\n");
    scanf("%d", &guess);
    no_of_guess++;
    if(guess<random){
      printf("Your guess is too low\n");
    }else if(guess>random){
      printf("Your guess is too high\n");
    }else{
      printf("\nCongratulations !!!You guessed it right in %d Attempt\n",no_of_guess); 
    }
  } while (guess != random);
  printf("Bye Bye,Thankyou For Playing\n");
  printf("Developed By Sharad Singh\n");
  return 0;
}