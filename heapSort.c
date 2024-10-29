#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "heapSort.h"
#include "definitions.h"
#include "helper.h"

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
void maxHeapifyRecursive(int *pnArr, const int nArrSize, const int nIndex)
{
    int nMaxIndex = 0, nMaxValue = 0;
    int nLeftIndex = 0, nRightIndex = 0;

    if(NULL == pnArr)       return;
    if(0 >= nArrSize)       return;
    // 1. Ends the recursive call if nIndex reach the end of the array
    if(nArrSize <= nIndex)  return;

    // 2.1 find the max comparing with nIndex, leftChild, rightChild;
    nMaxIndex = nIndex;
    nMaxValue = pnArr[nIndex];
    nLeftIndex = nIndex * 2 + 1;
    nRightIndex = nIndex * 2 + 2;

    if(nLeftIndex < nArrSize && pnArr[nLeftIndex] > nMaxValue)
    {
        nMaxIndex = nLeftIndex;
        nMaxValue = pnArr[nLeftIndex];
    }

    if(nRightIndex < nArrSize && pnArr[nRightIndex] > nMaxValue)
    {
        nMaxIndex = nRightIndex;
        nMaxValue = pnArr[nRightIndex];
    }

    // 2.2 if the nMaxIndex != nIndex, we should swap and heapify that subtree
    if(nIndex != nMaxIndex)
    {
        swap(&pnArr[nIndex], &pnArr[nMaxIndex]);
        maxHeapifyRecursive(pnArr, nArrSize, nMaxIndex);
    }
}

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
void maxHeapifyIterative(int *pnArr, const int nArrSize, const int nIndex)
{
    // static int naStack[gSTACK_SIZE];
    // int nStackIndex = -1;
    int i = 0;
    int val = 0;
    int nLeftIndex = 0, nRightIndex = 0;
    int nMaxIndex = 0, nMaxValue = 0;

    if(NULL == pnArr)       return;
    if(0 >= nArrSize)       return;
    if(nArrSize <= nIndex)  return;

    // 1. initialize i
    for(i = nIndex; i < nArrSize;)
    {
        // 2. find out if the i has the max value compare with it's child
        nMaxValue = pnArr[i];
        nMaxIndex = i;

        nLeftIndex = i * 2 + 1;
        nRightIndex = i * 2 + 2;

        if(nArrSize > nLeftIndex && pnArr[nLeftIndex] > nMaxValue)
        {
            nMaxIndex = nLeftIndex;
            nMaxValue = pnArr[nLeftIndex];
        }

        if(nArrSize > nRightIndex && pnArr[nRightIndex] > nMaxValue)
        {
            nMaxIndex = nRightIndex;
            nMaxValue = pnArr[nRightIndex];
        }

        // 3.1 if i is not the max value compare with it's child
            // swap the value and let i be the nMaxIndex
        if(i != nMaxIndex)
        {
            swap(&pnArr[i], &pnArr[nMaxIndex]);
            i = nMaxIndex;
        }
        // 3.2 otherwise end the loop
        else
        {
            break;
        }
    }
}

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
void buildHeap(int *pnArr, const int nArrSize, bool bRecursive)
{
    int i = 0;

    if(NULL == pnArr)       return;
    if(0 >= nArrSize)       return;

    // from n / 2 - 1 (non-leaves) index and start heapify each element
    for(i = nArrSize / 2 - 1; i >= 0; --i)
    {
        if(bRecursive)
        {
            maxHeapifyRecursive(pnArr, nArrSize, i);
        }
        else
        {
            maxHeapifyIterative(pnArr, nArrSize, i);
        }
    }
}

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
void heapSortRecursive(int *pnArr, const int nArrSize)
{
    int nHeapSize = 0;

    // 1. build the heap sturcture first
    buildHeap(pnArr, nArrSize, true);

    for(nHeapSize = nArrSize; nHeapSize > 1; --nHeapSize)
    {
        // 2. swap the max value (because of the maxHeap structure), it must be pnArr[0]
            // with the last of it's element
        swap(&pnArr[0], &pnArr[nHeapSize - 1]);

        // 3. maxHeapify the first element with less one element
        maxHeapifyRecursive(pnArr, nHeapSize - 1, 0);
    }
}

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
void heapSortIterative(int *pnArr, const int nArrSize)
{
    int nHeapSize = 0;

    // 1. build the heap sturcture first
    buildHeap(pnArr, nArrSize, true);

    for(nHeapSize = nArrSize; nHeapSize > 1; --nHeapSize)
    {
        // 2. swap the max value (because of the maxHeap structure), it must be pnArr[0]
            // with the last of it's element
        swap(&pnArr[0], &pnArr[nHeapSize - 1]);

        // 3. maxHeapify the first element with less one element
        maxHeapifyIterative(pnArr, nHeapSize - 1, 0);
    }
}