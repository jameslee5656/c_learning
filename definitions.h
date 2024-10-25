#ifndef DEFINITIOHS_H
#define DEFINITIONS_H

// gN should not be larger than INT_MAX(2147483647)
#define DEBUG
#ifdef DEBUG
#define gARR_SIZE               5
#define gMAX_NUM                10
#else
#define gARR_SIZE               1000 * 1000
#define gMAX_NUM                1000 * 1000
#endif // DEBUG
#define gSTACK_SIZE             gARR_SIZE
#define gLOOP                   1

#define ERROR_ARRAY_INVALID         -1
#define ERROR_ARRAY_SIZE_INVALID    -2
#define ERROR_INPUT_PARAM_INVLID    -3
#define ERROR_VERIFY_FAILURE    "[Error] Sorting verify failure"
#define ERROR_UNITTEST_FAILURE  "[Error] Unit test failure"
#define ERROR_SORTTING_FAILED   "[Error] Sorting failed"
#define ERROR_GARR_SIZE_LARGER_THAN_GMAX_NUM    "[Error] gARR_SIZE sets to big, shouldn't larger than gMAX_NUM"

#define SORT_TYPE_QUICKSORT_RECURSIVE       "quickSortRecursive"
#define SORT_TYPE_QUICKSORT_ITERATIVE       "quickSortIterative"
#define SORT_TYPE_MERGESORT_RECURSIVE       "mergeSortRecursive"
#define SORT_TYPE_MERGESORT_ITERATIVE       "mergeSortIterative"
#define SORT_TYPE_HEAPSORT_RECURSIVE        "heapSortRecursive"
#define SORT_TYPE_HEAPSORT_ITERATIVE        "heapSortIterative"

#define FUNC_NAME_PARTITION     "partition"
#define FUNC_NAME_MERGE         "merge"
#define FUNC_NAME_BUILDHEAP     "buildHeap"
#define FUNC_NAME_UNITTEST      "unitTest"

#endif // DEFINITIONS_H