#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"
#include "helper.h"
#include "unitTests.h"

// checkIsSame, check if pnArray1 and pnArray2 is the same
bool checkIsSame(int *pnArray1, int *pnArray2, const int nArrSize)
{
    int i = 0;

    for(i = 0; i < nArrSize; ++i)
    {
        if(pnArray1[i] != pnArray2[i])
        {
            return false;
        }
    }

    return true;
}

/**
 * @Description: check that if the array is non-decreasing
 * @param pnArr array that needed to be non-decreasing
 * @param nArrSize the array size
 * return bool, verify passed or not
 */
bool isNonDecreasing(int *pnArr, const int nArrSize)
{
    int i = 0;

    for(i = 1; i < nArrSize; ++i)
    {
        if(pnArr[i - 1] > pnArr[i])
        {
            printf("%s at %d, pnArr[i - 1]:%d pnArr[i]:%d\n",
                ERROR_VERIFY_FAILURE, i, pnArr[i - 1], pnArr[i]);
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
void unitTestSortFunc(void (*pfnSort)(int *, const int), char *psSortName)
{
    int nArrSize = 0;
    int nTestNum = 0;
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
        nTestNum = 1;
        nArrSize = 5;
        pfnSort(test1, 5);
        if(checkIsSame(test1, correct1, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest2
    // int test2[5] = {1000000, 0, 9999, -9999, -1000000};
    {
        nTestNum = 2;
        nArrSize = 5;
        pfnSort(test2, 5);
        if(checkIsSame(test2, correct2, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest3
    // 5, 4, 3, 2, 1
    {
        nTestNum = 3;
        nArrSize = 5;
        pfnSort(test3, 5);
        if(checkIsSame(test3, correct3, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest4
    // 0, 0, 0, 0, 0
    {
        nTestNum = 4;
        nArrSize = 5;
        pfnSort(test4, 5);
        if(checkIsSame(test4, correct4, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest5
    // -14, -14, -14, -14, -14
    {
        nTestNum = 5;
        nArrSize = 5;
        pfnSort(test5, 5);
        if(checkIsSame(test5, correct5, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest6
    // 1, 2, 3, 4, 5
    {
        nTestNum = 6;
        nArrSize = 5;
        pfnSort(test6, 5);
        if(checkIsSame(test6, correct6, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_VERIFY_FAILURE, psSortName, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }
}

/**
 * @function checkPartitionIsCorrect
 * @abstract check if the array is partitioned correctly
 *
 * check that left of the arr[iPartitionIndex] is smaller
 * and the right of arr[iPartitionIndex] is larger
 *
 * @param pnArr interger pointer pointing to partitioned array
 * @param nArrSize int that is the array size
 * @param iPartitionIndex the index that is where the partition number is at
 * return bool, true means check passed, false is failed
 */
// check that if the parition function is correct
//
bool checkPartitionIsCorrect(
    int *pnArr, const int nArrSize, int iPartitionIndex)
{
    int i = 0;
    int pivot = 0;

    if(iPartitionIndex >= nArrSize || 0 > iPartitionIndex)
    {
        return false;
    }

    pivot = pnArr[iPartitionIndex];

    // check the left side of the iPartitionIndex is all smaller than pivot
    for(i = 0; i < iPartitionIndex; ++i)
    {
        if(pnArr[i] >= pivot) return false;
    }

    // check the right side of the iParitionIndex is not smaller than pivot
    for(i = iPartitionIndex + 1; i < nArrSize; ++i)
    {
        if(pnArr[i] < pivot)  return false;
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
    int (*partitionFunc)(int *, const int, int, int))
{
    int nArrSize = 0, nTestNum = 0;
    int i = 0, partitionIndex = 0;
    int test1[5] = {3, 1, 4, 2, 5};
    int test2[5] = {4, 3, 2, 5, 1};
    int test3[5] = {4, 4, 4, 4, 4};
    int test4[5] = {0, 1, 2, 3, 4};
    int test5[5] = {5, 1, 2, 3, 4};
    int test6[5] = {0, -5, 4, 2, -3};

    // unitTest1
    {
        nTestNum = 1;
        nArrSize = 5;
        partitionIndex = partitionFunc(test1, nArrSize, 0, nArrSize - 1);
        if(checkPartitionIsCorrect(test1, nArrSize, partitionIndex) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest2
    {
        nTestNum = 2;
        nArrSize = 5;
        partitionIndex = partitionFunc(test2, nArrSize, 0, nArrSize - 1);
        if(checkPartitionIsCorrect(test2, nArrSize, partitionIndex) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest3
    {
        nTestNum = 3;
        nArrSize = 5;
        partitionIndex = partitionFunc(test3, nArrSize, 0, nArrSize - 1);
        if(checkPartitionIsCorrect(test3, nArrSize, partitionIndex) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest4
    {
        nTestNum = 4;
        nArrSize = 5;
        partitionIndex = partitionFunc(test4, nArrSize, 0, nArrSize - 1);
        if(checkPartitionIsCorrect(test4, nArrSize, partitionIndex) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest5
    {
        nTestNum = 5;
        nArrSize = 5;
        partitionIndex = partitionFunc(test5, nArrSize, 0, nArrSize - 1);
        if(checkPartitionIsCorrect(test5, nArrSize, partitionIndex) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest6
    {
        nTestNum = 6;
        nArrSize = 5;
        partitionIndex = partitionFunc(test6, nArrSize, 0, nArrSize - 1);
        if(checkPartitionIsCorrect(test6, nArrSize, partitionIndex) == false)
        {
            printf("%s, %s, %s%d\n"
                , ERROR_UNITTEST_FAILURE, FUNC_NAME_PARTITION, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }
}

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
    int (*pfnMerge)(int *, const int nArrSize, int nLeft, int nMiddle, int nRight))
{
    int nArrSize = 0, nTestNum = 0;
    int anTest1[5] = {2, 4, 1, 3, 5};
    int anCorrect1[5] = {1, 2, 3, 4, 5};
    int anTest2[5] = {1, 3, 5, 2, 4};
    int anCorrect2[5] = {1, 2, 3, 4, 5};
    int anTest3[5] = {-1, -1, -2, -2, -2};
    int anCorrect3[5] = {-2, -2, -2, -1, -1};
    int anTest4[5] = {0, 0, 0, 0, 0};
    int anCorrect4[5] = {0, 0, 0, 0, 0};
    int anTest5[5] = {-2, -1, 0, 1, 2};
    int anCorrect5[5] = {-2, -1, 0, 1, 2};
    int anTest6[5] = {6, 3, 1, 4, 0};
    // * special case, left part and right part isn't sort
    int anCorrect6[5] = {1, 4, 0, 6, 3};

    // unitTest1
    // int anTest1[5] = {2, 4, 1, 3, 5};
    // int anCorrect1[5] = {1, 2, 3, 4, 5};
    {
        nArrSize = 5;
        nTestNum = 1;
        pfnMerge(anTest1, nArrSize, 0, 2, 4);
        if(checkIsSame(anTest1, anCorrect1, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n",
                ERROR_UNITTEST_FAILURE, FUNC_NAME_MERGE, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest2
    // int anTest2[5] = {1, 3, 5, 2, 4};
    // int anCorrect2[5] = {1, 2, 3, 4, 5};
    {
        nArrSize = 5;
        nTestNum = 2;
        pfnMerge(anTest1, nArrSize, 0, 2, 4);
        if(checkIsSame(anTest1, anCorrect1, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n",
                ERROR_UNITTEST_FAILURE, FUNC_NAME_MERGE, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }


    // unitTest3
    // int anTest3[5] = {-1, -1, -2, -2, -2};
    // int anCorrect3[5] = {-2, -2, -2, -1, -1};
    {
        nArrSize = 5;
        nTestNum = 3;
        pfnMerge(anTest3, nArrSize, 0, 2, 4);
        if(checkIsSame(anTest3, anCorrect3, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n",
                ERROR_UNITTEST_FAILURE, FUNC_NAME_MERGE, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest4
    // int anTest4[5] = {0, 0, 0, 0, 0};
    // int anCorrect4[5] = {0, 0, 0, 0, 0};
    {
        nArrSize = 5;
        nTestNum = 4;
        pfnMerge(anTest4, nArrSize, 0, 3, 4);
        if(checkIsSame(anTest4, anCorrect4, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n",
                ERROR_UNITTEST_FAILURE, FUNC_NAME_MERGE, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest5
    // int anTest5[5] = {-2, -1, 0, 1, 2};
    // int anCorrect5[5] = {-2, -1, 0, 1, 2};
    {
        nArrSize = 5;
        nTestNum = 5;
        pfnMerge(anTest5, nArrSize, 0, 2, 4);
        if(checkIsSame(anTest5, anCorrect5, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n",
                ERROR_UNITTEST_FAILURE, FUNC_NAME_MERGE, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // * special case, left part and right part isn't sort
    // unitTest6
    // int anTest6[5] = {6, 3, 1, 4, 0};
    // int anCorrect6[5] = {1, 4, 0, 6, 3};
    {
        nArrSize = 5;
        nTestNum = 6;
        pfnMerge(anTest6, nArrSize, 0, 2, 4);
        if(checkIsSame(anTest6, anCorrect6, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n",
                ERROR_UNITTEST_FAILURE, FUNC_NAME_MERGE, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }
}

/*
 * unitTestHeapifyFunc, unit test heapify function to make sure that below case is correct heapify
 3 1 4 2 5
 -> heapify(pnArr[2]) -> 3 5 4 2 1
 -> heapify(pnArr[0]); -> 5 3 4 2 1
 */
void unitTestHeapifyFunc(
    void (*pfnHeapify)(int *pnArr, const int nArrSize, const int nIndex), char *sFuncName)
{
    int nArrSize = 0, nTestNum = 0;
    int test1[5] = {3, 1, 4, 2, 5};
    int correct1[5] = {3, 5, 4, 2, 1};
    int correct2[5] = {5, 3, 4, 2, 1};

    // unitTest1
    // heapify(pnArr[2]) -> 3 5 4 2 1
    {
        nTestNum = 1;
        nArrSize = 5;
        pfnHeapify(test1, nArrSize, 1);
        if(checkIsSame(test1, correct1, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n",
                ERROR_UNITTEST_FAILURE, sFuncName, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }

    // unitTest2
    // heapify(pnArr[0]); -> 5 3 4 2 1
    {
        nTestNum = 2;
        nArrSize = 5;
        pfnHeapify(test1, nArrSize, 0);
        if(checkIsSame(test1, correct2, nArrSize) == false)
        {
            printf("%s, %s, %s%d\n",
                ERROR_UNITTEST_FAILURE, sFuncName, FUNC_NAME_UNITTEST, nTestNum);
            return;
        }
    }
}