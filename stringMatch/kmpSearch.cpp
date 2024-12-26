// KMP function 完整步驟
#include "string.h"
#include "kmpSearch.hpp"

int next[PATTERN_MAX_LEN];

int createNextTable(char *psPattern)
{
    int i, j;
    int nPatternLen = 0;

    // Initialize patternLen, and lps
    nPatternLen = strnlen(psPattern, PATTERN_MAX_LEN + 10);
    if (nPatternLen > PATTERN_MAX_LEN)
        return ERROR_GENERAL;

    memset(next, 0, PATTERN_MAX_LEN);

    // 1. for loop each index of the pattern, find it's lps
    for (i = 1; i < nPatternLen; ++i)
    {
        // 2. Initialize j as the previous lps value
        j = next[i - 1];

        // 3. jumping to longest previous location
        while (j > 0 && psPattern[i] != psPattern[j])
            j = next[j - 1];

        // 4. if the index match, our prefix and suffix increased
        if (psPattern[i] == psPattern[j])
            ++j;

        next[i] = j;
    }

    // 5. move to the right to create next table, and set the first one as -1
    memmove(next, &next[1], nPatternLen);
    next[0] = -1;
}

// 傳入參數: char *psPattern, char *psBible
int kmpSearch(char *psPattern, char *psBible)
{
    // 1. 建立參數:
    int nPatternIdx = 0, nBibleIdx = 0;
    int nPatternLen, nBibleLen;

    nPatternLen  = strnlen(psPattern, PATTERN_MAX_LEN);
    nBibleLen = strnlen(psBible, PATTERN_MAX_LEN);

    // 2. 為 pattern 建立 next 表
    createNextTable(psPattern);

    // 3. while loop until Bible end
    while (psBible[nBibleIdx] != '\0')
    // 4.1. if (nBibleIndex < 0) or (pcPattern[nPatternIndex] == pcBible[nBibleIndex])
    //       ++nBibleIndex;
    //       ++ nPatternIndex;
    //         4.1.1. pcBible[nBibleIndex] == end
    // 	      ++result
    //             nPatternIndex = next[nPatternIndex]
    // 4.2.  else
    //       nPatternIndex = next[nPatternIndex]
    //  5. return result

}


// nPatternIndex = 0, nPatternIndex 代表 pattern 現在的位置
// nBibleIndex = 0, nBibleIndex 代表 bible 現在的位置
// nResult = 0, nResult代表 bible 當中 match 的次數
// 3.	for loop pcBible[nBibleIndex ] != ‘\0’
// 4.1. if (nBibleIndex < 0) or (pcPattern[nPatternIndex] == pcBible[nBibleIndex])
//       ++nBibleIndex;
//       ++ nPatternIndex;
//         4.1.1. pcBible[nBibleIndex] == end
// 	      ++result
//             nPatternIndex = next[nPatternIndex]
// 4.2.  else
//       nPatternIndex = next[nPatternIndex]
//  5. return result
