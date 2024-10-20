#include <stdio.h>
#include <stdlib.h>

#include "heapSort.h"

/**
 * @function minHeapify
 * @abstract the basic routine for heap sort, heapify the arr
 * index are 0-based
 *
 * @param heap pointer pointing to the heap
 * @param uHeapSize how many element that are in the current heap
 * @return if invalid inputs returning -1, return 0 if heapify successfully;
 */
int minHeapify(int* minHeap, const unsigned int uArrSize, const unsigned int uIndex)
{
    unsigned int uLeftIndex = 0, uRightIndex = 0;

    // checks

    uLeftIndex = uIndex * 2 + 1;
    uRightIndex = uLeftIndex + 1;

    if(uLeftIndex < uArrSize && minHeap[uLeftIndex] < minHeap[uIndex])
    {
        swap(&minHeap[uLeftIndex], &minHeap[uIndex]);
    }

    if(uRightIndex < uArrSize && minHeap[uRightIndex] < minHeap[uIndex])
    {
        swap(&minHeap[uRightIndex], &minHeap[uIndex]);
    }

    return 0;
}

void buildHeap(int* arr, const unsigned int uArrSize)
{
    int i = 0;

    for(i = uArrSize / 2 - 1; i >= 0; --i)
    {
        minHeapify(arr, uArrSize, i);
    }

    printArray(arr, uArrSize);
}