#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#define BUFFER_SIZE 1000


void replaceLine(struct User u, struct Record r, int line, const char *path)
{
    /* File pointer to hold reference of input file */
    FILE *fPtr;
    FILE *fTemp;

    char buffer[BUFFER_SIZE];
    int count;

    /*  Open all required files */
    fPtr = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }


    /*
     * Read line from source file and write to destination 
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        count++;

        /* If current line is line to replace */
        if (count == line)
            fprintf(fTemp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s",
                    r.id,
                    u.id,
                    u.name,
                    r.accountNbr,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.amount,
                    r.accountType);
        else
            fputs(buffer, fTemp);
    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);


    /* Delete original source file */
    remove(path);

    /* Rename temporary file as original file */
    rename("replace.tmp", path);
}
