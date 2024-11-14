#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *arr, int value, int left, int right);
void printArray(int *arr, int size);

int main() {
    int number = get_int("Number to search: ");

    //Numbers must be arrenged
    int numbers[] = {10,20,25,30,40,50,60,70,80,90};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    int found = binarySearch(numbers,number,0,size-1);

    printArray(numbers, size);

    if(found >= 0)
    {
        printf("Number %i is founded at index [%i]\n", number, found);
    }
    else
    {
        printf("Not found\n");
    }

    return 0;
}


int binarySearch(int *arr, int value, int left, int right)
{
    int mid = left + (right - left) / 2;

    // Array boundaries
    if(left > right || right < left)
    {
        return -1;
    }

    if(arr[mid]==value)
    {
        return mid;
    }
    else if(value < arr[mid])
    {
        return binarySearch(arr,value,left,mid-1);
    }
    else
    {
        return binarySearch(arr,value,mid+1,right);
    }

    return -1;
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
