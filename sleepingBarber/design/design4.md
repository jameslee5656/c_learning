#define gBARBER_NUM 3
#define gSOFA_SIZE  10

int gaSofa[gSOFA_SIZE];
int gnSofaUsedSize = 0;
CRITICAL_SECTION    g_cs;

## main thread
1. 建立三個 Barber threads,
    g_cs, 清空 gaSOFA, gnSofaUsedSize = gSOFA_SIZE;
    nCustomerId = 0;

2. while 等待 CUSTOMER_EVENT, CLOSE_EVENT

    2.1 CUSTOMER_EVENT
        ++nCustomerId;

        2.1.1 如果 gnSofaUsedSize >= gSOFA_SIZE (沙發沒有空位) (用 g_cs 保護起來)
            請客人直接離開

        2.1.2 如果 sofa 還有位置,

            2.1.2.1 把客人放在 sofa 的最後面 , ++gSofaUsedSize (用 g_cs 保護起來)

            2.1.2.2 ReleaseSemphore

    2.2 CLOSE_EVENT

        2.2.1 把 sofa 清空, gSofaUsedSize = 0 (用 g_cs 保護起來)

        2.2.2 等待 3 個 barber thread 做完, join

        2.2.3 關門

## barber thread
1. 等待 CLOSE_EVENT 跟 SEMAPHORE (while loop)

    1.1 CLOSE_EVENT
        Barber 結束 thread

    1.2 SEMAPHORE

        1.2.1 從 Sofa 拿出一人,
            --gSofaUsedSize;
            位移 gnSofa (由 i = 0 ~ gSOFA_SIZE - 2, gaSofa[i] = gaSofa[i + 1])
            (這些動作都要用 g_cs 保護)

        1.2.2 剪頭髮

        1.2.3 剪完頭髮 continue while loop



