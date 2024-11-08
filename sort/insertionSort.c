#include <stdlib.h>
#include <stdio.h>

#include "helper.h"
#include "insertionSort.h"

/**
 * @Description: public function to do insertion sort recursively,
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
void insertionSortRecursive(int *pnArr, const int nArrSize)
{
    if(NULL == pnArr)   return;
    if(1 >= nArrSize)   return;

    __insertionSortRecursive(pnArr, nArrSize, 1);
}

/**
 * @Description: private function to do insertion sort recursively,
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 1) return
 * @param nCurIndex:
 *  the current Index that we want to insert into the array
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.30 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void __insertionSortRecursive(int *pnArr, int nArrSize, int nCurIndex)
{
    int i = 0;
    int nCmpIndex = 0;

    if(NULL == pnArr)   return;
    if(1 >= nArrSize)   return;

    // 1. if curIndex >= nArrSize is the ending condition
    if(nCurIndex >= nArrSize)   return;

    // 2. Insert the nCurIndex into the correct position comparing with 0 ~ nCurIndex - 1
        // for i = nCurIndex - 1 ~ 0, if the index value is smaller than the i
        // we do a swap with it and assign index to i, otherwise break the for loop
    nCmpIndex = nCurIndex;
    for(i = nCurIndex - 1; i >= 0; --i)
    {
        if(pnArr[nCmpIndex] < pnArr[i])
        {
            swap(&pnArr[nCmpIndex], &pnArr[i]);
            nCmpIndex = i;
        }
        else
        {
            break;
        }
    }

    // 3. Recursively calls insertionSort for the next index
    __insertionSortRecursive(pnArr, nArrSize, nCurIndex + 1);
}

/**
 * @Description: insertion sort pnArr iteratively,
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 1) return
 * @param nCurIndex:
 *  the current Index that we want to insert into the array
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.30 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void insertionSortIterative(int *pnArr, const int nArrSize)
{
    int i = 0, j = 0, nCmpIndex = 0;

    if(NULL == pnArr) return;
    if(1 >= nArrSize) return;

    // 1. for i = 1 ~ nArrSize - 1
    for(i = 1; i < nArrSize; ++i)
    {
        // 2. Insert the pnArr[i] into the correct position comparing with 0 ~ i - 1
        nCmpIndex = i;

        for(j = i - 1; j >= 0; --j)
        {
            // 2.1 if pnArr[nIndex] < pnArr[j], swap(&pnArr[nIndex], &pnArr[j]);
                // nIndex = j;
            if(pnArr[nCmpIndex] < pnArr[j])
            {
                swap(&pnArr[nCmpIndex], &pnArr[j]);
                nCmpIndex = j;
            }
            // 2.2 otherwise break the for loop
            else
            {
                break;
            }
        }
    }
}