#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    int number = get_int("Number: ");

    if(number < 1)
    {
        printf("The number must be greather than 0.\n");
        return 1;
    }

    printf("The number %i takes %i steps to returns to 1\n",number,collatz(number));
}

int collatz(int n)
{
    if(n == 1)
        return 0;

    // bitwise sum AND.Determines if the number is even
    if((n & 1) == 0)
        return 1 + collatz(n / 2);

    return 1 + collatz(3 * n + 1);
}
