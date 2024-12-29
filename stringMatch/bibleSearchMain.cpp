#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/time.h>

#include "bibleSearch.hpp"

int main()
{
    FILE *dictFd, *bibleFd;
    int i = 0,  j = 0, nPatternLen = 0, nBibleLineLen = 0, nPatternArrSz = 0;
    int ret = 0;
    char **psPatternArr = NULL;
    char *psBibleContent = NULL;
    char buf[1024];
    int *kmpResult, *bmResult, *acResult;
    struct timeval timer, now;
    double dSeconds = 0;

    // 1. 開啟 dict.txt, bible.txt 兩個檔案，並取得 file descriptor
    dictFd = fopen("dict.txt", "r");
    if (dictFd == 0)
    {
        printf(gERROR_MSG_UNABLE_OPEN_FILE, "dict.txt");
        return -1;
    }

    bibleFd = fopen("bible.txt", "r");
    if (bibleFd == 0)
    {
        printf(gERROR_MSG_UNABLE_OPEN_FILE, "bible.txt");
        if (bibleFd != 0)
            fclose(bibleFd);
        return -1;
    }

    // 2. 讀取每一行的 dict.txt, 並將每一行的單字放入 patternArray 當中, 且pattern 結尾都有 ‘\0’
    i = -1;
    psPatternArr = (char **) malloc(gPATTERN_ARR_MAX_SIZE * sizeof(char *));
    while (fgets(buf, 1024, dictFd) != 0)
    {
        nPatternLen = -1;
        while (buf[++nPatternLen] != ' ')
            continue;

        if (i >= gPATTERN_ARR_MAX_SIZE)
        {
            printf(gERROR_MSG_PATTERN_ARR_FULL);
            return -1;
        }

        psPatternArr[++i] = (char *) malloc(gPATTERN_MAX_LEN);
        memcpy(psPatternArr[i], buf, nPatternLen);
    }
    nPatternArrSz = i + 1;

    // 3. 讀取bible.txt, 並將全部內容放進 bibleString 當中, bibleString 結尾有 ‘\0’
    i = 0;
    psBibleContent = (char *) malloc(gBIBLE_MAX_LEN);
    while (fgets(buf, 1024, bibleFd) != 0)
    {
        nBibleLineLen = strnlen(buf, 1024);

        for (j = 0; j < nBibleLineLen; ++j)
        {
            if (buf[j] >= 'A' && buf[j] <= 'Z')
                buf[j] += 32;
        }

        if (i + nBibleLineLen + 1 >= gBIBLE_MAX_LEN)
        {
            printf(gERROR_MSG_BIBLE_CONTENT_FULL);
            return -1;
        }

        memcpy(&(psBibleContent[i]), buf, nBibleLineLen);
        i += nBibleLineLen;
        psBibleContent[i++] = ' ';
    }

    // 4. 分別 initialize kmpResult, bmResult, acResult 紀錄每一個 pattern 用不同 search 後的結果
    kmpResult = (int *) malloc(sizeof(int) * nPatternArrSz);
    bmResult = (int *) malloc(sizeof(int) * nPatternArrSz);
    acResult = (int *) malloc(sizeof(int) * nPatternArrSz);

    // 5. for loop 每一個 pattern，將 pattern, bibleString傳入 kmpSearch function 當中, 並將每一個結果記錄在 kmpResult 中
// #if 0
    gettimeofday(&timer, NULL);
    for (i = 0; i < nPatternArrSz; ++i)
    {
        ret = kmpSearch(psPatternArr[i], psBibleContent);
        if (ret < 0)
        {
            printf(gERROR_MSG_SEARCH_FAILED, gKMP_SEARCH_NAME, i + 1, ret);
            return -1;
        }

        kmpResult[i] = ret;
        // if (i % 10000 == 0)
            // printf("KMP: i: %d, pattern: %s, found %d times\n", i, psPatternArr[i], ret);
    }
    gettimeofday(&now, NULL);
    dSeconds = now.tv_sec - timer.tv_sec + (double) (now.tv_usec - timer.tv_usec) / 1000000;
    printf("KMP search spend %f seconds\n\n", dSeconds);
// #endif

    // 6. for loop 每一個 pattern，將 pattern, bibleString傳入 bmSearch function 當中, 並將每一個結果記錄在 bmResult 中
// #if 0
    gettimeofday(&timer, NULL);
    for (i = 0; i < nPatternArrSz; ++i)
    {
        ret = bmSearch(psPatternArr[i], psBibleContent);
        if (ret < 0)
        {
            printf(gERROR_MSG_SEARCH_FAILED, gBM_SEARCH_NAME, i + 1, ret);
            return -1;
        }

        bmResult[i] = ret;
        // if (i % 10000 == 0)
            // printf("BM: i: %d, pattern: %s, found %d times\n", i, psPatternArr[i], ret);
    }
    gettimeofday(&now, NULL);
    dSeconds = now.tv_sec - timer.tv_sec + (double) (now.tv_usec - timer.tv_usec) / 1000000;
    printf("BM search spend %f seconds\n", dSeconds);
// #endif

    // 7. 將 patternArray, bibleString, acResult傳入 acSearch function
    gettimeofday(&timer, NULL);
    ret = acSearch(psPatternArr, nPatternArrSz, psBibleContent, acResult);
    if (ret < 0)
        printf(gERROR_MSG_SEARCH_FAILED_WITHOUT_PATTERN_IDX, gAC_SEARCH_NAME);
    gettimeofday(&now, NULL);
    dSeconds = now.tv_sec - timer.tv_sec + (double) (now.tv_usec - timer.tv_usec) / 1000000;
    printf("AC search spend %f seconds\n", dSeconds);

ERROR:
    // 8. 釋放 patternArray, bibleString, kmpResult, bmResult, acResult 的記憶體
    if (psPatternArr != NULL)
    {
        free(psPatternArr);
        psPatternArr = NULL;
    }

    if (psBibleContent != NULL)
    {
        free(psBibleContent);
        psBibleContent = NULL;
    }

    if (kmpResult != NULL)
    {
        free(kmpResult);
        kmpResult = NULL;
    }

    if (bmResult != NULL)
    {
        free(bmResult);
        bmResult = NULL;
    }

    if (acResult != NULL)
    {
        free(acResult);
        acResult = NULL;
    }

    // close dict.txt, bible.txt 的 file descriptor
    if (dictFd != 0)
    {
        fclose(dictFd);
        dictFd = 0;
    }

    if (bibleFd != 0)
    {
        fclose(bibleFd);
        bibleFd = 0;
    }
}