#include <stdio.h>
#include <string.h>

typedef struct
{
  char name[50];
  int account_number;
  float balance;
} Account;

void create_account();
void withdraw_money();
void deposit_money();
void check_balance();

const char *ACCOUNT_FILE = "account.dat";

int main()
{

  while (1)
  {
    int choice;

    printf("\n\n*** Bank Management System ***\n");
    printf("1. Create Account\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Check Balance\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      create_account();
      break;
    case 2:
      deposit_money();
      break;
    case 3:
      withdraw_money();
      break;
    case 4:
      check_balance();
      break;
    case 5:
      printf("\nClosing The Bank.Exiting the system.\n");
      return 0;
    default:
      printf("\nInvalid choice. Please try again.\n");
    }
  }

  return 0;
}

void create_account()
{
  Account acc;
  char c;
  do
  {
    c = getchar();
  } while (c != '\n' && c != EOF);

  FILE *file = fopen(ACCOUNT_FILE, "ab+");
  if (file == NULL)
  {
    printf("\nUnable To Open File.\n");
    return;
  }
  printf("\nEnter your name: ");
  fgets(acc.name, sizeof(acc.name), stdin);
  acc.name[strcspn(acc.name, "\n")] = '\0';
  printf("Enter your account number: ");
  scanf("%d", &acc.account_number);
  acc.balance = 0;

  fwrite(&acc, sizeof(acc), 1, file); // write to file
  fclose(file);
  printf("\nAccount created successfully.\n");
}
void withdraw_money()
{
  FILE *file = fopen(ACCOUNT_FILE, "rb+");
  if (file == NULL)
  {
    printf("\nUnable To Open File.\n");
    return;
  }

  int account_number;
  float money;
  printf("\nEnter your account number: ");
  scanf("%d", &account_number);

  Account acc_r;
  while (fread(&acc_r, sizeof(acc_r), 1, file))
  {
    if (acc_r.account_number == account_number)
    {
      printf("Enter the amount you wish to withdraw: ");
      scanf("%f", &money);
      if (money <= 0)
      {
        printf("\nInvalid amount.");
        fclose(file);
        return;
      }
      else if (acc_r.balance < money)
      {
        printf("\nInsufficient balance.");
        fclose(file);
        return;
      }
      else
      {
        acc_r.balance -= money;
        fseek(file, -sizeof(acc_r), SEEK_CUR);
        fwrite(&acc_r, sizeof(acc_r), 1, file);
        fclose(file);
        printf("\nAmount %.2f Withdraw Successfully.Your current balance is Rs: %.2f\n", money, acc_r.balance);
        return;
      }
    }
  }

  fclose(file);
  printf("\nAccount No:%d not found.\n", account_number);
}
void deposit_money()
{
  FILE *file = fopen(ACCOUNT_FILE, "rb+");
  if (file == NULL)
  {
    printf("\nUnable To Open File.\n");
    return;
  }

  int account_number;
  float money;
  printf("\nEnter your account number: ");
  scanf("%d", &account_number);

  Account acc_r;
  while (fread(&acc_r, sizeof(acc_r), 1, file))
  {
    if (acc_r.account_number == account_number)
    {
      printf("Enter the amount to deposit: ");
      scanf("%f", &money);
      if (money <= 0)
      {
        printf("\nInvalid amount.");
        fclose(file);
        return;
      }
      else
      {
        acc_r.balance += money;
        fseek(file, -sizeof(acc_r), SEEK_CUR);
        fwrite(&acc_r, sizeof(acc_r), 1, file);
        fclose(file);
        printf("\nAmount %.2f Deposited Successfully.Your current balance is Rs: %.2f\n", money, acc_r.balance);
        return;
      }
    }
  }

  fclose(file);
  printf("\nAccount No:%d not found.\n", account_number);
}
void check_balance()
{
  FILE *file = fopen(ACCOUNT_FILE, "rb");
  if (file == NULL)
  {
    printf("\nUnable To Open File.\n");
    return;
  }

  int account_number;
  printf("\nEnter your account number: ");
  scanf("%d", &account_number);
  Account acc_read;

  while (fread(&acc_read, sizeof(acc_read), 1, file))
  {
    if (acc_read.account_number == account_number)
    {
      printf("\nYour current balance is Rs: %.2f\n", acc_read.balance);
      fclose(file);
      return;
    }
  }
  fclose(file);
  printf("\nAccount No:%d not found.\n", account_number);
}