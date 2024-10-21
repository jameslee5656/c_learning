#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include <memory.h>

#include "definitions.h"
#include "helper.h"
#include "qsort.h"
#include "mergeSort.h"
#include "heapSort.h"

/**
 * @function verifyArray
 * @abstract checking that if the array is non-decreasing
 * @param arr array that needed to be non-decreasing
 * @param uArrSize the array size
 * return bool, verify passed or not
 */
bool verifyArray(int* arr, const unsigned int uArrSize)
{
    int i = 0;

    for(i = 1; i < uArrSize; ++i)
    {
        if(arr[i - 1] > arr[i])
        {
            printf("%s at %d, arr[i - 1]:%d arr[i]:%d\n",
                ERROR_VERIFY_FAILURE, i, arr[i - 1], arr[i]);
            return false;
        }
    }

    return true;
}

int main(void)
{
    time_t t;
    int i = 0, j = 0, temp = 0, sum = 0, uArrSize = 0, iBase = 0;
    clock_t begin, end;
    int arr[gN];

    time(&t);
    srand(t);

    if(gN > INT_MAX)
    {
        printf("%s\n", ERROR_GN_LARGER_THAN_INT_MAX);
    }

    // putting a much wider range of numbers into the array
    //  (include negative)
    uArrSize = gN;
    iBase = -1 * gN;
    for(i = 0; i < uArrSize; ++i)
    {
        arr[i] = iBase + (rand() % 10);
        ++iBase;
    }

    // scamble A
    for(i = uArrSize - 1; i > 0; --i)
    {
        j = rand() % (i + 1);
        temp = arr[i];
        swap(&arr[i], &arr[j]);
    }

#ifdef DEBUG
    printArray(arr, uArrSize);
#endif // DEBUG

    // copy one to restore
    int restoreArr[uArrSize];
    memcpy(restoreArr, arr, sizeof(int) * uArrSize);

    // quick sort iterative
    {
        printf("starting %s \n", SORT_TYPE_QUICKSORT_ITERATIVE);
        for(i = 0; i < gLOOP; ++i)
        {
            memcpy(arr, restoreArr, sizeof(int) * uArrSize);
            begin = clock();
            quickSortIterative(arr, uArrSize);
            end = clock();
            sum += (end - begin);
            if(verifyArray(arr, uArrSize) == false)
            {
                printf("%s %s\n", ERROR_VERIFY_FAILURE, SORT_TYPE_QUICKSORT_ITERATIVE);
            }
        }
        printf("Spend Time:[%f]\n", (float) sum / gLOOP / CLOCKS_PER_SEC);
        printf("***********************\n");
    }

    // quick sort recursive
    {
        printf("starting %s \n", SORT_TYPE_QUICKSORT_RECURSIVE);
        sum = 0;
        for(i = 0; i < gLOOP; ++i)
        {
            memcpy(arr, restoreArr, sizeof(int) * uArrSize);
            begin = clock();
            quickSortRecursive(arr, uArrSize);
            end = clock();
            sum += (end - begin);
            if(verifyArray(arr, uArrSize) == false)
            {
                printf("%s %s\n", ERROR_VERIFY_FAILURE, SORT_TYPE_QUICKSORT_RECURSIVE);
            }
        }
        printf("Spend Time:[%f]\n", (float) sum / gLOOP / CLOCKS_PER_SEC);
        printf("***********************\n");
    }

    // merge sort recursive
    {
        printf("starting %s \n", SORT_TYPE_MERGESORT_RECURSIVE);
        sum = 0;
        for(i = 0; i < gLOOP; ++i)
        {
            memcpy(arr, restoreArr, sizeof(int) * uArrSize);
            begin = clock();
            mergeSortRecursive(arr, uArrSize);
            end = clock();
            sum += (end - begin);
            if(verifyArray(arr, uArrSize) == false)
            {
                printf("%s %s\n", ERROR_VERIFY_FAILURE, SORT_TYPE_MERGESORT_RECURSIVE);
            }
        }
        printf("Spend Time:[%f]\n", (float) sum / gLOOP / CLOCKS_PER_SEC);
        printf("***********************\n");
    }

    // merge sort iterative
    {
        printf("starting %s \n", SORT_TYPE_MERGESORT_ITERATIVE);
        sum = 0;
        for(i = 0; i < gLOOP; ++i)
        {
            memcpy(arr, restoreArr, sizeof(int) * uArrSize);
            begin = clock();
            mergeSortIterative(arr, uArrSize);
            end = clock();
            sum += (end - begin);
            if(verifyArray(arr, uArrSize) == false)
            {
                printf("%s %s\n", ERROR_VERIFY_FAILURE, SORT_TYPE_MERGESORT_ITERATIVE);
            }
        }
        printf("Spend Time:[%f]\n", (float) sum / gLOOP / CLOCKS_PER_SEC);
        printf("***********************\n");
    }

    // heap sort recursively
    {
        printf("starting %s \n", SORT_TYPE_HEAPSORT_RECURSIVE);
        sum = 0;
        for(i = 0; i < gLOOP; ++i)
        {
            memcpy(arr, restoreArr, sizeof(int) * uArrSize);
            begin = clock();
            // recursively
            heapSort(arr, uArrSize, true);

            end = clock();
            sum += (end - begin);
            if(verifyArray(arr, uArrSize) == false)
            {
                printf("%s %s\n", ERROR_VERIFY_FAILURE, SORT_TYPE_HEAPSORT_RECURSIVE);
            }
    #ifdef DEBUG
            printArray(arr, uArrSize);
    #endif // DEBUG
        }
        printf("Spend Time:[%f]\n", (float) sum / gLOOP / CLOCKS_PER_SEC);
        printf("***********************\n");
    }

    // heap sort iteratively
    {
        printf("starting %s \n", SORT_TYPE_HEAPSORT_ITERATIVE);
        sum = 0;
        for(i = 0; i < gLOOP; ++i)
        {
            memcpy(arr, restoreArr, sizeof(int) * uArrSize);
            begin = clock();
            // recursively
            heapSort(arr, uArrSize, true);

            end = clock();
            sum += (end - begin);
            if(verifyArray(arr, uArrSize) == false)
            {
                printf("%s %s\n", ERROR_VERIFY_FAILURE, SORT_TYPE_HEAPSORT_ITERATIVE);
            }
    #ifdef DEBUG
            printArray(arr, uArrSize);
    #endif // DEBUG
        }
        printf("Spend Time:[%f]\n", (float) sum / gLOOP / CLOCKS_PER_SEC);
        printf("***********************\n");
    }
}
