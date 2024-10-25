#ifndef QSORT_H
#define QSORT_H

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
 * return index;
 */
int partition(int *pnArray, const unsigned int uArraySize,
    unsigned int uLeft, unsigned int uRight);

/**
 * @private function __quickSortRecursive
 * @abstract do the quick sort recursively with an integer array
 * @param pnArray pointing to the integer array
 * @param uArraySize expected size of the array
 * @param uLeft left side of the partition location, included left
 * @param uRight right side of the partition location, included right
 * @return
*/
void __quickSortRecursive(int *pnArray, const unsigned int uArraySize,
    unsigned int uLeft, unsigned int uRight);

/**
 * @public function quickSortRecursive
 * @abstract recursively quick sort an integer array
 * @param pnArray pointing to the integer array
 * @param uArraySize expected size of the array
 * @return
*/
void quickSortRecursive(int *pnArray, const unsigned int uArraySize);

/**
 * @public function quickSortIterative
 * @abstract iteratively quick sort an integer array
 * iStack's size should always either be 0 or 2's multiple number
 * example
 * iStack[1] = uArrSize - 1 (uRight)
 * iStack[0] = 0 (uLeft)
 * @param pnArray pointing to the integer array
 * @param uArraySize expected size of the array
 * @return
*/
void quickSortIterative(int *pnArray, const unsigned int uArraySize);

#endif // QSORT_H