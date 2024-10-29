#ifndef HEAPSORT_H
#define HEAPSORT_H

/**
 * @Description: recurisvely max heapify the array
 * @param pnArr, nArrSize
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 0) return
 * @param nIndex
 *  heapify the array starting from nIndex
 *  if(nIndex >= nArrSize) return
 * @return
 * @NOTE:
 * First Created on: 2024.10.29 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void maxHeapifyRecursive(int *pnArr, const int nArrSize, const int nIndex);

/**
 * @Description: iteratively max heapify the array
 * @param pnArr, nArrSize
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 0) return
 * @param nIndex
 *  heapify the array starting from nIndex
 *  if(nIndex >= nArrSize) return
 * @return
 * @NOTE:
 * First Created on: 2024.10.29 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void maxHeapifyIterative(int *pnArr, const int nArrSize, const int nIndex);

/**
 * @Description: build a maxHeap stucture from an unsorted array
 *  by calling maxHeapify from non-leaves node
 *
 * @param pnArr unsorted array
 * @param nArrSize the size of the array
 * @param bRecursive running recursively or iteratitve
 * @return
 * @NOTE:
 * First Created on: 2024.10.29 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void buildMaxHeap(int *pnArr, const int nArrSize, bool bRecursive);

/**
 * @Description: heap sort recursively the array with heap structure
 *  by putting the max element at the end of the array
 *  taking out the max, and maintaining the heap sturcture
 *
 * @param pnArr unsorted array
 * @param nArrSize the size of the array
 * @param bRecursive running recursively or iteratitve
 * @return
 * @NOTE:
 * First Created on: 2024.10.29 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void heapSortRecursive(int *pnArr, const int nArrSize);

/**
 * @Description: heap sort iteratively the array with heap structure
 *  by putting the max element at the end of the array
 *  taking out the max, and maintaining the heap sturcture
 *
 * @param pnArr unsorted array
 * @param nArrSize the size of the array
 * @param bRecursive running recursively or iteratitve
 * @return
 * @NOTE:
 * First Created on: 2024.10.29 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void heapSortIterative(int *pnArr, const int nArrSize);

#endif // HEAPSORT_H