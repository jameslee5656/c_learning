#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <memory.h>

#include "definitions.h"
#include "helper.h"
#include "tests.h"
#include "qsort.h"

/*
* specification
* the array range would be -10^6 ~ 10^6 of the random number
* the array could have maximum 10^6 numbers
*/

/**
 * @function loopSortAndTime
 * @abstract looping the sorting function and print out how long it is
 *
 * @param sortFunc sorting function pointer
 * @param sSortName char pointer for sorting name
 * @param arr integer array that needed to be sort
 * @param randomArr after the sort we could restore the random from this array
 * @param uArrSize array size for both arr and randomArr
 * return
 */
void loopSortAndTime(void (*sortFunc)(int *arr, const unsigned int uArrSize), char *sSortName
    , int *arr, int *randomArr, const unsigned int uArrSize)
{
    int i = 0, sum = 0;
    clock_t begin, end;

    printf("starting %s \n", sSortName);
    for(i = 0; i < gLOOP; ++i)
    {
        memcpy(arr, randomArr, sizeof(int) * uArrSize);
        begin = clock();
        sortFunc(arr, uArrSize);
        end = clock();
        sum += (end - begin);
        if(verifyArray(arr, uArrSize) == false)
        {
            printf("%s %s\n", ERROR_VERIFY_FAILURE, sSortName);
        }
    }
    printf("Spend Time:[%f]\n", (float) sum / gLOOP / CLOCKS_PER_SEC);
    printf("***********************\n");
}

int main(void)
{
    time_t t;
    int i = 0, j = 0, temp = 0, uArrSize = 0, iBase = 0;
    int arr[gARR_SIZE];
    int randomArr[gARR_SIZE];
    int randomNegArr[2];

    time(&t);
    srand(t);

    uArrSize = gARR_SIZE;
    randomNegArr[0] = 1;
    randomNegArr[1] = -1;
    for(int i = 0; i < uArrSize; ++i)
    {
        // generate 0 ~ gMAX_NUM number
        arr[i] = rand() % (gMAX_NUM + 1);
        // randomly multiple -1 to become negative number
        arr[i] *= randomNegArr[rand() % 2];
    }

    memcpy(randomArr, arr, sizeof(int) * uArrSize);

#ifdef DEBUG
    printArray(arr, uArrSize);
#endif // DEBUG

    // QuickSort
    unitTestPartitionFunc(&partition);

    // QuickSort Recursive
    unitTestSortFunc(&quickSortRecursive, SORT_TYPE_QUICKSORT_RECURSIVE);
    loopSortAndTime(quickSortRecursive, SORT_TYPE_QUICKSORT_RECURSIVE,
        arr, randomArr, uArrSize);

    // QuickSort Iterative
    unitTestSortFunc(&quickSortIterative, SORT_TYPE_QUICKSORT_ITERATIVE);
    loopSortAndTime(quickSortIterative, SORT_TYPE_QUICKSORT_ITERATIVE,
        arr, randomArr, uArrSize);

}