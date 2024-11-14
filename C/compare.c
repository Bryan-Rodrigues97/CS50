#include <cs50.h>
#include <stdio.h>

void compare(int x, int y)
{
    if(x<y)
    {
        printf("X is less than Y\n");
    }
    else if(x>y)
    {
        printf("X is greather than Y\n");
    }
    else
    {
        printf("X and Y are equals\n");
    }
}

int main(void)
{
    int x = get_int("What's X? ");
    int y = get_int("What's Y? ");

    compare(x,y);
}
