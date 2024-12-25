#include <cstdio>

#include "kmpSearch.hpp"


int main()
{
// 1.	開啟 dict.txt, bible.txt 兩個檔案，並取得 file descriptor
// 2.	讀取每一行的 dict.txt, 並將每一行的單字放入 patternArray 當中, 且pattern 結尾都有 ‘\0’
// 3.	讀取bible.txt, 並將全部內容放進 bibleString 當中, bibleString 結尾有 ‘\0’
// 4.	分別 initialize kmpResult, bmResult, acResult 紀錄每一個 pattern 用不同 search 後的結果
// 5.	for  loop 每一個 pattern，將 pattern, bibleString傳入 kmpSearch function 當中, 並將每一個結果記錄在 kmpResult 中
// 6.	for  loop 每一個 pattern，將 pattern, bibleString傳入 bmSearch function 當中, 並將每一個結果記錄在 bmResult 中
// 7.	將 patternArray, bibleString, acResult傳入 acSearch function
// acSearch 會把最後解果放入 acResult 當中
// 8.	比較 kmpResult, bmResult, acResult, 是否一樣
// 9.	釋放 patternArray, bibleString, kmpResult, bmResult, acResult 的記憶體
// close dict.txt, bible.txt 的 file descriptor

}