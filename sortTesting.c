#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <memory.h>

#include "definitions.h"
#include "helper.h"
#include "tests.h"
#include "qsort.h"
#include "mergeSort.h"

/*
* specification
* the array range would be -2^30 ~ 2^30 of the random number
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
 * @param nArrSize array size for both arr and randomArr
 * return
 */
void loopSortAndTime(void (*sortFunc)(int *pnArr, const int nArrSize), char *sSortName
    , int *arr, int *randomArr, const int nArrSize);

/**
 * @function createRandomArray
 * @abstract put in random number into a pre-allocated array with nArrSize
 * @param pnArr, the pointer pointing to the integer array
 * @param nArrSize, the array size
 * @param nRandomMax, the max number for of the random generated number
 * @param nRandomMin, the min number for of the random generated number
 * return if < 0, something is wrong with generating the randomArray
*/
int createRandomArray(int *pnArr, const int nArrSize, int nRandomMax, int nRandomMin);

int main(void)
{
    time_t t;
    int i = 0, j = 0, temp = 0, nArrSize = 0, iBase = 0;
    int result = 0;
    int *pnArr = NULL;
    int *pnRandomArray = NULL;

    time(&t);
    srand(t);
    nArrSize = gRANDOM_ARRAY_SIZE;
    pnArr = (int*) malloc(sizeof(int) * nArrSize);
    pnRandomArray = (int*) malloc(sizeof(int) * nArrSize);

#ifdef DEBUG
    result = createRandomArray(pnArr, nArrSize, 1000, -1000);
#else
    result = createRandomArray(pnArr, nArrSize,
        gRANDOM_UPPER_LIMIT, gRANDOM_LOWER_LIMIT);
#endif // DEBUG
    if(result < 0)
    {
        printf("%s ErrorCode:%d\n", FUNC_NAME_CREATE_RANDOM_ARRAY, result);
        goto ProcessEnd;
    }
    memcpy(pnRandomArray, pnArr, sizeof(int) * nArrSize);

#ifdef DEBUG
    printf("randomArray: ");
    printArray(pnRandomArray, nArrSize);
#endif // DEBUG

    // Parition
    unitTestPartitionFunc(&partition);

    // QuickSort Recursively
    unitTestSortFunc(&quickSortRecursive, SORT_TYPE_QUICKSORT_RECURSIVE);
    loopSortAndTime(quickSortRecursive, SORT_TYPE_QUICKSORT_RECURSIVE,
        pnArr, pnRandomArray, nArrSize);

    // QuickSort Iteratively
    unitTestSortFunc(&quickSortIterative, SORT_TYPE_QUICKSORT_ITERATIVE);
    loopSortAndTime(quickSortIterative, SORT_TYPE_QUICKSORT_ITERATIVE,
        pnArr, pnRandomArray, nArrSize);

    // Merge
    unitTestMergeFunc(&merge);

    // MergeSort Recursively
    unitTestSortFunc(&mergeSortRecursive, SORT_TYPE_MERGESORT_RECURSIVE);


ProcessEnd:
    if(NULL != pnArr)
    {
        free(pnArr);
        pnArr = NULL;
    }

    if(NULL != pnRandomArray)
    {
        free(pnRandomArray);
        pnRandomArray = NULL;
    }

    return 0;
}

/**
 * @function loopSortAndTime
 * @abstract looping the sorting function and print out how long it is
 *
 * @param sortFunc sorting function pointer
 * @param sSortName char pointer for sorting name
 * @param arr integer array that needed to be sort
 * @param randomArr after the sort we could restore the random from this array
 * @param nArrSize array size for both arr and randomArr
 * return
 */
void loopSortAndTime(void (*sortFunc)(int *arr, const int nArrSize), char *sSortName
    , int *arr, int *randomArr, const int nArrSize)
{
    int i = 0, sum = 0;
    clock_t begin, end;

    printf("starting %s \n", sSortName);
    for(i = 0; i < gLOOP; ++i)
    {
        memcpy(arr, randomArr, sizeof(int) * nArrSize);
        begin = clock();
        sortFunc(arr, nArrSize);
        end = clock();
        sum += (end - begin);

        if(verifyArray(arr, nArrSize) == false)
        {
            printf("%s %s\n", ERROR_VERIFY_FAILURE, sSortName);
        }
    }
    printf("Spend Time:[%f]\n", (float) sum / gLOOP / CLOCKS_PER_SEC);
    printf("***********************\n");
}

/**
 * @function createRandomArray
 * @abstract put in random number into a pre-allocated array with nArrSize
 * @param pnArr, the pointer pointing to the integer array
 * @param nArrSize, the array size
 * @param nRandomMax, the max number for of the random generated number
 * @param nRandomMin, the min number for of the random generated number
 * return if < 0, something is wrong with generating the randomArray
*/
int createRandomArray(int *pnArr, const int nArrSize, int nRandomMax, int nRandomMin)
{
    time_t t = time(NULL);
    int nInterval = 0, i = 0;

    // checkes for each param is valid
    if(NULL == pnArr) return ERROR_ARRAY_INVALID;
    if(0 == nArrSize) return ERROR_ARRAY_SIZE_INVALID;
    if(nRandomMax <= nRandomMin) return ERROR_INPUT_PARAM_INVLID;
    if(nRandomMax > gRANDOM_UPPER_LIMIT) return ERROR_INPUT_PARAM_INVLID;
    if(nRandomMin < gRANDOM_LOWER_LIMIT) return ERROR_INPUT_PARAM_INVLID;

    time(&t);
    srand(t);

    // Random algorithm:
    // Step1: r = rand() % interval -> interval = RANGE_MAX - RANGE_MIN (+1), if +1 includes max
    // Step2: r += RANGE_MIN
    nInterval = nRandomMax - nRandomMin + 1;
    for(i = 0; i < nArrSize; ++i)
    {
        pnArr[i] = rand() % nInterval + nRandomMin;
    }

    return 0;
}
