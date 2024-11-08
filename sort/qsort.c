#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"
#include "helper.h"
#include "qsort.h"

/**
 * @function partition
 * @abstact parition the array and split it into two part,
 *          smaller and bigger one of pivot
 * @example arr = {3, 1, 4, 2, 5}
 * (1) intialized i, index, and assigned pivot
 * 3, 1, 4, 2, 5
 * ^---pivot
 * ^---nLeft
 *             ^---nRight
 * ^---index
 *    ^---i
 *
 * (2) i go through the array, and swap with index if it is smaller than pivot
 * (2.1) arr[i] is smaller than pivot, do a swap with ++index
 * 3, 1, 4, 2, 5
 * ^---index
 *    ^---i
 * swap(++index = 1, i = 1);
 * 3, 1, 4, 2, 5
 *
 * (2.2) arr[i] is smaller than pivot, do a swap with ++index
 * 3, 1, 4, 2, 5
 *    ^---index
 *          ^---i
 *
 * swap(++index = 2, i = 3);
 * 3, 1, 2, 4, 5
 *       ^---index
 *
 * (3) swap the nLeft with the index
 * 2, 1, 3, 4, 5
 *       ^---index
 * return index, if <= 0 means there's some error;
 */
int partition(int *pnArr, const int nArrSize, int nLeft, int nRight)
{
    int i = 0;
    int pivot = 0, index = 0;

    // check1, make sure array is valid
    if(NULL == pnArr) return ERROR_ARRAY_INVALID;

    // check2 make sure nArrSize is not 0
    if(0 >= nArrSize)   return ERROR_ARRAY_SIZE_INVALID;

    // check3 if iLeft, and iRight is valid
    if(nRight <= nLeft) return ERROR_INPUT_PARAM_INVLID;

    // check4 param nLeft, nRight is valid and within the boundary of nArrSize
    if(nLeft >= nArrSize || nRight >= nArrSize || nArrSize < nRight - nLeft + 1)
    {
        return ERROR_INPUT_PARAM_INVLID;
    }

    // (1) intialize i, index, and assigned pivot
    index = nLeft;
    pivot = pnArr[index];

    // (2) i go through the array, and swap with index if it is smaller than pivot
    for(i = nLeft + 1; i <= nRight; ++i)
    {
        if(pnArr[i] < pivot)
        {
            swap(&pnArr[i], &pnArr[++index]);
        }
    }

    // (3) swap the pivot (nLeft) with the index
    swap(&pnArr[index], &pnArr[nLeft]);
    return index;
}

/**
 * @public function quickSortRecursive
 * @abstract recursively quick sort an integer array
 * @param pnArr pointing to the integer array
 * @param nArrSize expected size of the array
 * @return
*/
void quickSortRecursive(int *pnArr, const int nArrSize)
{
    if(NULL == pnArr) return;

    if(0 == nArrSize) return;

    __quickSortRecursive(pnArr, nArrSize, 0, nArrSize - 1);
}

/**
 * @private function __quickSortRecursive
 * @abstract do the quick sort recursively with an integer array
 * @param pnArr pointing to the integer array
 * @param nArrSize expected size of the array
 * @param nLeft left side of the partition location, included left
 * @param nRight right side of the partition location, included right
 * @return
*/
void __quickSortRecursive(
    int *pnArr, const int nArrSize, int nLeft, int nRight)
{
    int iPartitionResult = 0;

    // check1, make sure array is valid
    if(NULL == pnArr) return;

    // check2 make sure nArrSize is not 0
    if(0 == nArrSize) return;

    // check3 if iLeft, and iRight is valid
    if(nRight <= nLeft) return;

    // check4 param nLeft, nRight is valid and within the boundary of nArrSize
    if(nLeft >= nArrSize || nRight >= nArrSize || nArrSize < nRight - nLeft + 1)
    {
        return;
    }

    // 2. parition and get the middle location
    iPartitionResult = partition(pnArr, nArrSize, nLeft, nRight);
    if(0 > iPartitionResult)
    {
        printf("%s ErrorCode:%d", FUNC_NAME_PARTITION, iPartitionResult);
        return;
    }

    // 3.1 recursively sort the left part
    __quickSortRecursive(pnArr, nArrSize, nLeft, iPartitionResult - 1);

    // 3.2 recursively sort the right part
    __quickSortRecursive(pnArr, nArrSize, iPartitionResult + 1, nRight);
}

/**
 * @public function quickSortIterative
 * @abstract iteratively quick sort an integer array
 * iStack's size should always either empty or 2's multiple number
 * example
 * iStack[1] = 0 (nLeft)
 * iStack[0] = nArrSize - 1 (nRight)
 *
 * @param pnArr pointing to the integer array
 * @param nArrSize expected size of the array
 * @return
*/
void quickSortIterative(int *pnArr, const int nArrSize)
{
    int iStackIndex = -1, iPartitionResult = 0;
    int nLeft = 0, nRight = 0;
    static int iStack[gSTACK_SIZE];

    // check1, make sure array is valid
    if(NULL == pnArr)     return;

    // check2 make sure nArrSize is not 0
    if(0 >= nArrSize)     return;

    // (1) Initialize the nLeft, nRight, and put into the stack
    nLeft = 0;
    nRight = nArrSize - 1;
    iStack[++iStackIndex] = nRight;
    iStack[++iStackIndex] = nLeft;

    // (2) getting nLeft and nRight from the stack and keep partition until the stack empty
    while(0 < iStackIndex)
    {
        // (2.1) get nLeft, nRight from top of the stack
        nLeft = iStack[iStackIndex--];
        nRight = iStack[iStackIndex--];
        iPartitionResult = partition(pnArr, nArrSize, nLeft, nRight);

        if(0 > iPartitionResult)
        {
            printf("%s ErrorCode:%d", FUNC_NAME_PARTITION, iPartitionResult);
            return;
        }

        // (2.2) putting the nLeft, iPartitionIndex - 1
            // into the stack if it is valid range
        if(iPartitionResult > 0 && nLeft < iPartitionResult - 1)
        {
            iStack[++iStackIndex] = iPartitionResult - 1;
            iStack[++iStackIndex] = nLeft;
        }

        // (2.3) putting the iPartitionIndex + 1, nRight
            // into the stack if it is valid range
        if(nRight > iPartitionResult + 1)
        {
            iStack[++iStackIndex] = nRight;
            iStack[++iStackIndex] = iPartitionResult + 1;
        }
    }
}