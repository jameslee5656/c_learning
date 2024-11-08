#ifndef RADIXSORT_H
#define RADIXSORT_H

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
void radixSortRecursive(int *pnArr, const int nArrSize);

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
void __radixSortRecursive(int *pnArr, const int nArrSize, const int nMaxVal, const int nCurExp10);

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
 * First Created on: 2024.10.30 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void radixSortIterative(int *pnArr, const int nArrSize);

#endif // RADIXSORT_H