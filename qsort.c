#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#include "qsort.h"
#include "definitions.h"
#include "helper.h"

//////////////////
// Quick Sort
//////////////////
/**
 * @function parition
 * @abstract parition the array from with the left being pivot,
 *  returning the partition location
 *  or returning left if invalid location
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @param uLeft left side of the partition location, included left
 * @param uRight right side of the partition location, included right
 * @return partition location, if invalid inputs returning left
 */
int partition(int* arr, const unsigned int uArrSize, unsigned int uLeft, unsigned int uRight)
{
    int index = 0, i = 0;
    int pivot = 0;

    if(arr == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return -1;
    }

    if(uArrSize <= 0)
    {
        printf("%s, %s, %s\n",
            FUNC_NAME_PARTITION, ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_ARRAY_SIZE);
        return -1;
    }

    // check param uLeft is valid
    if(uLeft >= uArrSize || uLeft < 0)
    {
        printf("%s, %s, %s(%d)\n",
            FUNC_NAME_PARTITION, ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_ULEFT, uLeft);
        return -1;
    }

    // check param uRight is valid
    if(uRight >= uArrSize || uRight < 0)
    {
        printf("%s, %s, %s(%d)\n",
            FUNC_NAME_PARTITION, ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_URIGHT, uRight);
        return -1;
    }

    // check uArrSize is longer than uLeft ~ uRight
    if(uArrSize < uRight - uLeft + 1)
    {
        printf("%s, %s, %s(%d, %d)\n",
            FUNC_NAME_PARTITION, ERROR_INPUT_INVALID, ERROR_DETAIL_LEFT_RIGHT_LARGER_ARR_SIZE,
                uLeft, uRight);
        return -1;
    }

    // check the uLeft and uRight boundary is correct
    if(uRight <= uLeft)
    {
        printf("%s, %s, uLeft(%d) <= uRight(%d)\n",
            FUNC_NAME_PARTITION, ERROR_INPUT_INVALID, uLeft, uRight);
        return -1;
    }

    index = uLeft;
    pivot = arr[uLeft];

    for(i = uLeft + 1; i <= uRight; ++i)
    {
        if(arr[i] < pivot)
        {
            swap(&arr[++index], &arr[i]);
        }
    }
    swap(&arr[uLeft], &arr[index]);
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

    if(uArrSize <= 0)
    {
        printf("%s, %s, %s\n",
            SORT_TYPE_QUICKSORT_RECURSIVE, ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_ARRAY_SIZE);
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

    if(arr == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return;
    }

    if(uArrSize <= 0)
    {
        printf("%s, %s, %s\n",
            SORT_TYPE_QUICKSORT_RECURSIVE, ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_ARRAY_SIZE);
        return;
    }

    // check param uLeft is valid
    if(uLeft >= uArrSize || uLeft < 0)
    {
        printf("%s, %s, (%d)\n", ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_ULEFT, uLeft);
        return;
    }

    // check param uRight is valid
    if(uRight >= uArrSize || uRight < 0)
    {
        printf("%s, %s %d\n", ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_URIGHT, uRight);
        return;
    }

    // check uArrSize is longer than end ~ start
    if(uArrSize < uRight - uLeft + 1)
    {
        printf("%s, %s\n", ERROR_INPUT_INVALID, ERROR_DETAIL_LEFT_RIGHT_LARGER_ARR_SIZE);
        return;
    }

    // check the uLeft and right boundary is correct
    if(uRight <= uLeft)
    {
        printf("%s, uLeft(%d) <= uRight(%d)\n", ERROR_INPUT_INVALID, uLeft, uRight);
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
 * @function quickSortIterative
 * @abstract do the quick sort iteratively with an integer array
 * @param arr pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
*/
void quickSortIterative(int* arr, const unsigned int uArrSize)
{
    // iStack store (left, right) at one time
    int iStack[uArrSize];
    int left = 0, right = 0;
    int iStackIndex = -1, index = 0;

    if(arr == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return;
    }


    if(uArrSize <= 0)
    {
        printf("%s, %s, %s\n",
            SORT_TYPE_QUICKSORT_ITERATIVE, ERROR_INPUT_INVALID, ERROR_DETAIL_INVALID_ARRAY_SIZE);
        return;
    }

    // push the left and right boundary to the stack
    iStack[++iStackIndex] = 0;
    iStack[++iStackIndex] = uArrSize - 1;

    while(iStackIndex >= 0)
    {
        right = iStack[iStackIndex--];
        left = iStack[iStackIndex--];
        index = partition(arr, uArrSize, left, right);

        // making sure that the left side of the partition still has number
        if(index > 0 && index - 1 > left)
        {
            iStack[++iStackIndex] = left;
            iStack[++iStackIndex] = index - 1;
        }

        // making sure that the right side of the partition still has number
        if(index + 1 < right)
        {
            iStack[++iStackIndex] = index + 1;
            iStack[++iStackIndex] = right;
        }
    }
}

