#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
int getUserFromFile(FILE *ptr, struct User *u);
void saveUserToFile(FILE *ptr, struct User u);
void getUserByName(struct User *u);

// menu
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);
int checkUserExists(char a[50]);
void saveNewUser(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void updateAcc(struct User u);

// util funcs
void replaceLine(struct User u, struct Record r, int line, const char* path);
