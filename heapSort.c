#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "definitions.h"
#include "heapSort.h"

/**
 * @function maxHeapifyRecursive
 * @abstract the basic routine for heap sort,
 *           heapify the maxHeap at uIndex recursively
 * ! uIndex is 0-based
 *
 * @param maxHeap pointer pointing to the heap
 * @param uHeapSize how many element that are in the current heap
 * @param uIndex the index location to do the heapify operation
 * @return if invalid inputs returning -1, return 0 if merged successfully;
 */
int maxHeapifyRecursive(
    int* maxHeap, const unsigned int uArrSize, const unsigned int uIndex)
{
    unsigned int uLeftIndex = 0, uRightIndex = 0;
    unsigned int uLargetIndex = 0;

    if(maxHeap == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return -1;
    }

    if(uIndex >= uArrSize)
    {
        printf("%s, %s, %s\n",  SORT_TYPE_HEAPSORT_RECURSIVE,
            ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_UINDEX);
        return -1;
    }

    uLargetIndex = uIndex;
    uLeftIndex = uIndex * 2 + 1;
    uRightIndex = uLeftIndex + 1;

    if(uLeftIndex < uArrSize && maxHeap[uLeftIndex] > maxHeap[uLargetIndex])
    {
       uLargetIndex = uLeftIndex;
    }

    if(uRightIndex < uArrSize && maxHeap[uRightIndex] > maxHeap[uLargetIndex])
    {
        uLargetIndex = uRightIndex;
    }

    if(uLargetIndex != uIndex)
    {
        swap(&maxHeap[uLargetIndex], &maxHeap[uIndex]);
        maxHeapifyRecursive(maxHeap, uArrSize, uLargetIndex);
    }

    return 0;
}

/**
 * @function maxHeapifyIterative
 * @abstract the basic routine for heap sort,
 *           heapify the maxHeap at uIndex iteratively
 * ! uIndex is 0-based
 *
 * @param maxHeap pointer pointing to the heap
 * @param uHeapSize how many element that are in the current heap
 * @param uIndex the index location to do the heapify operation
 * @return if invalid inputs returning -1, return 0 if merged successfully;
 */
int maxHeapifyIterative(
    int* maxHeap, const unsigned int uArrSize, const unsigned int uIndex)
{
    unsigned int uLeftIndex = 0, uRightIndex = 0;
    unsigned int uLargetIndex = 0;
    static int iStack[gSTACK_SIZE];
    int iStackIndex = -1;

    if(maxHeap == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return -1;
    }

    if(uIndex >= uArrSize)
    {
        printf("%s, %s, %s\n",  SORT_TYPE_HEAPSORT_RECURSIVE,
            ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_UINDEX);
        return -1;
    }

    iStackIndex = -1;
    iStack[++iStackIndex] = uIndex;

    while(iStackIndex > 0)
    {
        uLargetIndex = iStack[iStackIndex--];
        uLeftIndex = uIndex * 2 + 1;
        uRightIndex = uLeftIndex + 1;

        if(uLeftIndex < uArrSize && maxHeap[uLeftIndex] > maxHeap[uLargetIndex])
        {
            uLargetIndex = uLeftIndex;
        }

        if(uRightIndex < uArrSize && maxHeap[uRightIndex] > maxHeap[uLargetIndex])
        {
            uLargetIndex = uRightIndex;
        }

        if(uLargetIndex != uIndex)
        {
            swap(&maxHeap[uLargetIndex], &maxHeap[uIndex]);
            iStack[++iStackIndex] = uLargetIndex;
        }
    }

    return 0;
}

/**
 * @function buildHeap
 * @abstract build a maxHeap stucture from an unsorted array
 *
 * @param arr unsorted array
 * @param uArrSize the size of the array
 * @param bRecursive running recursively or iteratitve
 * @return
 */
void buildHeap(int* arr, const unsigned int uArrSize, bool bRecursive)
{
    int i = 0;

    if(arr == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return;
    }

    if(uArrSize <= 0)
    {
        printf("%s %s %s", FUNC_NAME_BUILDHEAP,
            ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_ARRAY_SIZE);
        return;
    }

    for(i = uArrSize / 2 - 1; i >= 0; --i)
    {
        if(bRecursive)
        {
            maxHeapifyRecursive(arr, uArrSize, i);
        }
        else
        {
            maxHeapifyIterative(arr, uArrSize, i);
        }
    }
}

/**
 * @function heapSort
 * @abstract to perform heap sort on interger array
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @param bRecursive whether to run recursively (or false, run iteratively)
 * @return
 */
void heapSort(int* arr, const unsigned int uArrSize, bool bRecursive)
{
    int curHeapSize = 0;

    buildHeap(arr, uArrSize, bRecursive);
    swap(&arr[0], &arr[uArrSize - 1]);

    // going through the arr, which curHeapSize is the current maintained heap size
    for(curHeapSize = uArrSize - 1; curHeapSize > 1; --curHeapSize)
    {
        if(bRecursive)
        {
            maxHeapifyRecursive(arr, curHeapSize, 0);
        }
        else
        {
            maxHeapifyIterative(arr, curHeapSize, 0);
        }

        swap(&arr[0], &arr[curHeapSize - 1]);
    }
}