# String Match

## KMP  
Big Design: 
把要搜尋的 pattern substring 先預處理，當不符合的時候可以把最長的 Prefix 放到自己的位子  

Example:  
搜尋pattern: abcdabxy  
字串：abcdabcdabcdabxy

abcdabcdabcdabxy  
abcdabxy  
      ^does not match  
    abcdabxy  
      ^把字串移動到 index 2  
所以 preprocess 字串 preprocess[6] (x) = 2  

* 建立 preprocess array  
Big Design:  
由現在的字串去推下一個 index 最長的 prefix index 是誰  

0123456  
abcdabxy ->  
     ^ 當 i = 5, 我推 i + 1 = 6 最長的 prefix 是前一個 substring ab + 1
     preprocess[6] = 1 (index of first b) + 1
        
1. Intialize: preprocess[0] = -1  
2. for loop i = 0 ~ n - 2  
    3. 預設 preprocess[i + 1] = preprocess[i] + 1 -> aa 的這種狀況  
    4. 往前找 preprocess[i + 1] - 1 有沒有跟 s[i] 相同  
       有得話他的(preprocess[i + 1] - 1) preprocess + 1 就是尋找的值  
    while (preproces[i + 1] > 0 && s[i] != s[preprocess[i + 1] - 1])  
        preprocess[i + 1] = preprocess[preprocess[i + 1] - 1] + 1  

* KMP 比對
```
1. for pattern in dict:
    2. Initialize: 
    * p -> 指向 pattern 的指標, p = 0
    * 用上面的 algorithm 建立 preprocess array
    3. for char in bible
        if pattern[p] == char
            if p == pattern.end:
                ++result[pattern]
                p = preprocess[p]
            else
                ++p
        else
            p = preprocess[p]
```

## BM (Boyer-Moore) Search
* Big Design
案例：
pattern: tpabxab
serach string: abcdefghigtxabtpabxab

* Bad Character-> 不存在的 character 直接跳全部

abcdefg
tpabxab
      ^ g 不存在，直接跳 7

a -> 2, 5
abcdaab
tpabxab
     ^5
   tpabxab
跳 5 - 2 = 3

* Good Suffix rule-> 由尾巴決定要跳多遠
-> 自己不是自己的尾巴 abc, c 不是自己的尾巴

-> what is k? 指說 pattern prefix suffix 相同的部分
abcdab -> k = 2
tpabxab -> k = 0

tpabxab
      0
     ^ a 的尾巴是 b 跳 3 可以有前一個尾巴 
    ^ x 的尾巴是 ab

           0123456
           tpabxab
goodSuffix 7777330

tpatpabxab
tpabxab
    ^--mismatched jump 3, goodSuffix[4] = 3
   tpabxab

1. Initialize 
k = pattern 當中 prefix 和 suffix 相同的字數 -> 這其實是 KMP, finding the longest prefix of the suffix
goodSuffix(0, n-1) = k
goodSuffix[n - 1] = 0
2. for i = n - 2 ~ 0
    3. if



想請教兩個問題
(1) dict.txt, 單字後面的數字代表什麼意思
aa 0
aas 0
aalii 7

(2) 有大小寫的區分嗎？
God -> god 是同一個字嗎


## AC search

struct node