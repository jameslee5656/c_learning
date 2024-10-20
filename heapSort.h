#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#include "helper.h"
#include "definitions.h"

////////////////////
// heap Sort
////////////////////
// implementing a min-heap ADT to complete the sort

/**
 * @function max heapify
 * @abstract the basic routine for heap sort, heapify the arr
 *
 * @param heap pointer pointing to the heap
 * @param uHeapSize how many element that are in the current heap
 * @return if invalid inputs returning -1, return 0 if merged successfully;
 */
int minHeapify(int* minHeap, const unsigned int uHeapSize, const unsigned int uIndex);

void buildHeap(int* arr, const unsigned int uArrSize);


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
// void __mergeSortRecursive(
    // int *arr, const unsigned int uArrSize, unsigned int uLeft, unsigned int uRight);

/**
 * @public function mergeSortRecursive
 * @abstract to perform recursive merge sort on interger array
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
 */
// void heapSortRecursive(int *arr, const unsigned int uArrSize);
// void mergeSortRecursive(int *arr, const unsigned int uArrSize);

/**
 * @public function mergeSortIterative
 * @abstract to perform iterative merge sort on interger array
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @return
 */
// void mergeSortIterative(int *arr, const unsigned int uArrSize);

#endif // HEAPSORT_H