#include <cs50.h>
#include <stdio.h>

//sizeof - Returns the size of a variable in Bytes
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

int main(void)
{
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};
    int n = get_int("Number: ");

    //Linear Search O(n)
    for(int i=0; i < ARRAY_LENGTH(numbers); i++)
    {
        if(numbers[i] == n)
        {
            printf("Found\n");
            return 0;
        }
    }

    printf("Not found\n");
    return 1;
}
