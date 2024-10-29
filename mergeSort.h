/**
 * @Description: merge two presumed sorted range, left ~ middle - 1, middle ~ right
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @param left, middle:
 *  the first range is left ~ (middle - 1), presumed sorted
 * @param middle, right:
 *  the second range is middle ~ right, presumed sorted
 *
 * if(nArrSize > gRANDOM_ARRAY_SIZE)   return ERROR_INPUT_PARAM_INVLID;
 * if(nLeft >= nMiddle)    return ERROR_INPUT_PARAM_INVLID;
 * if(nMiddle > nRight)    return ERROR_INPUT_PARAM_INVLID;
 *
 * @return int, MERGE_SUCCESS(0), or other failure(<= 0)
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.28 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
int merge(int *pnArr, const int nArrSize, int left, int middle, int right);

/**
 * @Description: public function, merge sort pnArr recursively
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.28 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void mergeSortRecursive(int *pnArr, int nArrSize);

/**
 * @Description: private function, merge sort pnArr recursively
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @param nLeft, nMiddle:
 *  recursively seperate the left part, nLeft ~ nMiddle - 1, of the array;
 * @param nMiddle, nRight:
 *  recursively sperate the right part, nMiddle ~ nRight, of the array;
 *
 * Recursive Ending Conditions
 * if(nLeft >= nMiddle)                return;
 * if(nMiddle > nRight)                return;
 * if(nMiddle >= nArrSize)             return;
 * if(nRight >= nArrSize)              return;
 *
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.28 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void __mergeSortRecursive(int *pnArr, int nArrSize, int nLeft, int nMiddle, int nRight);

/**
 * @Description: public function, merge sort pnArr iteratively
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @return
 * @bug FIX:
 * @NOTE:
 * First Created on: 2024.10.29 by James.Lee
 * Last Modified on:
 * Code Review Record on:
 * Copyright(c):
 */
void mergeSortIterative(int *pnArr, int nArrSize);