#include <string.h>
#include <stdio.h>

#include "bmSearch.hpp"
#include "definitions.hpp"

static int gnBadCharArr[26];
static int gnNextBadCharArr[gPATTERN_MAX_LEN];
static int gLPS[gPATTERN_MAX_LEN];

void createBadCharTbl(char *psPattern)
{
    int i = 0;
    int nPatternLen = 0;
    int nPos = 0;

    nPatternLen = strnlen(psPattern, gPATTERN_MAX_LEN);
    memset(gnBadCharArr, -1, 26 * sizeof(int));
    memset(gnNextBadCharArr, -1, gPATTERN_MAX_LEN * sizeof(int));

    // 1. for loop each character in each position of pattern
    for (i = 0; i < nPatternLen; ++i)
    {
        // 2. gnBadCharArr[26] pointing to the first position
        nPos = gnBadCharArr[psPattern[i] - 'a'];

        if (nPos == -1)
        {
            gnBadCharArr[psPattern[i] - 'a'] = i;
            continue;
        }

        // 3. use gnNextBadCharArr pointing to the next position that have psPattern[i]
        while (gnNextBadCharArr[nPos] != -1)
            nPos = gnNextBadCharArr[nPos];

        gnNextBadCharArr[nPos] = i;
    }

    return;
}

// for debug bad char table purpose
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

void createGoodSuffixTbl(char *psPattern)
{
    int i = 0, j = 0;
    int K = 0;
    int nPatternLen = 0;

    nPatternLen = strnlen(psPattern, gPATTERN_MAX_LEN);

    // 1. calculating longest prefix suffix with KMP
    gLPS[0] = 0;
    // 1.1 for loop each index of the pattern, find it's lps
    for (i = 1; i < nPatternLen; ++i)
    {
        // 1.2 initialize j as the previous index lps value add 1
        j = gLPS[i - 1] + 1;

        // 1.3 while loop to find the previous same character's lps
        //      or not found (j = 0)
        while (j > 0 && psPattern[i] != psPattern[j])
            j = gLPS[j - 1];

        // 1.4 if psPattern[i] and psPattern[j] matched,
        //      meaning that we could skip one more character
        if (psPattern[i] == psPattern[j])
            ++j;

        // 1.5 assign the found value
        gLPS[i] = j;
    }
    K = gLPS[nPatternLen - 1];








    return;
}

int bmSearch(char* psPattern, char *psBibleContent)
{
    int i = 0, j = 0;
    int nPos = 0;
    int nPatternLen = 0;

    nPatternLen = strnlen(psPattern, gPATTERN_MAX_LEN);

    // 1. create bad character table
    createBadCharTbl(psPattern);

    // 2. create good suffix table
    createGoodSuffixTbl(psPattern);




    return gSUCCESS;
}