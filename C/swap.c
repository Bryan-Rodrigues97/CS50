#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 10;
    int y = 50;

    printf("x is %i, y is %i\n",x,y);
    swap(&x, &y);
    printf("x is %i, y is %i\n",x,y);
}

// swap using pointers without tmp variable
void swap(int *a, int *b)
{
    *a = *a + *b;

    *b = *a - *b;
    *a = *a - *b;
}
