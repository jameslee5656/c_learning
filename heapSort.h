#ifndef HEAPSORT_H
#define HEAPSORT_H

/**
 * @Description: recurisvely heapify the array
 * @param pnArr, nArrSize
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @param nIndex
 *  heapify the array starting from nIndex
 *  if(nIndex >= nArrSize) return SUCCESS_HEAPIFY
 * @return
 */
void heapifyRecursive(int *pnArr, const int nArrSize, const int nIndex);

/**
 * @Description: iteratively heapify the array
 * @param pnArr, nArrSize
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @param nIndex
 *  heapify the array starting from nIndex
 *  if(nIndex >= nArrSize) return SUCCESS_HEAPIFY
 * @return
 */
void heapifyIterative(int *pnArr, const int nArrSize, const int nIndex);



#endif // HEAPSORT_H