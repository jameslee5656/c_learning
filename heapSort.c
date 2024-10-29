#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "heapSort.h"
#include "definitions.h"

/**
 * @Description: recurisvely heapify the array
 * @param pnArr, nArrSize
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @param nIndex
 *  heapify the array starting from nIndex
 *  if(nIndex >= nArrSize) return SUCCESS_HEAPIFY
 * @return
 */
void heapifyRecursive(int *pnArr, const int nArrSize, const int nIndex)
{
    int nMaxIndex = 0, nMaxValue = 0;
    int nLeftIndex = 0, nRightIndex = 0;

    if(NULL == pnArr)       return;
    if(0 >= nArrSize)       return;
    // 1. Ends the recursive call if nIndex reach the end of the array
    if(nArrSize <= nIndex)  return;

    // 2.1 find the max comparing with nIndex, leftChild, rightChild;
    nMaxIndex = nIndex;
    nMaxValue = pnArr[nIndex];
    nLeftIndex = nIndex * 2 + 1;
    nRightIndex = nIndex * 2 + 2;

    if(nLeftIndex < nArrSize && pnArr[nLeftIndex] > nMaxValue)
    {
        nMaxIndex = nLeftIndex;
        nMaxValue = pnArr[nLeftIndex];
    }

    if(nRightIndex < nArrSize && pnArr[nRightIndex] > nMaxValue)
    {
        nMaxIndex = nRightIndex;
        nMaxValue = pnArr[nRightIndex];
    }

    // 2.2 swap with nIndex and nMaxIndex
    swap(&pnArr[nIndex], &pnArr[nMaxIndex]);

    // 3. Recusively heapify the nIndexs' child
    heapifyRecursive(pnArr, nArrSize, nLeftIndex);
    heapifyRecursive(pnArr, nArrSize, nRightIndex);
}

/**
 * @Description: iteratively heapify the array
 * @param pnArr, nArrSize
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @param nIndex
 *  heapify the array starting from nIndex
 *  if(nIndex >= nArrSize) return SUCCESS_HEAPIFY
 * @return
 */
void heapifyIterative(int *pnArr, const int nArrSize, const int nIndex)
{
    static int naStack[gSTACK_SIZE];
    int nStackIndex = -1;
    int nStackTopVal = 0;
    int nLeftIndex = 0, nRightIndex = 0;
    int nMaxIndex = 0, nMaxValue = 0;

    if(NULL == pnArr)       return;
    if(0 >= nArrSize)       return;
    // 1. Ends the recursive call if nIndex reach the end of the array
    if(nArrSize <= nIndex)  return;

    // 1. put nIndex into naStack
    naStack[++nStackIndex] = nIndex;

    while(nStackIndex >= 0)
    {
        // 2.1 pop the stack and get the top index from stack
        nStackTopVal = naStack[nStackIndex--];

        // 2.2 find out if the topIndex is the max compare with it's child
            // at the same time, put nLeftIndex into the stack
        nMaxIndex = nStackTopVal;
        nMaxValue = pnArr[nStackIndex];

        nLeftIndex = nStackTopVal * 2 + 1;
        nRightIndex = nStackTopVal * 2 + 2;

        if(nArrSize > nLeftIndex)
        {
            if(pnArr[nLeftIndex] > nMaxValue)
            {
                nMaxIndex = nLeftIndex;
                nMaxValue = pnArr[nLeftIndex];
            }

            naStack[++nStackIndex] = nLeftIndex;
        }

        if(nArrSize > nRightIndex)
        {
            if(pnArr[nRightIndex] > nMaxValue)
            {
                nMaxIndex = nRightIndex;
                nMaxValue = pnArr[nRightIndex];
            }

            naStack[++nStackIndex] = nRightIndex;
        }


        // 2.3 swap nIndex with nMaxIndex
        swap(&pnArr[nStackTopVal], &pnArr[nMaxIndex]);
    }
}

/**
 * @function buildHeap
 * @abstract build a maxHeap stucture from an unsorted array
 *
 * @param pnArr unsorted array
 * @param nArrSize the size of the array
 * @param bRecursive running recursively or iteratitve
 * @return
 */
void buildHeap(int *pnArr, const int nArrSize, bool bRecursive)
{
    int i = 0;

    if(NULL == pnArr)       return;
    if(0 >= nArrSize)       return;

    // from n / 2 - 1 (non-leaves) index and start heapify each element
    for(i = nArrSize / 2 - 1; i >= 0; --i)
    {
        if(bRecursive)
        {
            maxHeapifyRecursive(pnArr, nArrSize, i);
        }
        else
        {
            maxHeapifyIterative(pnArr, nArrSize, i);
        }
    }
}