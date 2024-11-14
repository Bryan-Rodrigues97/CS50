#include <cs50.h>
#include <stdio.h>

int fib(int n);

int main(void)
{
    int number = get_int("Number: ");

    if(number < 0)
    {
        printf("The number must be greather or equals 0.\n");
        return 1;
    }

    printf("The fibonacci sequence for %i is %i\n",number,fib(number));
}

int fib(int n)
{
    if(n == 0 || n == 1)
        return n;

    return fib(n-1)  + fib(n-2);
}
