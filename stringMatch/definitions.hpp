#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#define gSUCCESS            1
#define gERROR_BASE         0
#define gERROR_GENERAL      -1

#define gPATTERN_MAX_LEN        64
#define gPATTERN_ARR_MAX_SIZE   70000
#define gTEXT_MAX_LEN           5000000

#define gERROR_MSG_UNABLE_OPEN_FILE "[Error] Unable to open File %s\n"
#define gERROR_MSG_PATTERN_ARR_FULL "[Error] Pattern array size > gPATTERN_ARR_MAX_SIZE, unable read all pattern\n"
#define gERROR_MSG_BIBLE_CONTENT_FULL "[Error] Bible content > gTEXT_MAX_LEN, unable read full bible content\n"
#define gERROR_MSG_SEARCH_FAILED "[Error] %s failed at pattern %d\n"

#define gKMP_SEARCH_NAME "kmpSearch"
#define gBM_SEARCH_NAME  "bmSearch"

#endif // DEFINITIONS_HPP