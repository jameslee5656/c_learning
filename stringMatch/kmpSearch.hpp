// KMP function 完整步驟
// 傳入參數: char *psPattern, char *psBible
// 1.	建立參數:
// nPatternIndex = 0, nPatternIndex 代表 pattern 現在的位置
// nBibleIndex = 0, nBibleIndex 代表 bible 現在的位置
// nResult = 0, nResult代表 bible 當中 match 的次數
// 2.	為 pattern 建立 next 表
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

#include "definitions.hpp"

int createLpsTable(char *psPattern);

int kmpSearch(char *psPattern, char *psBible);
