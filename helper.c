#include "helper.h"

void swap(int *a1, int *a2)
{
    int temp = *a1;
    *a1 = *a2;
    *a2 = temp;
}

void printArray(int *arr, const unsigned int uArrSize)
{
    for(int i = 0; i < uArrSize; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int min(int a, int b)
{
    return (a <= b) ? a : b;
}