#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void meow(int i);
void askClearTerminal();

int main(void)
{
    askClearTerminal();
    meow(5);
}

void meow(int n)
{
    for(int i=0;i<n;i++)
    {
        printf("meow\n");
    }
}

void askClearTerminal()
{
    char clear = tolower(get_char("Do you want to clear the terminal (Y/N)? "));

    if(clear == 'y')
    {
        system("clear");
    }
    else if(clear != 'n')
    {
        printf("Invalid Command\n");
    }
}
