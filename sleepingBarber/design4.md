## Main Thread

#define gBARBER_NUM 3
#define gSOFA_SIZE  10
int gSofa[gSOFA_SIZE];
int gSofaFreeSize = 0;

1. 建立三個 Barber threads,
    g_c, 清空 gSOFA, gSofaFreeSize = gSOFA_SIZE;

2. while loop 輸入動作

    2.1 動作1: customer

        2.1.1 如果 gSofaFreeSize < 0 (沙發沒有為)

