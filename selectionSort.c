#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include "selectionSort.h"

/**
 * @Description: public function to do selection sort recursively,
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 1) return
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.30 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void selectionSortRecursive(int *pnArr, const int nArrSize)
{
    if(NULL == pnArr)   return;
    if(1 >= nArrSize)   return;

    __selectionSortRecursive(pnArr, nArrSize, 0);
}

/**
 * @Description: private function to do selection sort recursively,
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 1) return
 * @param nUnsortedFirst:
 *  the first index that is in the unsorted area
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.30 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void __selectionSortRecursive(int *pnArr, const int nArrSize, const int nUnsortedFirst)
{
    int nIndex = 0;
    int nMinIndex = 0, nMinVal = 0;

    if(NULL == pnArr)   return;
    if(1 >= nArrSize)   return;

    // Ending condition
    if(nUnsortedFirst >= nArrSize)  return;

    nMinIndex = nUnsortedFirst;
    nMinVal = pnArr[nUnsortedFirst];
    for(nIndex = nUnsortedFirst; nIndex < nArrSize; ++nIndex)
    {
        if(nMinVal > pnArr[nIndex])
        {
            nMinIndex = nIndex;
            nMinVal = pnArr[nIndex];
        }
    }
    swap(&pnArr[nMinIndex], &pnArr[nUnsortedFirst]);

    __selectionSortRecursive(pnArr, nArrSize, nUnsortedFirst + 1);
}

/**
 * @Description: selection sort pnArr iteratively
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 1) return
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.30 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void selectionSortIterative(int *pnArr, const int nArrSize)
{
    int nUnsortedFirst = 0, nIndex = 0;
    int nMinIndex = 0;
    int nMinVal = 0;

    if(NULL == pnArr)   return;
    if(1 >= nArrSize)   return;

    // 1. divided the array into sorted and unsorted area
        // using a nUnSortedFirst to point to the first position of the unsorted area
    for(nUnsortedFirst = 0; nUnsortedFirst < nArrSize - 1; ++nUnsortedFirst)
    {
        nMinIndex = nUnsortedFirst;
        nMinVal = pnArr[nUnsortedFirst];

        // 2.1 find the minimal index in the unsorted area
        for(nIndex = nUnsortedFirst + 1; nIndex < nArrSize; ++nIndex)
        {
            if(pnArr[nIndex] < nMinVal)
            {
                nMinIndex = nIndex;
                nMinVal = pnArr[nIndex];
            }
        }

        // 2.2 swap with the minmal and the nUnsortedFirst
        swap(&pnArr[nMinIndex], &pnArr[nUnsortedFirst]);
    }
}