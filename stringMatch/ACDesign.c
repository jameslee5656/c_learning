#define ASCII_NUM           255
#define TREE_TRACE_SHIFT    1

typedef struct _node_t
{
    int isLeaf;
    int nPattern; // which pattern index it is
    char *content;
    struct _node_t *link[ASCII_NUM];
    struct _node_t *failureLink;
} node;

int buildTree(node* pRoot, char *pattern)
{
    // 1. check pattern is not empty
    if(1)
    {}

    // 2. check pRoot exist or not
    if (pRoot == NULL)
    {}
    // ptr = pRoot

    // 3. 找尋已存在的節點
    for(;;)
    {
        // 3.1 該字節點存在
        if(exist == true)
        {
            // ptr = current node
        }
        // 3.2 該字節點不存在
        else
        {
            // 建立節點並初始化
            // ptr->next = newNode
        }
    }

    // 4. 處理結尾node
    // ptr->isLeaf = 1
    // ptr->nPattern = i;
}

node* findPrefix(node *pRoot, char* pattern, int subHead, int subTail)
{
    // 1. Initialize ptr = pRoot

    // 2. 在 tree 找 sub pattern
    for(i = subHead; i <= subTail; ++i)
    {
        // ptr = ptr->next

        // 2.1 不是結尾且節點存在
        if(1)
        {
            // ptr = ptr->next
        }
        // 2.2 是結尾且節點存在
        else if(1)
        {
            // return ptr;
        }
        // 2.3 sub pattern 沒走完，節點不存在
        else
        {
            // return pRoot;
        }
    }
}

int buildFailureLink(node* pRoot, char *pattern)
{
    node *tailNode = NULL;
    int i = 0, j = 0, k = 0;

    subTail = strlen(pattern);

    // 1. 從pattern的第二字元開始找 pattern [i ~ j] 是否為他人的 prefix
    // i 是 substring 的尾巴
    for (i = 1; i < subTail; ++i)
    {
        // 2. 找目前 substring last node
        for ()
        {
            // 將 tailNode 指向 pattern 第 i 個
        }

        // 3. j 是 substring 的頭
        for (j = 1; j <= i; ++j)
        {
            // 在 tree 找 pattern [i ~ j]
            for (k = j; k <= i; ++k)
            {
                // 3.1 取的 substring 的 failure link
                tailNode->failureLink = findPrefix(root, pattern, j, i);
            }
        }
        // move tailNode
    }
}

int traversal(node* pRoot, char *text)
{
    // 1. 搜尋整份文件
    while ()
    {
        // 2. if (ptr->next[c] == NULL)
        {
            // 2.1 if ptr == pRoot, move on to next char

            // 2.2 else ptr = ptr->failure
        }
        // 3. else have the next point
        {
            // 3.1 移動到下一個點
            ptr = ptr->next[c];

            // 3.2 如果是最後一個點，pattern 的結果 +1
            // if (ptr->isLeaf)
                // result++


            // 3.3 move on to the next char of the text
        }
    }
}

void acSearch(char **patternArray, int patternArraySize, char *bibleContent)
{
    int nBibleLen = strlen(bibleContent);
    node *treeRoot;

    // 1. build tree with every pattern in patternArray
    for (;;)
    {
        buildTree(patternArray[i], treeRoot);
    }

    // 2. build failure link
    for(;;)
    {
        buildFailureLink(patternArray[i]);
    }

    // 3. traverse the tree with bible content
    Traversal(treeRoot, bibleContent)
}