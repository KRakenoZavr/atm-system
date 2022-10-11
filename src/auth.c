#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

int getUserFromFile(FILE *ptr, struct User *u)
{
    return fscanf(ptr, "%d %s %s",
                  &u->id,
                  u->name,
                  u->password) != EOF;
}

void saveUserToFile(FILE *ptr, struct User u)
{
    fprintf(ptr, "%d %s %s\n",
            u.id,
            u.name,
            u.password);
}

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\tBank Management System\n\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

void registerMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\tBank Management System\n\t\t User Login:");
    scanf("%s", a);

    if (checkUserExists(a) == 1)
    {
        printf("User with such username already exists\n");
        exit(1);
    }

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
}

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s %s", userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

int checkUserExists(char a[50])
{
    FILE *fp;
    char userChecker[50];

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s", userChecker) != EOF)
    {
        if (strcmp(userChecker, a) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void saveNewUser(struct User u)
{
    FILE *pf = fopen(USERS, "a+");

    struct User oldUser;

    while (getUserFromFile(pf, &oldUser))
    {}

    // last user id + 1
    u.id = oldUser.id + 1;

    saveUserToFile(pf, u);
    fclose(pf);
}

void getUserByName(struct User *u)
{
    FILE *pf = fopen(USERS, "a+");
    char username[50];

    strcpy(username, u->name);

    while (getUserFromFile(pf, u))
    {
        if (strcmp(username, u->name) == 0)
        {
            fclose(pf);
            return;
        }
    }

    fclose(pf);
    printf("\nUnexpected error");
    exit(1);
}
