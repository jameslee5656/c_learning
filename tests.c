#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"
#include "helper.h"
#include "tests.h"

// checkIsSame, check if pnArray1 and pnArray2 is the same
bool checkIsSame(int *pnArray1, int *pnArray2, const unsigned int uArraySize)
{
    int i = 0;

    for(i = 0; i < uArraySize; ++i)
    {
        if(pnArray1[i] != pnArray2[i])
        {
            return false;
        }
    }

    return true;
}

// unitTest function, making sure that the below test cases passed
/*
0, 3, 1, 5, 2
-1000000, 9999, -9999, 0, 1000000
5, 4, 3, 2, 1
0, 0, 0, 0, 0
-14, -14, -14, -14, -14
1, 2, 3, 4, 5
*/
void unitTestSortFunc(void (*pfnSort)(int *, const unsigned int), char *psSortName)
{
    unsigned int uArraySize = 0;
    unsigned int uTestNum = 0;
    int i = 0;
    int test1[5] = {0, 3, 1, 5, 2};
    int correct1[5] = {0, 1, 2, 3, 5};
    int test2[5] = {1000000, 0, 9999, -9999, -1000000};
    int correct2[5] = {-1000000, -9999, 0, 9999, 1000000};
    int test3[5] = {5, 4, 3, 2, 1};
    int correct3[5] = {1, 2, 3, 4, 5};
    int test4[5] = {0, 0, 0, 0, 0};
    int correct4[5] = {0, 0, 0, 0, 0};
    int test5[5] = {-14, -14, -14, -14, -14};
    int correct5[5] = {-14, -14, -14, -14, -14};
    int test6[5] = {1, 2, 3, 4, 5};
    int correct6[5] = {1, 2, 3, 4, 5};

    // unitTest1
    // 0, 3, 1, 5, 2
    {
        uTestNum = 1;
        uArraySize = 5;
        sortFunc(test1, 5);
        if(checkIsSame(test1, correct1, uArraySize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest2
    // 0, 3, 1, 5, 2
    {
        uTestNum = 2;
        uArraySize = 5;
        sortFunc(test2, 5);
        if(checkIsSame(test2, correct2, uArraySize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest3
    // 5, 4, 3, 2, 1
    {
        uTestNum = 3;
        uArraySize = 5;
        sortFunc(test3, 5);
        if(checkIsSame(test3, correct3, uArraySize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest4
    // 0, 0, 0, 0, 0
    {
        uTestNum = 4;
        uArraySize = 5;
        sortFunc(test4, 5);
        if(checkIsSame(test4, correct4, uArraySize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest5
    // -14, -14, -14, -14, -14
    {
        uTestNum = 5;
        uArraySize = 5;
        sortFunc(test5, 5);
        if(checkIsSame(test5, correct5, uArraySize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest6
    // 1, 2, 3, 4, 5
    {
        uTestNum = 6;
        uArraySize = 5;
        sortFunc(test6, 5);
        if(checkIsSame(test6, correct6, uArraySize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }
}

/**
 * @function verifyArray
 * @abstract checking that if the array is non-decreasing
 * @param pnArray array that needed to be non-decreasing
 * @param uArraySize the array size
 * return bool, verify passed or not
 */
bool verifyArray(int *pnArray, const unsigned int uArraySize)
{
    int i = 0;

    for(i = 1; i < uArraySize; ++i)
    {
        if(pnArray[i - 1] > pnArray[i])
        {
            printf("%s at %d, pnArray[i - 1]:%d pnArray[i]:%d\n",
                ERROR_VERIFY_FAILURE, i, pnArray[i - 1], pnArray[i]);
            return false;
        }
    }

    return true;
}

/**
 * @function checkPartitionIsCorrect
 * @abstract check if the array is partitioned correctly
 *
 * check that left of the arr[iPartitionIndex] is smaller
 * and the right of arr[iPartitionIndex] is larger
 *
 * @param pnArray interger pointer pointing to partitioned array
 * @param uArraySize unsigned int that is the array size
 * @param iPartitionIndex the index that is where the partition number is at
 * return bool, true means check passed, false is failed
 */
// check that if the parition function is correct
//
bool checkPartitionIsCorrect(
    int *pnArray, const unsigned int uArraySize, int iPartitionIndex)
{
    int i = 0;
    int pivot = 0;

    if(iPartitionIndex >= uArraySize || 0 > iPartitionIndex)
    {
        return false;
    }

    pivot = pnArray[iPartitionIndex];

    // check the left side of the iPartitionIndex is all smaller than pivot
    for(i = 0; i < iPartitionIndex; ++i)
    {
        if(pnArray[i] >= pivot) return false;
    }

    // check the right side of the iParitionIndex is not smaller than pivot
    for(i = iPartitionIndex + 1; i < uArraySize; ++i)
    {
        if(pnArray[i] < pivot)  return false;
    }

    return true;
}

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
    int (*partitionFunc)(int *, const unsigned int, unsigned int, unsigned int))
{
    unsigned int uArraySize = 0;
    unsigned int uTestNum = 0;
    int i = 0, partitionIndex = 0;
    int test1[5] = {3, 1, 4, 2, 5};
    int test2[5] = {4, 3, 2, 5, 1};
    int test3[5] = {4, 4, 4, 4, 4};
    int test4[5] = {0, 1, 2, 3, 4};
    int test5[5] = {5, 1, 2, 3, 4};
    int test6[5] = {0, -5, 4, 2, -3};

    // unitTest1
    {
        uTestNum = 1;
        uArraySize = 5;
        partitionIndex = partitionFunc(test1, uArraySize, 0, uArraySize - 1);
        if(checkPartitionIsCorrect(test1, uArraySize, partitionIndex) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest2
    {
        uTestNum = 2;
        uArraySize = 5;
        partitionIndex = partitionFunc(test2, uArraySize, 0, uArraySize - 1);
        if(checkPartitionIsCorrect(test2, uArraySize, partitionIndex) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest3
    {
        uTestNum = 3;
        uArraySize = 5;
        partitionIndex = partitionFunc(test3, uArraySize, 0, uArraySize - 1);
        if(checkPartitionIsCorrect(test3, uArraySize, partitionIndex) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest4
    {
        uTestNum = 4;
        uArraySize = 5;
        partitionIndex = partitionFunc(test4, uArraySize, 0, uArraySize - 1);
        if(checkPartitionIsCorrect(test4, uArraySize, partitionIndex) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest5
    {
        uTestNum = 5;
        uArraySize = 5;
        partitionIndex = partitionFunc(test5, uArraySize, 0, uArraySize - 1);
        if(checkPartitionIsCorrect(test5, uArraySize, partitionIndex) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest6
    {
        uTestNum = 6;
        uArraySize = 5;
        partitionIndex = partitionFunc(test6, uArraySize, 0, uArraySize - 1);
        if(checkPartitionIsCorrect(test6, uArraySize, partitionIndex) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }
}