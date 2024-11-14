#include <cs50.h>
#include <stdio.h>

int fact(int n);

int main(void)
{
    int n = get_int("Number: ");

    if(n < 0)
    {
        printf("The number must be greather or equals 0.\n");
        return 1;
    }

    printf("Factorial of %i is %i\n", n, fact(n));

}

int fact(int n)
{
    if(n == 1 || n == 0)
    {
        return 1;
    }

    return n * fact(n-1);
}
