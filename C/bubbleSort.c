#include <stdio.h>

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

int main(void)
{
    int arr[] = {9,7,3,1,0,2,4,8,5,6,10,11,12,13,14};
    int size = ARRAY_LENGTH(arr);
    int swapCounter = -1;
    int loopCount = 0;

    while(swapCounter != 0)
    {
        swapCounter = 0;

        for(int i = 0; i < size - 1 - loopCount; i++)
        {
            if(arr[i] > arr[i+1])
            {
                swapCounter++;

                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
            }
        }

        loopCount++;
    }

    // prints the sorted array
    for(int i = 0; i < ARRAY_LENGTH(arr); i++)
    {
        printf("[%i] = %i\n", i, arr[i]);
    }

    return 0;
}
