#ifndef QSORT_H
#define QSORT_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @function parition
 * @abstract parition the array from with the left being pivot,
 *  returning the partition location
 *  or returning left if invalid location
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @param uLeft left side of the partition location, included left
 * @param uRight right side of the partition location, included right
 * @return partition location, if invalid inputs returns -1
 */
int partition(int* arr, const unsigned int uArrSize, unsigned int uLeft, unsigned int uRight);

/**
 * @private function __quickSortRecursive
 * @abstract do the quick sort recursively with an integer array
 * @param arr pointing to the integer array
 * @param uArrSize expected size of the array
 * @param uLeft left side of the partition location, included left
 * @param uRight right side of the partition location, included right
 * @return
*/
void __quickSortRecursive(int* arr, const unsigned int uArrSize,
    unsigned int uLeft, unsigned int uRight);

/**
 * @public function quickSortRecursive
 * @abstract recursively quick sort an integer array
 * @param arr pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
*/
void quickSortRecursive(int* arr, const unsigned int uArrSize);

/**
 * @function quickSortIterative
 * @abstract do the quick sort iteratively with an integer array
 * @param arr pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
*/
void quickSortIterative(int *arr, const unsigned int uArrSize);

#endif // QSORT_H