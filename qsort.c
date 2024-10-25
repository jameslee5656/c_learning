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
 * ^---uLeft
 *             ^---uRight
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
 * (3) swap the uLeft with the index
 * 2, 1, 3, 4, 5
 *       ^---index
 * return index, if <= 0 means there's some error;
 */
int partition(int *pnArray, const unsigned int uArrSize,
    unsigned int uLeft, unsigned int uRight)
{
    int i = 0;
    int pivot = 0;
    unsigned int index = 0;

    // check1, make sure array is valid
    if(NULL == pnArray) return ERROR_ARRAY_INVALID;

    // check2 make sure uArrSize is not 0
    if(0 == uArrSize)   return ERROR_ARRAY_SIZE_INVALID;

    // check3 if iLeft, and iRight is valid
    if(uRight <= uLeft) return ERROR_INPUT_PARAM_INVLID;

    // check4 param uLeft, uRight is valid and within the boundary of uArrSize
    if(uLeft >= uArrSize || uRight >= uArrSize || uArrSize < uRight - uLeft + 1)
    {
        return ERROR_INPUT_PARAM_INVLID;
    }

    // (1) intialize i, index, and assigned pivot
    index = uLeft;
    pivot = pnArray[index];

    // (2) i go through the array, and swap with index if it is smaller than pivot
    for(i = uLeft + 1; i <= uRight; ++i)
    {
        if(pnArray[i] < pivot)
        {
            swap(&pnArray[i], &pnArray[++index]);
        }
    }

    // (3) swap the pivot (uLeft) with the index
    swap(&pnArray[index], &pnArray[uLeft]);
    return index;
}

/**
 * @public function quickSortRecursive
 * @abstract recursively quick sort an integer array
 * @param pnArray pointing to the integer array
 * @param uArraySize expected size of the array
 * @return
*/
void quickSortRecursive(int *pnArray, const unsigned int uArraySize)
{
    if(NULL == pnArray) return;

    if(0 == uArraySize) return;

    __quickSortRecursive(pnArray, uArraySize, 0, uArraySize - 1);
}

/**
 * @private function __quickSortRecursive
 * @abstract do the quick sort recursively with an integer array
 * @param pnArray pointing to the integer array
 * @param uArraySize expected size of the array
 * @param uLeft left side of the partition location, included left
 * @param uRight right side of the partition location, included right
 * @return
*/
void __quickSortRecursive(
    int *pnArray, const unsigned int uArraySize, unsigned int uLeft, unsigned int uRight)
{
    int iPartitionResult = 0;

    // check1, make sure array is valid
    if(NULL == pnArray) return;

    // check2 make sure uArrSize is not 0
    if(0 == uArraySize) return;

    // check3 if iLeft, and iRight is valid
    if(uRight <= uLeft) return;

    // check4 param uLeft, uRight is valid and within the boundary of uArrSize
    if(uLeft >= uArraySize || uRight >= uArraySize || uArraySize < uRight - uLeft + 1)
    {
        return;
    }

    // 2. parition and get the middle location
    iPartitionResult = partition(pnArray, uArraySize, uLeft, uRight);
    if(0 > iPartitionResult)
    {
        printf("%s ErrorCode:%d", FUNC_NAME_PARTITION, iPartitionResult);
        return;
    }

    // 3.1 recursively sort the left part
    __quickSortRecursive(pnArray, uArraySize, uLeft, iPartitionResult - 1);

    // 3.2 recursively sort the right part
    __quickSortRecursive(pnArray, uArraySize, iPartitionResult + 1, uRight);
}

/**
 * @public function quickSortIterative
 * @abstract iteratively quick sort an integer array
 * iStack's size should always either empty or 2's multiple number
 * example
 * iStack[1] = 0 (uLeft)
 * iStack[0] = uArrSize - 1 (uRight)
 *
 * @param pnArray pointing to the integer array
 * @param uArraySize expected size of the array
 * @return
*/
void quickSortIterative(int *pnArray, const unsigned int uArraySize)
{
    int iStackIndex = -1, iPartitionResult = 0;
    unsigned int uLeft = 0, uRight = 0;
    static int iStack[gSTACK_SIZE];

    // check1, make sure array is valid
    if(NULL == pnArray)     return;

    // check2 make sure uArrSize is not 0
    if(0 == uArraySize)     return;

    // (1) Initialize the uLeft, uRight, and put into the stack
    uLeft = 0;
    uRight = uArraySize - 1;
    iStack[++iStackIndex] = uRight;
    iStack[++iStackIndex] = uLeft;

    // (2) getting uLeft and uRight from the stack and keep partition until the stack empty
    while(0 < iStackIndex)
    {
        // (2.1) get uLeft, uRight from top of the stack
        uLeft = iStack[iStackIndex--];
        uRight = iStack[iStackIndex--];
        iPartitionResult = partition(pnArray, uArraySize, uLeft, uRight);

        if(0 > iPartitionResult)
        {
            printf("%s ErrorCode:%d", FUNC_NAME_PARTITION, iPartitionResult);
            return;
        }

        // (2.2) putting the uLeft, iPartitionIndex - 1
            // into the stack if it is valid range
        if(iPartitionResult > 0 && uLeft < iPartitionResult - 1)
        {
            iStack[++iStackIndex] = iPartitionResult - 1;
            iStack[++iStackIndex] = uLeft;
        }

        // (2.3) putting the iPartitionIndex + 1, uRight
            // into the stack if it is valid range
        if(uRight > iPartitionResult + 1)
        {
            iStack[++iStackIndex] = uRight;
            iStack[++iStackIndex] = iPartitionResult + 1;
        }
    }
}