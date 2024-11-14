#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void copy(char *copyFrom, char* copyTo);

int main(void)
{
    char *s = get_string("s: ");
    char *t = (char *)malloc(strlen(s) + 1);

    if(t == NULL)
    {
        // cannot allocate the space in memory
        return 1;
    }

    copy(s, t);

    if(strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("%s\n", s);
    printf("%s\n", t);

    free(t);
}

void copy(char *copyFrom, char* copyTo)
{
    if(strlen(copyTo) < strlen(copyTo))
    {
        printf("The size of string destination is lower than the origin\n");
        return;
    }

    // need includ len. Bacause of '\0' char
    for(int i = 0, len = strlen(copyFrom); i <= len; i++)
    {
        *(copyTo + i) = *(copyFrom + i);
        // copyTo[i] = copyFrom[i];
    }
}
