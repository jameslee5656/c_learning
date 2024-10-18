#ifndef MERGESORT_H
#define MERGESORT_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#include "definitions.h"

////////////////////
// Merge Sort
////////////////////
/**
 * @function merge
 * @abstract merge the left array and the right array,
 * left side would be left ~ mid, right side would be mid + 1 ~ right
 * by using two pointer technique and merge the smallest number onto the additional space.
 * At last memcopy back to arr.
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @param uLeft left side of the merge location, included left
 * @param uMid mid index of the merge location uMid is the end of the left part
 * uMid + 1 is the start of the right part
 * @param uRight right side of the merge location, included right
 * @return if invalid inputs returning -1, return 0 if merged successfully;
 */
int merge(int* arr, const unsigned int uArrSize,
    unsigned int uLeft, unsigned int uMid, unsigned int uRight);

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
    int *arr, const unsigned int uArrSize, unsigned int uLeft, unsigned int uRight);

/**
 * @public function mergeSortRecursive
 * @abstract to perform recursive merge sort on interger array
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
 */
void mergeSortRecursive(int *arr, const unsigned int uArrSize);

/**
 * @public function mergeSortIterative
 * @abstract to perform iterative merge sort on interger array
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
 */
void mergeSortIterative(int *arr, const unsigned int uArrSize);

#endif // MERGESORT_H