#include "stdio.h"
#include "string.h"

#include "bibleSearch.hpp"

static int gnNextArr[gPATTERN_MAX_LEN];

int createNextTable(char *psPattern)
{
    int i = 0, j = 0;
    int nPatternLen = 0;

    if (psPattern == NULL)
        return gERROR_ARGUMENT_INCORRECT;

    // Initialize patternLen, and lps
    nPatternLen = strnlen(psPattern, gPATTERN_MAX_LEN - 1);
    if (nPatternLen == 0)
        return gERROR_ARGUMENT_INCORRECT;

    if (nPatternLen > gPATTERN_MAX_LEN)
        return gERROR_PATTERN_TOO_LONG;

    memset(gnNextArr, 0, gPATTERN_MAX_LEN);

    // 1. for loop each index of the pattern, find it's lps
    for (i = 1; i < nPatternLen; ++i)
    {
        // 2. Initialize j as the previous lps value
        j = gnNextArr[i - 1];

        // 3. jumping to longest previous location
        while (j > 0 && psPattern[i] != psPattern[j])
            j = gnNextArr[j - 1];

        // 4. if the index match, our prefix and suffix increased
        if (psPattern[i] == psPattern[j])
            ++j;

        gnNextArr[i] = j;
    }

    // 5. move to the right to create next table, and set the first one as -1
    memmove(&gnNextArr[1], gnNextArr, nPatternLen - 1);
    gnNextArr[0] = -1;

    return gSUCCESS;
}

// 傳入參數: char *psPattern, char *psBible
int kmpSearch(char *psPattern, char *psBibleContent)
{
    // 1. 建立參數:
    int nPatternIdx = 0, nBibleIdx = 0;
    int nPatternLen = 0, nBibleLen = 0;
    int nRet = 0, nResult = 0;

    if (psPattern == NULL || psBibleContent == NULL)
        return gERROR_ARGUMENT_INCORRECT;

    nPatternLen = strnlen(psPattern, gPATTERN_MAX_LEN);
    nBibleLen = strnlen(psBibleContent, gPATTERN_MAX_LEN);

    if (nPatternLen == 0 || nBibleLen == 0)
        return gERROR_ARGUMENT_INCORRECT;

    // 2. 為 pattern 建立 next 表
    nRet = createNextTable(psPattern);
    if (nRet < 0)
    {
        printf(gERROR_MSG_PREPROCESSING_FAILED, gKMP_SEARCH_NAME, nRet);
        return nRet;
    }

    // 3. while loop until Bible end
    nBibleIdx = 0;
    nPatternIdx = 0;
    while (psBibleContent[nBibleIdx] != '\0')
    {
        // 4.1. if (nBibleIdx < 0) or (psPattern[nPatternIdx] == psBible[nBibleIdx])
        // ++ both of the index
        if ((nPatternIdx < 0) || (psPattern[nPatternIdx] == psBibleContent[nBibleIdx]))
        {
            ++nBibleIdx;
            ++nPatternIdx;

            // 4.1.1 found pattern
            if (nPatternIdx >= nPatternLen)
            {
                ++nResult;
                nPatternIdx = gnNextArr[nPatternIdx];
            }
        }
        // 4.2.  else
        // nPatternIndex = gnNextArr[nPatternIndex]
        else
            nPatternIdx = gnNextArr[nPatternIdx];
    }

    //  5. return result
    return nResult;
}