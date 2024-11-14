#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *file = fopen("phonebook.csv","a");

    if(file == NULL)
    {
        printf("Cannot read/open the file\n");
        return 1;
    }

    char *name = get_string("Name: ");
    char *number = get_string("Phone Number: ");

    fprintf(file, "%s,%s\n", name, number);

    fclose(file);
}
