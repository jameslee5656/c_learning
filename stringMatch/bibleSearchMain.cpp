#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "definitions.hpp"
#include "kmpSearch.hpp"
#include "bmSearch.hpp"

int main()
{
    FILE *dictFd, *bibleFd;
    int i = 0,  j = 0, nPatternLen = 0, nBibleLineLen = 0, nPatternArrSize = 0;
    int ret = 0;
    char **psPatternArr = NULL;
    char *psBibleContent = NULL;
    char buf[1024];
    int *kmpResult, *bmResult, *acResult;

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
    nPatternArrSize = i + 1;

    // 3. 讀取bible.txt, 並將全部內容放進 bibleString 當中, bibleString 結尾有 ‘\0’
    i = 0;
    psBibleContent = (char *) malloc(gTEXT_MAX_LEN);
    while (fgets(buf, 1024, bibleFd) != 0)
    {
        nBibleLineLen = strnlen(buf, 1024);

        for (j = 0; j < nBibleLineLen; ++j)
        {
            if (buf[j] >= 65 && buf[j] <= 90)
                buf[j] += 32;
        }

        if (i + nBibleLineLen + 1 >= gTEXT_MAX_LEN)
        {
            printf(gERROR_MSG_BIBLE_CONTENT_FULL);
            return -1;
        }

        memcpy(&(psBibleContent[i]), buf, nBibleLineLen);
        i += nBibleLineLen;
        psBibleContent[i++] = ' ';
    }

    // 4. 分別 initialize kmpResult, bmResult, acResult 紀錄每一個 pattern 用不同 search 後的結果
    kmpResult = (int *) malloc(sizeof(int) * nPatternArrSize);
    bmResult = (int *) malloc(sizeof(int) * nPatternArrSize);
    acResult = (int *) malloc(sizeof(int) * nPatternArrSize);

#if 0
    // 5. for loop 每一個 pattern，將 pattern, bibleString傳入 kmpSearch function 當中, 並將每一個結果記錄在 kmpResult 中
    for (i = 0; i < nPatternArrSize; ++i)
    {
        ret = kmpSearch(psPatternArr[i], psBibleContent);
        if (ret < 0)
        {
            printf(gERROR_MSG_SEARCH_FAILED, gKMP_SEARCH_NAME, i + 1);
            return -1;
        }

        kmpResult[i] = ret;
        if (i % 100 == 0)
            printf("KMP: i: %d, pattern: %s, found %d times\n", i, psPatternArr[i], ret);
    }
#endif

    // 6. for loop 每一個 pattern，將 pattern, bibleString傳入 bmSearch function 當中, 並將每一個結果記錄在 bmResult 中
    for (i = 0; i < nPatternArrSize; ++i)
    {
        ret = bmSearch(psPatternArr[i], psBibleContent);
        if (ret < 0)
        {
            printf(gERROR_MSG_SEARCH_FAILED, gBM_SEARCH_NAME, i + 1);
            return -1;
        }

        bmResult[i] = ret;

        if (i > 5)
            goto ERROR;
    }
    // 7. 將 patternArray, bibleString, acResult傳入 acSearch function
    // acSearch 會把最後解果放入 acResult 當中
    // 8. 比較 kmpResult, bmResult, acResult, 是否一樣
    // 9. 釋放 patternArray, bibleString, kmpResult, bmResult, acResult 的記憶體
    // close dict.txt, bible.txt 的 file descriptor

ERROR:
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