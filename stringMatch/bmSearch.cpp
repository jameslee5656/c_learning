#include <stdio.h>
#include <string.h>

#include "bibleSearch.hpp"

static int gnBadCharArr[gASCII_NUM];
static int gnNextBadCharArr[gPATTERN_MAX_LEN];
static int gnGoodSuffixArr[gPATTERN_MAX_LEN];

int createBadCharTbl(char *psPattern)
{
    int i = 0;
    int nPatternLen = 0;
    int nPos = 0;
    unsigned char uKey = 0;

    if (psPattern == NULL)
        return gERROR_ARGUMENT_INCORRECT;

    nPatternLen = strnlen(psPattern, gPATTERN_MAX_LEN);
    memset(gnBadCharArr, -1, gASCII_NUM * sizeof(int));
    memset(gnNextBadCharArr, -1, gPATTERN_MAX_LEN * sizeof(int));

    // 1. for loop each character in each position of pattern
    for (i = nPatternLen - 1; i >= 0; --i)
    {
        // 2. gnBadCharArr[26] pointing to the first position
        uKey = psPattern[i];
        nPos = gnBadCharArr[uKey];

        if (nPos == -1)
        {
            gnBadCharArr[uKey] = i;
            continue;
        }

        // 3. use gnNextBadCharArr pointing to the next position so that we have psPattern[i]
        while (gnNextBadCharArr[nPos] != -1)
            nPos = gnNextBadCharArr[nPos];

        gnNextBadCharArr[nPos] = i;
    }

    return gSUCCESS;
}

// debug bad char table
void printBadCharTbl()
{
    int i = 0, nPos = 0;

    printf("*********\n");
    for (i = 0; i < 26; ++i)
    {
        nPos = gnBadCharArr[i];
        if (nPos == -1)
            continue;

        printf("%c: %d", i + 'a', nPos);
        while (gnNextBadCharArr[nPos] != -1)
        {
            nPos = gnNextBadCharArr[nPos];
            printf(" %d", nPos);
        }
        printf("\n");
    }

    return;
}

int createGoodSuffixTbl(char *psPattern)
{
    int i = 0, j = 0;
    int K = 0;
    int nPatternLen = 0, nMaxMove = 0;
    char *pFrontTail = NULL;
    char *pSuffixTail = NULL;
    char *pFoundTail = NULL;

    if (psPattern == NULL)
        return gERROR_ARGUMENT_INCORRECT;

    memset(gnGoodSuffixArr, 0, nPatternLen * sizeof(int));
    nPatternLen = strnlen(psPattern, gPATTERN_MAX_LEN);

    // 1. calculating longest prefix suffix with KMP
    gnGoodSuffixArr[0] = 0;
    // 1.1 for loop each index of the pattern, find it's lps
    for (i = 1; i < nPatternLen; ++i)
    {
        // 1.2 initialize j as the previous index lps value add 1
        j = gnGoodSuffixArr[i - 1];

        // 1.3 while loop to find the previous same character's lps
        //      or not found (j = 0)
        while (j > 0 && psPattern[i] != psPattern[j])
            j = gnGoodSuffixArr[j - 1];

        // 1.4 if psPattern[i] and psPattern[j] matched,
        //      meaning that we could skip one more character
        if (psPattern[i] == psPattern[j])
            ++j;

        // 1.5 assign the found value
        gnGoodSuffixArr[i] = j;
    }
    K = gnGoodSuffixArr[nPatternLen - 1];

    // 2. calculate good suffix
    memset(gnGoodSuffixArr, 0, nPatternLen * sizeof(int));
    nMaxMove = nPatternLen - K;
    for (i = nPatternLen - 2; i >= 0; --i)
    {
        pSuffixTail = psPattern + i + 1;
        pFrontTail = psPattern;
        while ((pFoundTail = strstr(pFrontTail, pSuffixTail)) != NULL)
        {
            if (pFoundTail < pSuffixTail)
                pFrontTail = pFoundTail + 1;
            else
                break;
        }

        // can't find suffix tail anymore
        if (pFrontTail == psPattern)
            gnGoodSuffixArr[i] = nMaxMove;
        else
        {
            --pFrontTail;
            gnGoodSuffixArr[i] = pSuffixTail - pFrontTail;
        }
    }

    return gSUCCESS;
}

 void printGoodSuffix(int nPatternLen)
 {
    int i = 0;

    for (i = 0; i < nPatternLen; ++i)
        printf("%d ", gnGoodSuffixArr[i]);

    printf("\n");
 }

int bmSearch(char* psPattern, char *psBibleContent)
{
    int nBibleIdx = 0, nPatternIdx = 0;
    int nPatternLen = 0, nBibleLen = 0;
    int nResult = 0, nMove = 0;
    int nBadMove = 0, nGoodMove = 0;
    int ret = 0;
    unsigned char uKey = 0;

    // checks to make sure pass in variable is valid
    if (psPattern == NULL || psBibleContent == NULL)
        return 0;

    nPatternLen = strnlen(psPattern, gPATTERN_MAX_LEN);
    nBibleLen = strnlen(psBibleContent, gBIBLE_MAX_LEN);

    // 1. create bad character table
    ret = createBadCharTbl(psPattern);
    if (ret < 0)
        printf(gERROR_MSG_PREPROCESSING_FAILED, gBM_SEARCH_NAME, ret);

    // 2. create good suffix table
    createGoodSuffixTbl(psPattern);

    // 3. while loop and start comparing pattern and text
    while (nBibleIdx < nBibleLen)
    {
        // 3.1 comparing the tail until the the psPattern ends
        while (psBibleContent[nBibleIdx] == psPattern[nPatternIdx])
        {
            if (nPatternIdx == 0)
            {
                ++nResult;
                nMove = nPatternLen;
                break;
            }
            --nBibleIdx;
            --nPatternIdx;
        }

        // 3.2 calculate bad char table shift value
        uKey = psBibleContent[nBibleIdx];
        nBadMove = gnBadCharArr[uKey];
        while (nBadMove != -1 && nBadMove > nBibleIdx)
            nBadMove = gnNextBadCharArr[nBadMove];

        if (nBadMove == -1)
            nBadMove = nPatternLen;
        else
            nBadMove = nPatternIdx - nBadMove;

        // 3.3 retrieve goodmove
        nGoodMove = gnGoodSuffixArr[nPatternIdx];
        nMove = (nGoodMove > nBadMove) ? nGoodMove : nBadMove;

        nBibleIdx = nBibleIdx + nMove + (nPatternLen - 1 - nPatternIdx);
        nPatternIdx = nPatternLen - 1;
    }

    return nResult;
}