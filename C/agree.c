#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char agree = tolower(get_char("Do you agree (Y/N)? \n"));

    if(agree == 'y')
    {
        printf("Agreed\n");
    }
    else if(agree == 'n')
    {
        printf("Not agreed.\n");
    }
    else
    {
        printf("Invalid answer (%c)\n",agree);
    }
}
