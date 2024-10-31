#include <stdio.h>
#include <stdlib.h>

#include "helper.h"

void swap(int *a1, int *a2)
{
    int temp = *a1;
    *a1 = *a2;
    *a2 = temp;
}

void printArray(int *pnArr, const int nArrSize)
{
    int i = 0;

    for(i = 0; i < nArrSize; ++i)
    {
        printf("%d ", pnArr[i]);
    }
    printf("\n");
}

int min(int n1, int n2)
{
    return n1 <= n2 ? n1 : n2;
}

int max(int n1, int n2)
{
    return n1 >= n2 ? n1 : n2;
}