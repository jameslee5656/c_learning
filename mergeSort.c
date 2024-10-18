#include "mergeSort.h"
#include "helper.h"

/**
 * @function merge
 * @abstract merge the left array and the right array,
 * left side would be left ~ mid, right side would be mid + 1 ~ right
 *
 * @param arr pointer pointing to the integer array
 * @param arrSize expected size of the array
 * @param left left side of the partition location, included left
 * @param mid mid index of the merge location, included left
 * @param right right side of the partition location, included right
 * @return partition location, if invalid inputs returning -1
 */
int merge(int* arr, const unsigned int uArrSize,
    unsigned int uLeft, unsigned int uMid, unsigned int uRight)
{
    static int mergeArr[gSTACK_SIZE];
    int i = 0, leftIndex = 0, rightIndex = 0;

    if(arr == NULL)
    {
        printf("%s\n", ERROR_ARRAY_INVALID);
        return -1;
    }

    // check the uLeft, uMid, uRight boundary is correct
    if(uRight <= uLeft || uMid < uLeft || uMid > uRight)
    {
        printf("%s, %s, uLeft:(%u), uMid:(%u), uRight:(%u)\n",
            FUNC_NAME_MERGE, ERROR_INPUT_INVALID, uLeft, uMid, uRight);
        return -1;
    }

    // check param uLeft, uMid, uRight is valid and within the boundary of uArrSize
    if(uLeft >= uArrSize || uMid >= uArrSize || uRight >= uArrSize
        || uArrSize < uRight - uLeft + 1)
    {
        printf("%s, %s, uArrSize:(%u) uLeft:(%u) uMid:(%u) uRight:(%u)\n",
            FUNC_NAME_MERGE, ERROR_INPUT_INVALID, uArrSize, uLeft, uMid, uRight);
        return -1;
    }

    for(i = 0, leftIndex = uLeft, rightIndex = uMid + 1; i < (uRight - uLeft + 1); ++i)
    {
        if(leftIndex > uMid)
        {
            memcpy(mergeArr + i, arr + rightIndex, sizeof(int) * (uRight - rightIndex + 1));
            break;
        }
        else if(rightIndex > uRight)
        {
            memcpy(mergeArr + i, arr + leftIndex, sizeof(int) * (uMid - leftIndex + 1));
            break;
        }
        else if(arr[leftIndex] <= arr[rightIndex])
        {
            mergeArr[i] = arr[leftIndex++];
        }
        else
        {
            mergeArr[i] = arr[rightIndex++];
        }
    }

    memcpy(arr + uLeft, mergeArr, sizeof(int) * (uRight - uLeft + 1));
    return 0;
}

/**
 * @private function __mergeSortRecursive
 * @abstract recursively being called by itself and mergeSortRecursive
 * to perform merge sort recursively
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @param uLeft left side of the merge location, included left
 * @param uRight right side of the merge location, included right
 * @return
 */
void __mergeSortRecursive(
    int *arr, const unsigned int uArrSize, unsigned int uLeft, unsigned int uRight)
{
    unsigned int uMid = 0;
    int result = 0;

    if(uLeft >= uRight)
        return;

    uMid = uLeft + (uRight - uLeft) / 2;
    __mergeSortRecursive(arr, uArrSize, uLeft, uMid);
    __mergeSortRecursive(arr, uArrSize, uMid + 1, uRight);

    result = merge(arr, uArrSize, uLeft, uMid, uRight);
    if(result == -1)
    {
        printf("%s, %s\n", ERROR_SORTTING_FAILED, SORT_TYPE_MERGESORT_RECURSIVE);
    }
}


/**
 * @public function mergeSortRecursive
 * @abstract to perform recursive merge sort on interger array arr
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
 */
void mergeSortRecursive(int *arr, const unsigned int uArrSize)
{
    if(uArrSize <= 0)
    {
        printf("%s %s, uArrSize:%u\n",
            ERROR_SORTTING_FAILED, SORT_TYPE_MERGESORT_RECURSIVE, uArrSize);
    }

    __mergeSortRecursive(arr, uArrSize, 0, uArrSize - 1);
}

/**
 * @public function mergeSortIterative
 * @abstract to perform iterative merge sort on interger array
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
 */
void mergeSortIterative(int *arr, const unsigned int uArrSize)
{
    unsigned uCurSize = 0, uLeft = 0, uMid = 0, uRight = 0;

    for(uCurSize = 1; uCurSize < uArrSize; uCurSize *= 2)
    {
        for(uLeft = 0; uLeft + uCurSize < uArrSize; uLeft += uCurSize * 2)
        {
            uMid = uLeft + uCurSize - 1;
            uRight = min(uLeft + uCurSize * 2 - 1, uArrSize - 1);

            merge(arr, uArrSize, uLeft, uMid, uRight);
        }
    }
}