#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"
#include "tests.h"

// checkIsSame, check if arr1 and arr2 is the same
bool checkIsSame(int *arr1, int *arr2, const unsigned int uArrSize)
{
    int i = 0;

    for(i = 0; i < uArrSize; ++i)
    {
        if(arr1[i] != arr2[i])
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
void unitTest(void (*sortFunc)(int *, const unsigned int), char *sSortName)
{
    unsigned int uArrSize = 0;
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
        uArrSize = 5;
        sortFunc(test1, 5);
        if(checkIsSame(test1, correct1, uArrSize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, sSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest2
    // 0, 3, 1, 5, 2
    {
        uTestNum = 2;
        uArrSize = 5;
        sortFunc(test2, 5);
        if(checkIsSame(test2, correct2, uArrSize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, sSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest3
    // 5, 4, 3, 2, 1
    {
        uTestNum = 3;
        uArrSize = 5;
        sortFunc(test3, 5);
        if(checkIsSame(test3, correct3, uArrSize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, sSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest4
    // 0, 0, 0, 0, 0
    {
        uTestNum = 4;
        uArrSize = 5;
        sortFunc(test4, 5);
        if(checkIsSame(test4, correct4, uArrSize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, sSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest5
    // -14, -14, -14, -14, -14
    {
        uArrSize = 5;
        sortFunc(test5, 5);
        if(checkIsSame(test5, correct5, uArrSize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, sSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }

    // unitTest6
    // 1, 2, 3, 4, 5
    {
        uArrSize = 5;
        sortFunc(test6, 5);
        if(checkIsSame(test6, correct6, uArrSize) == false)
        {
            printf("%s, %s, %s%u\n"
                , ERROR_VERIFY_FAILURE, sSortName, FUNC_NAME_UNITTEST, uTestNum);
            return;
        }
    }
}

/**
 * @function verifyArray
 * @abstract checking that if the array is non-decreasing
 * @param arr array that needed to be non-decreasing
 * @param uArrSize the array size
 * return bool, verify passed or not
 */
bool verifyArray(int* arr, const unsigned int uArrSize)
{
    int i = 0;

    for(i = 1; i < uArrSize; ++i)
    {
        if(arr[i - 1] > arr[i])
        {
            printf("%s at %d, arr[i - 1]:%d arr[i]:%d\n",
                ERROR_VERIFY_FAILURE, i, arr[i - 1], arr[i]);
            return false;
        }
    }

    return true;
}