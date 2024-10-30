#ifndef RADIXSORT_H
#define RADIXSORT_H

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
// void selectionSortRecursive(int *pnArr, const int nArrSize);

/**
 * @Description: private function to do selection sort recursively,
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
// void __selectionSortRecursive(int *pnArr, const int nArrSize, const int nCurIndex);

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