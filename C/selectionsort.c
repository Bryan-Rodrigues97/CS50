#include <stdio.h>

//sizeof - Returns the size of a variable in Bytes
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

int main(void)
{
    int arr[] = {9,7,3,1,0,2,4,8,5,6,10,11,13,12,16,15,14,20,19,17,18};

    for(int i = 0; i < ARRAY_LENGTH(arr); i++)
    {
        int small = i;
        for(int j = i+1; j < ARRAY_LENGTH(arr); j++)
        {
            if(arr[j] < arr[small])
            {
                small = j;
            }
        }

        if(small != i)
        {
            int tmp = arr[i];

            arr[i] = arr[small];
            arr[small] = tmp;
        }

    }

    for(int i = 0; i < ARRAY_LENGTH(arr); i++)
    {
        printf("[%i] = %i\n", i, arr[i]);
    }
}
