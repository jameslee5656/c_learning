#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "definitions.h"
#include "mergeSort.h"


/**
 * @Description: merge two presumed sorted range, left ~ middle - 1, middle ~ right
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @param left, middle:
 *  the first range is left ~ (middle - 1), presumed sorted
 * @param middle, right:
 *  the second range is middle ~ right, presumed sorted
 * @return int, MERGE_SUCCESS(0), or other failure(<= 0)
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.28 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
int merge(int *pnArr, const int nArrSize, int nLeft, int nMiddle, int nRight)
{
// 1. A preallocated array space (size at least nArrSize),
    // with nIndex pointing to the start of the preallocated array,
    // nLeftIndex pointing to nLeft, nRightIndex pointing to nMiddle
    int nLeftIndex = 0, nRightIndex = 0;
    int nSmallerVal = 0, nIndex = 0;
    static int anPreAllocatedArr[gRANDOM_ARRAY_SIZE];

    if(NULL == pnArr)                   return ERROR_ARRAY_INVALID;
    if(gRANDOM_ARRAY_SIZE < nArrSize)   return ERROR_INPUT_PARAM_INVLID;
    if(nLeft >= nMiddle)                return ERROR_INPUT_PARAM_INVLID;
    if(nMiddle > nRight)                return ERROR_INPUT_PARAM_INVLID;

    nLeftIndex = nLeft;
    nRightIndex = nMiddle;
    nIndex = 0;

    // 2.1 Find the smallest value from nLeftIndex, nRightIndex
    //     put the value in nIndex location,
    //     move forward the nIndex and the smaller Index(nLeftIndex, or nRightIndex)
    //     until either nRightIndex > nRight or nLeftIndex > middle - 1
    while(nRightIndex <= nRight && nLeftIndex <= nMiddle - 1)
    {
        if(pnArr[nLeftIndex] <= pnArr[nRightIndex])
        {
            nSmallerVal = pnArr[nLeftIndex++];
        }
        else
        {
            nSmallerVal = pnArr[nRightIndex++];
        }

        anPreAllocatedArr[nIndex++] = nSmallerVal;
    }

    // 2.2 if either nLeftIndex > middle or nRightIndex > nRight
    // 2.2.1 nLeftIndex > nMiddle - 1, copy nRightIndex -> right to nIndex
    if(nLeftIndex > nMiddle - 1 && nRightIndex <= nRight)
    {
        memcpy(&anPreAllocatedArr[nIndex], &pnArr[nRightIndex], sizeof(int) * (nRight - nRightIndex + 1));
    }
    // 2.2.2 nRightIndex > nRight, copy nLeftIndex -> middle - 1 to nIndex
    else if(nRightIndex > nRight && nLeftIndex <= nMiddle - 1)
    {
        memcpy(&anPreAllocatedArr[nIndex], &pnArr[nLeftIndex], sizeof(int) * (nMiddle - nLeftIndex));
    }

    // 3. copy preallocated result to pnArr (left -> right)
    memcpy(&pnArr[nLeft], &anPreAllocatedArr[0], sizeof(int) * (nRight - nLeft + 1));
    return SUCCESS_MERGE;
}

/**
 * @Description: public function, merge sort pnArr recursively
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.28 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void mergeSortRecursive(int *pnArr, int nArrSize)
{
    int nMiddle = 0;

    if(NULL == pnArr)                   return;
    if(gRANDOM_ARRAY_SIZE < nArrSize)   return;

    nMiddle = nArrSize / 2;
    __mergeSortRecursive(pnArr, nArrSize, 0, nMiddle, nArrSize - 1);
}

/**
 * @Description: private function, merge sort pnArr recursively
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @param nLeft, nMiddle:
 *  recursively seperate the left part, nLeft ~ nMiddle - 1, of the array;
 * @param nMiddle, nRight:
 *  recursively sperate the right part, nMiddle ~ nRight, of the array;
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.28 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void __mergeSortRecursive(int *pnArr, int nArrSize, int nLeft, int nMiddle, int nRight)
{
    int nNextMiddle = 0;
    int nMergeResult = 0;

    if(NULL == pnArr)                   return;
    if(gRANDOM_ARRAY_SIZE < nArrSize)   return;
    if(nLeft >= nMiddle)                return;
    if(nMiddle > nRight)                return;
    if(nMiddle >= nArrSize)             return;
    if(nRight >= nArrSize)              return;

    // 1. divide array into blocks until it's undividable (only one element), then start merging each blocks back
    nNextMiddle = nLeft + (nMiddle - nLeft) / 2;
    __mergeSortRecursive(pnArr, nArrSize, nLeft, nNextMiddle, nMiddle - 1);
    nNextMiddle = nMiddle + (nRight - nMiddle + 1) / 2;
    __mergeSortRecursive(pnArr, nArrSize, nMiddle, nNextMiddle, nRight);

    // 2, merging it back from the bottom of the level
    nMergeResult = merge(pnArr, nArrSize, nLeft, nMiddle, nRight);
    if(nMergeResult < 0)
    {
        printf("%s result:%d\n", ERROR_MERGE_FAILED, nMergeResult);
    }
}