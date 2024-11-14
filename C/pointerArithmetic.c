#include <stdio.h>

int main(void)
{
    int arr[] = {0,1,2,3,4,5};
    int size = 6;

    // Different ways to pass trough array elements
    for(int i = 0; i < 6; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");

    for(int i = 0; i < 6; i++)
    {
        printf("%i ", *(arr + i));
    }
    printf("\n");

    // Thats Crazy
    for(int i = 0; i < 6; i++)
    {
        printf("%i ", i[arr]);
    }
    printf("\n");
}
