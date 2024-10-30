#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "definitions.h"
#include "radixSort.h"

#include "helper.h"

/**
 * @Description: radix sort pnArr iteratively
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 1) return
 * @param nCurIndex:
 *  the current Index that we want to insert into the array
 * @return
 * @bug FIX:
 * @NOTE:
 * Need to consider the negative one
 * First Created on: 2024.10.30 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void radixSortIterative(int *pnArr, const int nArrSize)
{
    static int nRadixBucket[10];
    static int anTemp[gRANDOM_ARRAY_SIZE];
    int i = 0;
    int nRadixIndex = 0;
    int nMaxVal = 0;
    int nMinVal = 0;
    int nExp10 = 1;
    int nMod = 0;
    int negMult = 1;

    if(NULL == pnArr)   return;
    if(1 >= nArrSize)   return;

    nExp10 = 1;
    memset(anTemp, 0, (unsigned)nArrSize * sizeof(int));

    nMaxVal = pnArr[0];
    // nMinVal = pnArr[0];
    for(i = 1; i < nArrSize; ++i)
    {
        if(pnArr[i] > nMaxVal)
        {
            nMaxVal = pnArr[i];
        }
    }

    // nMinVal *= nMinVal < 0 ? -1 : 1;
    // if(nMinVal > nMaxVal) nMaxVal = nMinVal;
    // printArray(pnArr, nArrSize);

    while(nMaxVal / nExp10 > 0)
    {
        // round intialization
        memset(nRadixBucket, 0, 10 * sizeof(int));

        for(i = 0; i < nArrSize; ++i)
        {
            negMult = pnArr[i] < 0 ? -1 : 1;
            nMod = pnArr[i] * negMult / nExp10 % 10;
            ++nRadixBucket[nMod];
        }

        for(i = 1; i < 10; ++i)
        {
            nRadixBucket[i] += nRadixBucket[i - 1];
        }
        printArray(nRadixBucket, 10);

        for(i = nArrSize - 1; i >= 0; --i)
        {
            negMult = pnArr[i] < 0 ? -1 : 1;
            nMod = (pnArr[i] / nExp10) * negMult % 10;
            // printf("%d %d %d\n", pnArr[i], nMod, nRadixIndex);
            anTemp[--nRadixBucket[nMod]] = pnArr[i];
        }

        memcpy(pnArr, anTemp, (unsigned)nArrSize * sizeof(int));
        printArray(pnArr, nArrSize);
        nExp10 *= 10;
    }
    printArray(pnArr, nArrSize);
}