#ifndef TESTS_H
#define TESTS_H

#include <stdbool.h>

// checkIsSame, check if pnArray1 and pnArray2 is the same
bool checkIsSame(int *pnArray1, int *pnArray2, const int nArrSize);

/*
* unitTestSortFunc unit test sort func, making sure that the below test cases passed
0, 3, 1, 5, 2
-1000000, 9999, -9999, 0, 1000000
5, 4, 3, 2, 1
0, 0, 0, 0, 0
-14, -14, -14, -14, -14
1, 2, 3, 4, 5
*/
void unitTestSortFunc(void (*pfnSort)(int *, const int), char *sSortName);

/**
 * @function verifyArray
 * @abstract checking that if the array is non-decreasing
 * @param pnArr array that needed to be non-decreasing
 * @param nArrSize the array size
 * return bool, verify passed or not
 */
bool verifyArray(int* pnArr, const int nArrSize);

/*
* unitTestPartitionFunc, unit test partition function to make sure that the below cases passed
3, 1, 4, 2, 5
4, 3, 2, 5, 1
4, 4, 4, 4, 4
0, 1, 2, 3, 4
5, 1, 2, 3, 4
0, -5, 4, 2, -3
*/
void unitTestPartitionFunc(
    int (*pfnPartition)(int *, const int, int, int));

/*
 * unitTestMergeFunc, unit test mmerge function to make sure that the below cases passed
2 4 1 3 5
1 3 5 2 4
-1 -1 -2 -2 -2
0 0 0 0 0
-2 -1 0 1 2
* special case, left part and right part isn't sort
6 3 1 4 0
 */
void unitTestMergeFunc(
    int (*pfnMerge)(int *pnArr, const int nArrSize, int nLeft, int nMiddle, int nRight));

/*
 * unitTestHeapifyFunc, unit test heapify function to make sure that below case is correct heapify
 3 1 4 2 5
 -> heapify(pnArr[2]) -> 3 5 4 2 1
 -> heapify(pnArr[0]); -> 5 3 4 2 1
 */
void unitTestHeapifyFunc(
    void (*pfnHeapify)(int *pnArr, const int nArrSize, const int nIndex), char *sFuncName);

#endif // TESTS_H