#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "definitions.h"
#include "radixSort.h"

#include "helper.h"

/**
 * @Description: public function to do radix sort recursively,
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 1) return
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.31 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void radixSortRecursive(int *pnArr, const int nArrSize)
{
    int i = 0;
    int nMaxVal = 0, nMinVal = 0;
    int nShiftVal = 0;

    if(NULL == pnArr)   return;
    if(1 >= nArrSize)   return;

    // 1. find the max, min value of the pnArr and decide how much is the shift value
    nMaxVal = pnArr[0];
    nMinVal = pnArr[0];
    for(i = 1; i < nArrSize; ++i)
    {
        if(nMaxVal < pnArr[i])
        {
            nMaxVal = pnArr[i];
        }

        if(nMinVal > pnArr[i])
        {
            nMinVal = pnArr[i];
        }
    }

    if(nMaxVal > gRANDOM_UPPER_LIMIT)
    {
        printf("%s %s %s\n", ERROR_SORTTING_FAILED, SORT_TYPE_RADIXSORT_ITERATIVE, ERROR_MAX_VAL_OVER_LIMIT);
        return;
    }

    if(nMinVal < 0)
    {
        nShiftVal = -1 * nMinVal;
        for(i = 0; i < nArrSize; ++i)
        {
            pnArr[i] += nShiftVal;
        }

        __radixSortRecursive(pnArr, nArrSize, nMaxVal + nShiftVal, 1);

        for(i = 0; i < nArrSize; ++i)
        {
            pnArr[i] -= nShiftVal;
        }

        return;
    }

    __radixSortRecursive(pnArr, nArrSize, nMaxVal, 1);

    return;
}

/**
 * @Description: private function to do selection sort recursively,
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return
 *  if(nArrSize <= 1) return
 * @param nCurIndex:
 *  nMaxVal the max value in the array
 *  nCurExp10 current 10 folded value, we divide this value to sort each number
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.31 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void __radixSortRecursive(int *pnArr, const int nArrSize, const int nMaxVal, const int nCurExp10)
{
    int i = 0, nMod = 0;
    static int nRadixBucket[10];
    static int anTemp[gRANDOM_ARRAY_SIZE];

    if(NULL == pnArr)   return;
    if(1 >= nArrSize)   return;

    // 2. Ending condition: nCurExp10 > nMaxVal
    if(nCurExp10 > nMaxVal) return;

    memset(nRadixBucket, 0, 10 * sizeof(int));

    // 3.1 Count the mod of pnArr[i] / nCurExp10 and put in the nRadixBucket
    for(i = 0; i < nArrSize; ++i)
    {
        nMod = pnArr[i] / nCurExp10 % 10;
        ++nRadixBucket[nMod];
    }

    // 3.2 Cumulate the value of nRadixBucket so we can have the prefix of the position where the mod is
    for(i = 1; i < 10; ++i)
    {
        nRadixBucket[i] += nRadixBucket[i - 1];
    }

    // 4. From the largest mod, put each element into a temp array corresponding to it's mod value,
        // and decrease the value of nRadixBucket[mod]
    for(i = nArrSize - 1; i >= 0; --i)
    {
        nMod = pnArr[i] / nCurExp10 % 10;
        anTemp[--nRadixBucket[nMod]] = pnArr[i];
    }

    memcpy(pnArr, anTemp, nArrSize * sizeof(int));

    // 5. Recursively call for ten folding nCurExp10
    __radixSortRecursive(pnArr, nArrSize, nMaxVal, nCurExp10 * 10);
}

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
    int nShiftVal = 0;

    if(NULL == pnArr)   return;
    if(1 >= nArrSize)   return;

    nExp10 = 1;
    memset(anTemp, 0, (unsigned)nArrSize * sizeof(int));

    // 1. find the min and the max value in the array
        // if max value is > gRANDOM_UPPER_LIMIT return
        // nShiftVal = min(0, 0 - min value);
    nMaxVal = pnArr[0];
    nMinVal = pnArr[0];
    for(i = 1; i < nArrSize; ++i)
    {
        if(nMaxVal < pnArr[i])
        {
            nMaxVal = pnArr[i];
        }

        if(nMinVal > pnArr[i])
        {
            nMinVal = pnArr[i];
        }
    }

    if(nMaxVal > gRANDOM_UPPER_LIMIT)
    {
        printf("%s %s %s\n", ERROR_SORTTING_FAILED, SORT_TYPE_RADIXSORT_ITERATIVE, ERROR_MAX_VAL_OVER_LIMIT);
        return;
    }

    nShiftVal = 0;
    if(nMinVal < 0)
    {
        nShiftVal = -1 * nMinVal;
        for(i = 0; i < nArrSize; ++i)
        {
            pnArr[i] += nShiftVal;
        }
        nMaxVal += nShiftVal;
    }

    // Normal radix sort procedure
    // 2. while nExp10 > 0, keep radix sorting
    while(nMaxVal / nExp10 > 0)
    {
        // 3. clear the radixBucket
        memset(nRadixBucket, 0, 10 * sizeof(int));

        // 4.1 for all element of pnArr, pnArr[i], count the counts of pnArr[i] / nExp10 % 10
            // put it in radixBucket
        for(i = 0; i < nArrSize; ++i)
        {
            nMod = pnArr[i] / nExp10 % 10;
            ++nRadixBucket[nMod];
        }

        // 4.2 cumulate all the value of the nRadixBucket
        for(i = 1; i < 10; ++i)
        {
            nRadixBucket[i] += nRadixBucket[i - 1];
        }

        // 5. for each element of pnArr, pnArr[i], get it's module of pnArr[i] / nExp10
            //  and put it in the location of --radixBucket[mod]
        for(i = nArrSize - 1; i >= 0; --i)
        {
            nMod = pnArr[i] / nExp10 % 10;
            anTemp[--nRadixBucket[nMod]] = pnArr[i];
        }

        // 6. increase n#Exp10 10 fold and put anTemp to pnArr
        nExp10 *= 10;
        memcpy(pnArr, anTemp, (unsigned)nArrSize * sizeof(int));
    }

    // 7. if nShiftVal > 0, shift it back to the original array
    if(nShiftVal > 0)
    {
        for(i = 0; i < nArrSize; ++i)
        {
            pnArr[i] -= nShiftVal;
        }
    }

    return;
}