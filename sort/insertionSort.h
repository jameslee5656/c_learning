#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

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
void insertionSortRecursive(int *pnArr, const int nArrSize);

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
void __insertionSortRecursive(int *pnArr, const int nArrSize, const int nCurIndex);

/**
 * @Description: insertion sort pnArr iteratively
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
void insertionSortIterative(int *pnArr, const int nArrSize);

#endif // INSERTIONSORT_H