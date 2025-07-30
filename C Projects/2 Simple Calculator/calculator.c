#include <stdio.h>
#include <math.h>
void print_menu();
double division(double, double);
double modulus(int, int);
int main()
{
  int choice;
  double first, second, result;
  while (1)
  {
    print_menu();
    scanf("%d", &choice);
    if (choice == 7)
    {
      break;
    }
    else if (choice > 7 || choice < 1)
    {
      fprintf(stderr,"\nInvalid choice. Please choose a valid option.\n");
    }
    else
    {
      printf("\nPlease enter first number: ");
      scanf("%lf", &first);
      printf("Please enter second number: ");
      scanf("%lf", &second);
      switch (choice)
      {
      case 1: // Add
        result = first + second;

        break;
      case 2: // Subtract
        result = first - second;

        break;
      case 3: // Multiply
        result = first * second;

        break;
      case 4: // Divide
        result = division(first, second);

        break;
      case 5: // Modulus
        result = modulus(first, second);

        break;
      case 6: // Power
        result = pow(first, second);
        break;
      }
      if (!isnan(result))
      {
        printf("\nResult of Operation is: %.2lf\n", result);
      }
    }
  };
}

double modulus(int a, int b)
{
  if (b == 0)
  {
    fprintf(stderr, "Invalid Argument For Modulus");
    return NAN;
  }
  else
  {
    return a % b;
  }
}

double division(double a, double b)
{
  if (b == 0)
  {
    fprintf(stderr, "Invalid Argument For Division");
    return NAN;
  }
  else
  {
    return a / b;
  }
}

void print_menu()
{
  printf("\n\n----------------------------------------");
  printf("\nWelcome to Simple Calculator\n");
  
  printf("\nChoose one of the Following opyions:");
  printf("\n1. Add");
  printf("\n2. Subtract");
  printf("\n3. Multiply");
  printf("\n4. Divide");
  printf("\n5. Modulus");
  printf("\n6. Power");
  printf("\n7. Exit");
  printf("\nNow, Enter your choice: ");
}