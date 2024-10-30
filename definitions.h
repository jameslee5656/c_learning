#ifndef DEFINITIOHS_H
#define DEFINITIONS_H

// gN should not be larger than INT_MAX(2147483647)
#define DEBUG
#ifdef DEBUG
#define gRANDOM_ARRAY_SIZE      5
#else
#define gRANDOM_ARRAY_SIZE      1000 * 100
#endif // DEBUG

#define gRANDOM_UPPER_LIMIT     (1 << 30)
#define gRANDOM_LOWER_LIMIT     -1 * (1 << 30)
#define gSTACK_SIZE             gRANDOM_ARRAY_SIZE
#define gLOOP                   1

#define SUCCESS_MERGE           0
#define SUCCESS_HEAPIFY         1

#define ERROR_ARRAY_INVALID         -1
#define ERROR_ARRAY_SIZE_INVALID    -2
#define ERROR_INPUT_PARAM_INVLID    -3
#define ERROR_VERIFY_FAILURE        "[Error] Sorting verify failure"
#define ERROR_UNITTEST_FAILURE      "[Error] Unit test failure"
#define ERROR_SORTTING_FAILED       "[Error] Sorting failed"
#define ERROR_MERGE_FAILED          "[Error] Merged failed"
#define ERROR_GARR_SIZE_LARGER_THAN_GMAX_NUM    "[Error] gARR_SIZE sets to big, shouldn't larger than gMAX_NUM"

#define SORT_TYPE_QUICKSORT_RECURSIVE       "quickSortRecursive"
#define SORT_TYPE_QUICKSORT_ITERATIVE       "quickSortIterative"
#define SORT_TYPE_MERGESORT_RECURSIVE       "mergeSortRecursive"
#define SORT_TYPE_MERGESORT_ITERATIVE       "mergeSortIterative"
#define SORT_TYPE_HEAPSORT_RECURSIVE        "heapSortRecursive"
#define SORT_TYPE_HEAPSORT_ITERATIVE        "heapSortIterative"
#define SORT_TYPE_INSERTIONSORT_RECURSIVE   "insertionSortRecursive"
#define SORT_TYPE_INSERTIONSORT_ITERATIVE   "insertionSortItertive"
#define SORT_TYPE_SELECTIONSORT_RECURSIVE   "selectionSortRecursive"
#define SORT_TYPE_SELECTIONSORT_ITERATIVE   "selectionSortIterative"
#define SORT_TYPE_RADIXSORT_RECURSIVE       "radixSortRecursive"
#define SORT_TYPE_RADIXSORT_ITERATIVE       "radixSortIterative"

#define FUNC_NAME_PARTITION     "partition"
#define FUNC_NAME_MERGE         "merge"
#define FUNC_NAME_BUILDHEAP     "buildHeap"
#define FUNC_NAME_UNITTEST      "unitTest"
#define FUNC_NAME_CREATE_RANDOM_ARRAY   "createRandomArray"
#define FUNC_NAME_HEAPIFY_RECURSIVE     "heapifyRecursive"
#define FUNC_NAME_HEAPIFY_ITERATIVE     "heapifyIterative"

#endif // DEFINITIONS_H