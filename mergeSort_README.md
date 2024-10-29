# Merge Sort

## merge
```
/**
 * @Description: merge two presumed sorted range, nLeft ~ nMiddle - 1, nMiddle ~ nRight
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @param nLeft, nMiddle:
 *  the first range is nLeft ~ (nMiddle - 1), presumed sorted
 * @param nMiddle, nRight:
 *  the second range is nMiddle ~ nRight, presumed sorted
 * @return int, MERGE_SUCCESS(0), or other failure(<= 0)
 */
int merge(int *pnArr, int nArrSize, int nLeft, int nMiddle, int nRight);
```
0. Presumed the left part and the right part is sorted,
    if it isn't the result won't be sorted
nLeft ~ nMiddle - 1 (2, 4) is left part
nMiddle ~ nRight (1, 3, 5) is right part
2 4 1 3 5
^---nLeft
    ^---nMiddle
        ^---nRight

1. A preallocated array space (size at least nArrSize),
    with nIndex pointing to the start of the preallocated array,
    nLeftIndex pointing to nLeft, nRightIndex pointing to nMiddle
2 4 1 3 5
^---nLeft
^---nLeftIndex
    ^---nMiddle
    ^---nRightIndex
        ^---nRight
0 0 0 0 0
^---nIndex

2. Find the smallest value from nLeftIndex, nRightIndex
    put the value in nIndex location,
    move forward the nIndex and the smaller Index(nLeftIndex, or nRightIndex)
    2.1 until either nRightIndex > nRight or nLeftIndex > middle - 1

// loop1
2 4 1 3 5
^---nLeftIndex
      ^---nRightIndex
1 0 0 0 0
  ^---nIndex


// loop2
2 4 1 3 5
  ^---nLeftIndex
      ^---nRightIndex
1 2 0 0 0
    ^---nIndex

// loop3
2 4 1 3 5
  ^---nLeftIndex
        ^---nRightIndex
1 2 3 0 0
      ^---nIndex

// loop4
2 4 1 3 5
    ^---nLeftIndex
        ^---nRightIndex
1 2 3 4 0
        ^---nIndex

2.2 if either nLeftIndex > middle or nRightIndex > nRight
2.2.1 nLeftIndex > middle - 1, copy nRightIndex -> right to nIndex
before:
2 4 1 3 5
    ^---nLeftIndex
        ^---nRightIndex
1 2 3 4 0
        ^---nIndex
after:
1 2 3 4 5

2.2.2 nRightIndex > nRight, copy nLeftIndex -> middle - 1 to nIndex
before:
1 3 5 2 4 X
  ^---nLeftIndex
        ^---nRight
          ^---nRightIndex
1 2 3 4 0
        ^---nIndex
after:
1 2 3 4 5

3. copy preallocated result to pnArr (left -> right)
pnArr before:
2 4 1 3 5
pnArr after:
1 2 3 4 5

## mergeSortRecursive
```
/**
 * @Description: public function, merge sort pnArr iteratively
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @return
 */
void mergeSortRecursive(int *pnArr, int nArrSize);
```
* mergeSortRecursive is the public entry point for sorting recursively
* example
pnArray: 2 4 1 3 5
-> calling mergeSortRescursive(pnArray, 5);

```
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
 */
void __mergeSortRecursive(int *pnArr, int nArrSize, int nLeft, int nMiddle, int nRight);
```
* __mergeSortRecursive is a private function that should only called by mergeSortRecursive

1. divide array into blocks until it's undividable (only one element), then start merging each blocks back
* what is undividable -> nLeft == nMiddle && nMiddle == nRight
* example
pnArray: 2 4 1 3 5
-> calling mergeSortRescursive(pnArray, 5);
-> calling __mergeSortRecursive(pnArray, 5, 0, 2, 4)
first level -> (nLeft, nMiddle, nRight) 0, 2, 4
second level ->              (0, 1, 1)              (2, 3, 4)
third level ->          (0, 0, 0)  (1, 1, 1)   (2, 2, 2)    (3, 4, 4)
fourth level ->                                        (3, 3, 3)  (4, 4, 4)

2. merging it back from the bottom of the level
-> using function merge to merge each block of element

## mergeSortIterative

```
/**
 * @Description: public function, merge sort pnArr iteratively
 * @param pnArr, nArrSize:
 *  if(pnArr == NULL) return ERROR_ARRAY_INVALID
 *  if(nArrSize <= 0) return ERROR_ARRAY_SIZE_INVALID
 * @return
 */
void mergeSortIterative(int *pnArr, int nArrSize);
```
* mergeSortIterative will merge sort the array iteratively
* example
pnArray: 2 4 1 3 5
(Loop Level 1.1, block = 1)

(Loop Level 2.1)
nLeft = 0
nMiddle = 1
nRight = 1
merge(0, 1, 1)

(Loop Level 2.2)
nLeft = 0 + 2 * 1 = 2
nMiddle = 3
nRight = 3
merge(2, 3, 3);

(Loop Level 2.3)
nLeft = 2 + 2 * 1 = 4
nMiddle = 4
nRight = 4
-> End Loop

(Loop Level 1.2, block = 1 * 2 = 2)

(Loop Level 2.1)
nLeft = 0
nMiddle = 2
nRight = 3
merge(0, 2, 3)

(Loop Level 2.2)
nLeft = 0 + 2 * 2 = 4
nMiddle = 4
nRight = 4
-> End Loop

(Loop Level 1.3, block = 2 * 2 = 4)

(Loop Level 2.1)
nLeft = 0
nMiddle = 3
nRight = 4
merge(0, 3, 4)

(Loop Level 2.2)
nLeft = 0 + 2 * 3 = 6
-> End Loop