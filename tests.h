#ifndef TESTS_H
#define TESTS_H

#include <stdbool.h>

// checkIsSame, check if arr1 and arr2 is the same
bool checkIsSame(int *arr1, int *arr2, const unsigned int uArrSize);

/*
* unitTestSortFunc unit test sort func, making sure that the below test cases passed
0, 3, 1, 5, 2
-1000000, 9999, -9999, 0, 1000000
5, 4, 3, 2, 1
0, 0, 0, 0, 0
-14, -14, -14, -14, -14
1, 2, 3, 4, 5
*/
void unitTestSortFunc(void (*sortFunc)(int *, const unsigned int), char *sSortName);

/**
 * @function verifyArray
 * @abstract checking that if the array is non-decreasing
 * @param arr array that needed to be non-decreasing
 * @param uArrSize the array size
 * return bool, verify passed or not
 */
bool verifyArray(int* arr, const unsigned int uArrSize);

/*
* unitTestPartitionFunc, unit test partitionFunc to make sure that the below cases passed
3, 1, 4, 2, 5
4, 3, 2, 5, 1
4, 4, 4, 4, 4
0, 1, 2, 3, 4
5, 1, 2, 3, 4
0, -5, 4, 2, -3
*/
void unitTestPartitionFunc(
    int (*partitionFunc)(int *, const unsigned int, unsigned int, unsigned int));

#endif // TESTS_H