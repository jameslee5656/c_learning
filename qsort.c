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
 * 3, 1, 4, 2, 5
 * (2.2) arr[i] is smaller than pivot, do a swap with ++index
 * 3, 1, 4, 2, 5
 *    ^---index
 *          ^---i
 * 3, 1, 2, 4, 5
 *       ^---index
 *
 * (3) swap the uLeft with the index
 * 2, 1, 3, 4, 5
 *       ^---index
 * return index;
 */
int partition(int *arr, const unsigned int uArrSize,
    unsigned int uLeft, unsigned int uRight)
{
    int i = 0;
    unsigned int index = 0;
    int pivot = 0;

    // check1, make sure array is valid
    if(arr == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return -1;
    }

    // check2 make sure uArrSize is not 0
    if(uArrSize == 0)
    {
        printf("%s, %s, %s, uArrSize:(%u)\n", FUNC_NAME_PARTITION, ERROR_INPUT_INVALID,
            ERROR_DETAIL_INVALID_ARRAY_SIZE, uArrSize);
        return -1;
    }

    // check3 if iLeft, and iRight is valid
    if(uRight <= uLeft)
    {
        printf("%s, %s, uLeft:(%u), uRight:(%u)\n",
            FUNC_NAME_PARTITION, ERROR_INPUT_INVALID, uLeft, uRight);
        return -1;
    }

    // check4 param uLeft, uRight is valid and within the boundary of uArrSize
    if(uLeft >= uArrSize || uRight >= uArrSize || uArrSize < uRight - uLeft + 1)
    {
        printf("%s, %s, uArrSize:(%u) uLeft:(%u) uRight:(%u)\n",
            FUNC_NAME_PARTITION, ERROR_INPUT_INVALID, uArrSize, uLeft, uRight);
        return -1;
    }

    // (1) intialize i, index, and assigned pivot
    index = uLeft;
    pivot = arr[index];

    // (2) i go through the array, and swap with index if it is smaller than pivot
    for(i = uLeft + 1; i <= uRight; ++i)
    {
        if(arr[i] < pivot)
        {
            swap(&arr[i], &arr[++index]);
        }
    }

    // (3) swap the uLeft with the index
    swap(&arr[index], &arr[uLeft]);
    return index;
}

/**
 * @public function quickSortRecursive
 * @abstract recursively quick sort an integer array
 * @param arr pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
*/
void quickSortRecursive(int* arr, const unsigned int uArrSize)
{
    if(arr == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return;
    }

    if(uArrSize == 0)
    {
        printf("%s, %s, %s, uArrSize:(%u)\n", SORT_TYPE_QUICKSORT_RECURSIVE,
            ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_ARRAY_SIZE, uArrSize);
        return;
    }

    __quickSortRecursive(arr, uArrSize, 0, uArrSize - 1);
}

/**
 * @private function __quickSortRecursive
 * @abstract do the quick sort recursively with an integer array
 * @param arr pointing to the integer array
 * @param uArrSize expected size of the array
 * @param uLeft left side of the partition location, included left
 * @param uRight right side of the partition location, included right
 * @return
*/
void __quickSortRecursive(
    int* arr, const unsigned int uArrSize, unsigned int uLeft, unsigned int uRight)
{
    int index = 0;

    // check1, make sure array is valid
    if(arr == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return;
    }

    // check2 make sure uArrSize is not 0
    if(uArrSize == 0)
    {
        printf("%s, %s, %s, uArrSize:(%u)\n", SORT_TYPE_QUICKSORT_RECURSIVE, ERROR_INPUT_INVALID,
            ERROR_DETAIL_INVALID_ARRAY_SIZE, uArrSize);
        return;
    }

    // check3 if iLeft, and iRight is valid
    if(uRight <= uLeft)
    {
        printf("%s, %s, uLeft:(%u), uRight:(%u)\n",
            SORT_TYPE_QUICKSORT_RECURSIVE, ERROR_INPUT_INVALID, uLeft, uRight);
        return;
    }

    // check4 param uLeft, uRight is valid and within the boundary of uArrSize
    if(uLeft >= uArrSize || uRight >= uArrSize || uArrSize < uRight - uLeft + 1)
    {
        printf("%s, %s, uArrSize:(%u) uLeft:(%u) uRight:(%u)\n",
            SORT_TYPE_QUICKSORT_RECURSIVE, ERROR_INPUT_INVALID, uArrSize, uLeft, uRight);
        return;
    }

    // 2. parition and get the middle one (sorted location)
    index = partition(arr, uArrSize, uLeft, uRight);
    if (index == -1)
    {
        printf("%s %s", SORT_TYPE_QUICKSORT_RECURSIVE, ERROR_SORTTING_FAILED);
    }

    // 3.1 recursively sort the left part
    if(index > 0 && uLeft < index - 1)
    {
        __quickSortRecursive(arr, uArrSize, uLeft, index - 1);
    }

    // 3.2 recursively sort the right part
    if (uRight > index + 1)
    {
        __quickSortRecursive(arr, uArrSize, index + 1, uRight);
    }
}

/**
 * @public function quickSortIterative
 * @abstract iteratively quick sort an integer array
 * iStack's size should always either empty or 2's multiple number
 * example
 * iStack[1] = o (uLeft)
 * iStack[0] = uArrSize - 1 (uRight)
 * @param arr pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
*/
void quickSortIterative(int *arr, const unsigned int uArrSize)
{
    static int iStack[gSTACK_SIZE];
    int iStackIndex = -1, iPartitionIndex;
    unsigned int uLeft = 0, uRight = 0;

    // check1, make sure array is valid
    if(arr == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return;
    }

    // check2 make sure uArrSize is not 0
    if(uArrSize <= 1)
    {
        printf("%s, %s, %s, uArrSize:(%u)\n", FUNC_NAME_PARTITION, ERROR_INPUT_INVALID,
            ERROR_DETAIL_INVALID_ARRAY_SIZE, uArrSize);
        return;
    }

    // (1) Initialize the uLeft, uRight, and put into the stack
    uLeft = 0;
    uRight = uArrSize - 1;
    iStack[++iStackIndex] = uRight;
    iStack[++iStackIndex] = uLeft;

    // (2) getting uLeft and uRight from the stack and keep partition until the stack empty
    while(iStackIndex > 0)
    {
        // (2.1) get uLeft, uRight from top of the stack
        uLeft = iStack[iStackIndex--];
        uRight = iStack[iStackIndex--];
        iPartitionIndex = partition(arr, uArrSize, uLeft, uRight);

        if(iPartitionIndex == -1)
        {
            return;
        }

        // (2.2) putting the uLeft, iPartitionIndex - 1
            // into the stack if it is valid range
        if(iPartitionIndex > 0 && uLeft < iPartitionIndex - 1)
        {
            iStack[++iStackIndex] = iPartitionIndex - 1;
            iStack[++iStackIndex] = uLeft;
        }

        // (2.3) putting the iPartitionIndex + 1, uRight
            // into the stack if it is valid range
        if(uRight > iPartitionIndex + 1)
        {
            iStack[++iStackIndex] = uRight;
            iStack[++iStackIndex] = iPartitionIndex + 1;
        }
    }
}