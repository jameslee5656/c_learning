#include "stdio.h"
#include "string.h"

#include "kmpSearch.hpp"
#include "definitions.hpp"

static int gnNextArr[gPATTERN_MAX_LEN];

int createNextTable(char *psPattern)
{
    int i, j;
    int nPatternLen = 0;

    // Initialize patternLen, and lps
    nPatternLen = strnlen(psPattern, gPATTERN_MAX_LEN + 10);
    if (nPatternLen > gPATTERN_MAX_LEN)
        return gERROR_GENERAL;

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
int kmpSearch(char *psPattern, char *psBible)
{
    // 1. 建立參數:
    int nPatternIdx = 0, nBibleIdx = 0;
    int nPatternLen, nBibleLen;
    int nResult = 0;

    nPatternLen  = strnlen(psPattern, gPATTERN_MAX_LEN);
    nBibleLen = strnlen(psBible, gPATTERN_MAX_LEN);

    // 2. 為 pattern 建立 next 表
    createNextTable(psPattern);

    // printf("%s", psPattern);
    // for (nPatternIdx = 0; nPatternIdx < nPatternLen; ++nPatternIdx)
        // printf(" %d", next[nPatternIdx]);
    // printf("\n");

    // 3. while loop until Bible end
    nBibleIdx = 0;
    nPatternIdx = 0;
    while (psBible[nBibleIdx] != '\0')
    {
        // printf("%d %d\n", nBibleIdx, nPatternIdx);
        // 4.1. if (nBibleIdx < 0) or (psPattern[nPatternIdx] == psBible[nBibleIdx])
            // ++ nBibleIdx;
            // ++ nPatternIdx;
        if ((nPatternIdx < 0) || (psPattern[nPatternIdx] == psBible[nBibleIdx]))
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
        // nPatternIndex = next[nPatternIndex]
        else
            nPatternIdx = gnNextArr[nPatternIdx];
    }

    //  5. return result
    return nResult;
}