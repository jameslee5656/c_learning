#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <stdbool.h>

#define N       1000 * 100
#define LOOP    1
#define BASE    10

int A[N];
// for recursive quick sort
int stack[N];

// for merge sort
int left[N];
int right[N];

// for counting sort
int counts[N];

// for radix sort
int A2[N];

//////////////////
// helper function
////////////////////
void swap(int *a1, int *a2)
{
    int temp = *a1;
    *a1 = *a2;
    *a2 = temp;
}

void printArray(int *arr)
{
    for (int i=0;i<N;++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void verifyArray(int *arr)
{
    bool result = true;
    for (int i=0;i<N;++i)
    {
        if (arr[i] != i)
        {
            result = false;
            break;
        }
    }

    if (!result)
        printf("CURRENT SORTING IS INCORRECT\n");
}

int min(int a, int b)
{
    if(a <= b)
        return a;
    else
        return b;
}

//////////////////
// Quick Sort
//////////////////
int partition(int *arr, unsigned int start, unsigned int end)
{
    // check the boundry is correct
    if (start >= end)
        return start;

    // 1. use the start as pivot;
    int pivot = arr[start];

    // 2. go through the range and swap out the smaller one to the left,
    // bigger one to the right
        // detail 1: i = -1, represent the start (pivot location)
        // detail 2: for(int j=0;j<=end;++j) going through each one and swap the smaller one with ++i
    int i=start;
    for (int j=start+1;j<=end;++j)
    {
        if (arr[j] < pivot)
        {
            swap(&arr[++i], &arr[j]);
        }
    }

    // 3. swap the pivot with the smaller (or equal) one (where location i should be)
    swap(&arr[start], &arr[i]);

    return i;
}

void quickSortRecursive(int *arr, int start, int end)
{
    // 1. check if start, end boundary is correct
    if(start >= end)
        return;

    // 2. parition and get the middle one (sorted location)
    int m = partition(arr, start, end);
    // 3.1 recursively sort the left part
    quickSortRecursive(arr, start, m - 1);
    // 3.2 recursively sort the right part
    quickSortRecursive(arr, m + 1, end);
}

// TODO this one is quite special, practice this again after some time
void quickSortIterative(int *arr)
{
    int top=-1;
    int left=0,right=0;

    // push the left and right boundary to the stack
    stack[++top] = 0;
    stack[++top] = N - 1;

    while (top >= 0)
    {
        right = stack[top--];
        left = stack[top--];

        int p = partition(arr, left, right);

        // making sure that the left side of the partition still has number
        if (p-1 > left)
        {
            stack[++top] = left;
            stack[++top] = p - 1;
        }

        // making sure that the right side of the partition still has number
        if (p+1 < right)
        {
            stack[++top] = p + 1;
            stack[++top] = right;
        }
    }
}

//////////////////
// Insertion Sort
//////////////////
void insertionSortIterative(int *arr)
{
    int i=0,j=0;
    for (i=1;i<N;++i)
    {
        int insertNum = arr[i];
        for (j=i;j>0&&arr[j-1]>insertNum;--j)
            swap(&arr[j], &arr[j-1]);

        arr[j] = insertNum;
    }
}

void insertionSortRecursive(int *arr, unsigned int i)
{
    if(i >= N || i < 0)
        return;

    int j = 0;
    int insertNum = arr[i];

    for (j=i;j>0&&arr[j-1]>insertNum;--j)
        swap(&arr[j-1], &arr[j]);

    arr[j] = insertNum;

    insertionSortRecursive(arr, ++i);
}

//////////////////
// Selection Sort
//////////////////
void selectionSortIterative(int *arr)
{
    int i=0,j=0,minIndex=0;
    for (i=0;i<N;++i)
    {
        minIndex = i;
        for (j=i+1;j<N;++j)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(&arr[minIndex], &arr[i]);
    }
}

void selectionSortRecursive(int *arr, unsigned int i)
{
    if(i < 0 || i >= N)
        return;

    int minIndex = i;
    for (int j=i+1;j<N;++j)
    {
        if(arr[j] < arr[minIndex])
            minIndex = j;
    }

    swap(&arr[minIndex], &arr[i]);

    selectionSortRecursive(arr, i+1);
}

////////////////////
// Merge Sort
////////////////////
// Phantom's implementation seems only need one array
    // -> take a more careful look and understand
// I use two array, which is more intuitive for me
void merge(int *arr, unsigned int start, unsigned int mid, unsigned int end)
{
    int i=0,leftIndex=0,rightIndex=0;
    memcpy(left, arr + start, sizeof(int)*(mid - start + 1));
    memcpy(right, arr + mid + 1, sizeof(int) * (end - mid));

    // putting the last one with a maxout number
        // -> to know that it's the end;
    left[mid - start + 1] = N + 1;
    right[end - mid] = N + 1;

    for (i=start;i<=end;++i)
    {
        if(left[leftIndex] <= right[rightIndex])
        {
            arr[i] = left[leftIndex];
            ++leftIndex;
        }
        else
        {
            arr[i] = right[rightIndex];
            ++rightIndex;
        }
    }
}

// this one too, think again and practice again
void mergeSortIterative(int *arr)
{
    for (int cur_size=1;cur_size<N;cur_size*=2)
    {
        for (int left=0;left<N;left+=2*cur_size)
        {
            int mid = min(left+cur_size-1, N-1);
            int right = min(left+2*cur_size-1, N-1);
            merge(arr, left, mid, right);
        }
    }
}

void mergeSortRecursive(int *arr, unsigned int start, unsigned int end)
{
    if(start >= end)
        return;

    int mid=0;
    // mid = ((first & last) + ((first ^ last) >> 1));
    // have some thoughts what does this mean??
    mid = start + (end - start) / 2;
    mergeSortRecursive(arr, start, mid);
    mergeSortRecursive(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

void __counting(int *arr, int *counts, unsigned int cur_index)
{
    if (cur_index >= N || cur_index < 0)
        return;

    ++counts[arr[cur_index]];
    __counting(arr, counts, cur_index + 1);
}

void __countingSort(int arr, int counts, unsigned int cur_arr_index, unsigned int cur_counts_index)
{
    if (cur_arr_index >= N || cur_arr_index < 0)
        return;

    while (cur_counts_index < N && counts[cur_counts_index] <= 0)
        ++cur_counts_index;

    if(cur_counts_index >= N || cur_counts_index < 0)
    {
        printf("[Error] countingSort , cur_counts_index incorrect\n");
        return;
    }

    arr[cur_arr_index] = cur_counts_index;
    --counts[cur_counts_index];

    __countingSort(arr, counts, cur_arr_index + 1, cur_counts_index);
}

void countingSortRecursive(int *arr)
{
    memset(counts, 0, sizeof(int)*N);
    __counting(arr, counts, 0);
    __countingSort(arr, counts, 0, 0);
}

void countingSortIterative(int *arr)
{
    int i=0,j=0;

    for (i=0;i<N;++i)
        ++counts[arr[i]];

    for (i=0;i<N;++i)
    {
        while (j < N && counts[j] == 0)
            ++j;
        arr[i] = j;
        --counts[j];
    }
}

void radixSortIterative(int *arr)
{
    int i=0,j=0,exp=1,max_num=arr[0];
    int radixBucket[10];

    // find the max number of the array
    for (i=0;i<N;++i)
    {
        if (arr[i] > max_num)
            max_num = arr[i];
    }

    while (max_num / exp > 0)
    {
        memset(radixBucket, 0, sizeof(int)*10);

        for (i=0;i<N;++i)
            ++radixBucket[arr[i] / exp % 10];

        // make the radixBucket be the prefix array
        for (i=1;i<BASE;++i)
            radixBucket[i] += radixBucket[i-1];

        // from the back and put the number to the "stable sort" location
        for (i=N-1;i>=0;--i)
        {
            int mod = arr[i] / exp % 10;
            // printf("%d loc: %d\n", arr[i], radixBucket[mod]);
            A2[--radixBucket[mod]] = arr[i];
        }
        // printf("\n");

        memcpy(arr, A2, sizeof(int)*N);
        exp *= 10;
    }
}

void __radixSort(int *arr, int max_num, int exp)
{
    if (max_num / exp <= 0)
        return;

    int i=0;
    int radixBucket[10];
    memset(radixBucket, 0, sizeof(int)*10);

    for (i=0;i<N;++i)
        ++radixBucket[arr[i] / exp % 10];

    for (i=1;i<10;++i)
        radixBucket[i] += radixBucket[i-1];

    for (i=N-1;i>=0;--i)
    {
        int mod = arr[i] / exp % 10;
        A2[--radixBucket[mod]] = arr[i];
    }

    memcpy(arr, A2, sizeof(int)*N);
    __radixSort(arr, max_num, exp*10);
}

void radixSortRecursive(int *arr)
{
    int max_num = arr[0];
    for (int i=0;i<N;++i)
        if (max_num < arr[i])
            max_num = arr[i];
    __radixSort(arr, max_num, 1);
}

int main(void)
{
    time_t t;
    int i=0,j=0,temp=0,sum=0;
    clock_t begin, end;

    time(&t);
    srand(t);

    for (i=0;i<N;++i)
        A[i] = i;

    // scramble A
    for (i=N-1;i>0;--i)
    {
        j = rand() % (i+1);
        temp = A[i];
        swap(&A[i],&A[j]);
    }

    // copy one to restore
    int restoreA[N];
    memcpy(restoreA, A, sizeof(int)*N);
#ifdef DEBUG
    printArray(restoreA);
#endif

    printf("starting quickSortIterative ");
    // A[0] = 4;
    // A[1] = 5;
    // A[2] = 1;
    // A[3] = 3;
    // A[4] = 6;
    // A[5] = 2;
    for (i=0;i<LOOP;++i)
    {
        memcpy(A, restoreA, sizeof(int)*N);
        begin = clock();
        quickSortIterative(A);
        end = clock();
        sum += (end - begin);
        verifyArray(A);
    }
    printf("Spend Time:[%f]\n", (float) sum / LOOP / CLOCKS_PER_SEC);

    printf("starting quickSortRecursive ");
    sum = 0;
    for (i=0;i<LOOP;++i)
    {
        memcpy(A, restoreA, sizeof(int)*N);
        begin = clock();
        quickSortRecursive(A, 0, N-1);
        end = clock();
        sum += (end - begin);
        verifyArray(A);
    }
    printf("Spend Time:[%f]\n", (float) sum / LOOP / CLOCKS_PER_SEC);

    printf("starting insertionSortIterative ");
    sum = 0;
    for (i=0;i<LOOP;++i)
    {
        memcpy(A, restoreA, sizeof(int)*N);
        begin = clock();
        insertionSortIterative(A);
        end = clock();
        sum += (end - begin);
        verifyArray(A);
    }
}