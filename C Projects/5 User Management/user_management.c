#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#define MAX_USER 10
#define CREDENTIAL_LENGTH 30

typedef struct
{
  char username[CREDENTIAL_LENGTH];
  char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USER];
int user_count = 0;

void register_user();
int login_user();
void fix_fgets_input(char *);
void input_credential(char *username, char *password);
int main()
{
  int option;
  int user_index;
  while ((1))
  {
    printf("\nWelcome To User Management");
    printf("\n1. Register");
    printf("\n2. Login");
    printf("\n3. Exit");
    printf("\nSelect an option: ");
    scanf("%d", &option);
    getchar(); // Consume Extra Enter

    switch (option)
    {
    case 1:
      register_user();
      break;
    case 2:
      user_index = login_user();
      if (user_index < 0)
      {
        printf("\nLogin Failed.Invalid username or password\n");
      }
      else
      {
        printf("\nLogin Successfull! Welcome %s\n", users[user_index].username);
      }
      break;
    case 3:
      printf("\nExiting Program.");
      return 0;
      break;

    default:
      printf("\nInvalid Option. Please Try Again.\n");
      break;
    }
  }

  return 0;
}

void register_user()
{
  if (user_count == MAX_USER)
  {
    printf("\n MAximum %d users are Supported! No More Registrations Allowed\n", MAX_USER);
    return;
  }
  printf("\nRegister A New User");
  int new_index = user_count;

  input_credential(users[new_index].username, users[new_index].password);
  user_count++;
  printf("\nRegestration Successfull!\n");
}

int login_user()
{
  char username[CREDENTIAL_LENGTH];
  char password[CREDENTIAL_LENGTH];
  input_credential(username, password);
  for (int i = 0; i < user_count; i++)
  {
    if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
    {
      return i;
    }
  }

  return -1;
}

void fix_fgets_input(char *string)
{
  string[strcspn(string, "\n")] = '\0';
}

void input_credential(char *username, char *password)
{
  printf("\nEnter Username: ");
  fgets(username, CREDENTIAL_LENGTH, stdin);
  fix_fgets_input(username);


  printf("Enter Password (masking enabled): ");
  char ch;
  int i = 0;
  
  while(1){
    ch =_getch();
    if(ch==13){
      password[i]='\0';
      break;
    }else if(ch=='\r'||ch=='\n'){
      password[i]='\0';
    }else if(ch=='\b'){
      if(i>0){
        i--;
        printf("\b \b");
      }
    }else{
      if(i<CREDENTIAL_LENGTH){
        password[i++]=ch;
        printf("*");
      }
    }
  }
  printf("\n");
}