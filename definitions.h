#ifndef DEFINITIOHS_H
#define DEFINITIONS_H

// gN should not be larger than INT_MAX(2147483647)
// #define DEBUG
#ifdef DEBUG
#define gN                      5
#else
#define gN                      1000 * 1000
#endif // DEBUG
#define gSTACK_SIZE             gN
#define gLOOP                   1

#define ERROR_ARRAY_INVALID     "[Error] Input array is invalid"
#define ERROR_INPUT_INVALID     "[Error] Input params is invalid"
#define ERROR_VERIFY_FAILURE    "[Error] Sorting verify failure"
#define ERROR_SORTTING_FAILED   "[Error] Sorting failed"
#define ERROR_GN_LARGER_THAN_INT_MAX    "[Error] gN sets to big, shouldn't larger than INT_MAX(2147483647)"

#define ERROR_DETAIL_INVALID_ULEFT      "invalid uLeft"
#define ERROR_DETAIL_INVALID_URIGHT     "invalid uRight"
#define ERROR_DETAIL_LEFT_RIGHT_LARGER_ARR_SIZE     "left ~ right length is longer than uArrSize"
#define ERROR_DETAIL_INVALID_ARRAY_SIZE             "invalid array_size"
#define ERROR_DETAIL_INDEX_EXCEED_STACK_SIZE        "index exceed stack size"

#define SORT_TYPE_QUICKSORT_RECURSIVE       "quickSortRecursive"
#define SORT_TYPE_QUICKSORT_ITERATIVE       "quickSortIterative"
#define SORT_TYPE_MERGESORT_RECURSIVE       "mergeSortRecursive"
#define SORT_TYPE_MERGESORT_ITERATIVE       "mergeSortIterative"

#define FUNC_NAME_PARTITION     "parition"
#define FUNC_NAME_MERGE         "merge"

#endif // DEFINITIONS_H