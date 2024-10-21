#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#include "helper.h"

////////////////////
// heap Sort
////////////////////
// implementing a max-heap ADT to complete the sort

/**
 * @function maxHeapifyRecursive
 * @abstract the basic routine for heap sort,
 *           heapify the maxHeap at uIndex recursively
 * ! uIndex is 0-based
 *
 * @param maxHeap pointer pointing to the heap
 * @param uHeapSize how many element that are in the current heap
 * @param uIndex the index location to do the heapify operation
 * @return if invalid inputs returning -1, return 0 if merged successfully
 */
int maxHeapifyRecursive(
    int* maxHeap, const unsigned int uArrSize, const unsigned int uIndex);

/**
 * @function maxHeapifyIterative
 * @abstract the basic routine for heap sort,
 *           heapify the maxHeap at uIndex iteratively
 * ! uIndex is 0-based
 *
 * @param maxHeap pointer pointing to the heap
 * @param uHeapSize how many element that are in the current heap
 * @param uIndex the index location to do the heapify operation
 * @return if invalid inputs returning -1, return 0 if merged successfully;
 */
int maxHeapifyIterative(
    int* maxHeap, const unsigned int uArrSize, const unsigned int uIndex);

/**
 * @function buildHeap
 * @abstract build a maxHeap stucture from an unsorted array
 *
 * @param arr unsorted array
 * @param uArrSize the size of the array
 * @param bRecursive running recursively (or false, run iteratively)
 * @return
 */
void buildHeap(int* arr, const unsigned int uArrSize, bool bRecursive);

/**
 * @function heapSort
 * @abstract to perform heap sort on interger array
 *
 * @param arr pointer pointing to the integer array
 * @param uArrSize expected size of the array
 * @param bRecursive whether to run recursively (or false, run iteratively)
 * @return
 */
void heapSort(int* arr, const unsigned int uArrSize, bool bRecursive);

#endif // HEAPSORT_H