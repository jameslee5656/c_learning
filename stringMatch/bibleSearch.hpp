#ifndef BIBLESEARCH_HPP
#define BIBLESEARCH_HPP

#define gSUCCESS                    1
#define gERROR_BASE                 0
#define gERROR_GENERAL              -1
#define gERROR_ARGUMENT_INCORRECT   -2
#define gERROR_MALLOC_FAILED        -3
#define gERROR_PATTERN_TOO_LONG     -4
#define gERROR_AC_TRAVERSAL_FAILED  -5

#define gPATTERN_MAX_LEN        64
#define gPATTERN_ARR_MAX_SIZE   70000
#define gBIBLE_MAX_LEN          5000000
#define gASCII_NUM              255
#define gBUFFER_MAX_SIZE        1024

#define gERROR_MSG_UNABLE_OPEN_FILE "[Error] Unable to open File %s\n"
#define gERROR_MSG_PATTERN_ARR_FULL "[Error] Pattern array size > gPATTERN_ARR_MAX_SIZE, unable read all pattern\n"
#define gERROR_MSG_BIBLE_CONTENT_FULL "[Error] Bible content > gTEXT_MAX_LEN, unable read full bible content\n"
#define gERROR_MSG_SEARCH_FAILED "[Error] %s failed at patternIdx:%d, return:%d \n"
#define gERROR_MSG_SEARCH_FAILED_WITHOUT_PATTERN_IDX "[Error] %s failed, return:%d\n"
#define gERROR_MSG_AC_SEARCH_BUILD_FAILED "[Error] AC Search build tree failed at pattern %d\n"
#define gERROR_MSG_PREPROCESSING_FAILED "[Error] %s preprocessing failed, errocode:%d\n"
#define gERROR_MSG_MALLOC_FAILED "[Error] malloc failed\n"

#define gKMP_SEARCH_NAME "kmpSearch"
#define gBM_SEARCH_NAME  "bmSearch"
#define gAC_SEARCH_NAME  "acSearch"

int kmpSearch(char *psPattern, char *psBible);

int bmSearch(char* psPattern, char* psBibleContent);

int acSearch(char **psPatternArray, int nPatternArraySz, char *psBibleContent, int *acResult);

#endif // BIBLESEARCH_HPP