#include <stdio.h>

int square(int number);
int pSquare(int *pNumber);

int main(void)
{
    int n = 50;
    int *pn = &n;

    //printf("Address on N is %p\n", &n);
    //printf("Address on N is %p\n", pn);

    //printf("Value of N is %i\n", n);
    //printf("Value of N is %i\n", *pn);
    printf("No pointers here: \n");
    printf("N is %i\n",n);
    printf("Square of N is %i\n",square(n));
    printf("N still is %i\n",n);

    printf("\n\n*** *** *** *** ***\n\n");
    printf("Using pointers here: \n");
    printf("N is %i\n",*pn);
    printf("Square of N is %i\n",pSquare(pn));
    printf("Now N is %i\n",*pn);
}

int square(int number)
{
    // number is a copy
    return number * number;
}

int pSquare(int *pNumber)
{
    // *pNumber is a reference, wich means that the original int variable will be modified
    return *pNumber = *pNumber * *pNumber;
}
