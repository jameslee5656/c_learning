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

    // check1 if array is valid
    // check2 if iLeft, and iRight is valid

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