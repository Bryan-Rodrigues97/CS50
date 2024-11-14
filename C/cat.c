#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./cat file\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    if(f == NULL)
    {
        return 2;
    }

    char ch;

    while((ch = fgetc(f)) != EOF)
    {
        printf("%c",ch);
    }

    printf("\n");
    fclose(f);
}
