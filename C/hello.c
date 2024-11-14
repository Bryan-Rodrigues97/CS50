#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(void)
{
    system("clear");

    printf("Hello, this is an example of usage of the CS50 C Library\n");
    string answer = get_string("What`s your name? ");

    printf("hello, %s\n",answer);
}
