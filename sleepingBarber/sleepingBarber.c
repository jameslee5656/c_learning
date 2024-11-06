#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "sleepingBarber.h"


#define gnBARBER_NUM    3
#define gnTOTAL_SEATS   10

int gnFreeSeat = 10;
pthread_mutex_t gSofaMutex = PTHREAD_MUTEX_INITIALIZER;


// ## Main Thread
int main()
{
    int i = 0, x = 100;
    int nAction = 0;
    char aInput[20];

    pthread_t aBarberThread[gnBARBER_NUM];

// 1. 建立三個 Barber threads,
//    1 個 IPC Queue, eventQueue, 並且清空

    for(i = 0; i < gnBARBER_NUM; ++i)
    {
        if(pthread_create(&aBarberThread[i], NULL, barberProcess, (void *)(&x)) != 0)
            goto errexit;
    }

// 2. while 等待 input
    while(1)
    {
        printf("Input 1, 動作1: customer comes\n");
        printf("Input 2, 動作2: close door\n");
        scanf("%s", aInput);
        if(strlen(aInput) > 1 || aInput[0] != 1 || aInput[0] != '2')
        {
            printf("Wrong input, please input '1' or '2'\n");
            continue;
        }




//     2.1 有客人上門, input 動作 1, 同時輸入所需秒數,

//         2.1.1 lock gSofaMutex

//         2.1.2 如果 gnFreeSeat 沒有位置了 (<= 0),
//             unlock gSofaMutex,
//             放棄這位customer, continue

//         2.1.3 建立新的 eventMessage_t, newMsg
//             初始化 newMsg 的參數
//                 eventType = customer
//                 nNeedSecond = 所需秒數

//         2.1.4 gnFreeSeat -= 1

//         2.1.5 unlock gSofaMutex

        // msgsnd eventQueue 要放在 lock 的外面
        // 這樣 Barber thread 才可以順利 recv
//         2.1.6 把建立的 newMsg 放入 eventQueue 當中

//     2.2 input 動作 2

//     2.2.1 lock gSofaMutex
//         gnFreeSeat = 10
//         unlock gSofaMutex

//     2.2.2 清空 eventQueue

//     2.2.3 for loop 3 次 (3 個 barber threads)

//         2.2.3.1 建立新的 eventMessage_t, newMsg
//                 初始化 newMsg 的參數
//                     eventType = ending
//                     nNeedSecond = 0

        // msgsnd eventQueue 要放在 lock 的外面
        // 這樣 Barber thread 才可以順利 recv
//         2.2.3.2 建立的 newMsg 放入 eventQueue 當中

        // 2.2.4 timeout pthread join, with some timeout
            // otherwise kill the process
    }

errexit:

    for(i = 0; i < gnBARBER_NUM; ++i)
    {
        pthread_join(aBarberThread[i], NULL);
    }

    return 0;
}


void *barberProcess(void *arg)
{
}
// ## Barber Thread
// 1. 建立一個 IPC queue, eventQueue
//     int nRecvResult = 0;

// 2. while loop,
//     nRecvResult = msgrcv eventQueue

//     2.1 lock gSofaMutex

//     2.2 msgrcv 各項檢查
//         如果 nRecvResult <= 0

//         2.2.1 檢查 msgrcv 的資訊是否是剛好"正在"清理 eventQueue, 如果是繼續等待下一訊息
//             if(errno == E2BIG && gnFreeSeat >= 10)
//                 continue

//         2.2.2 如果是其他種狀況, print 結果, unlock gSofaMutex, end thread

//     2.3 if newMsg.eventType_t == customer

//         2.3.1 gnFreeSeat += 1

//         2.3.2 unlock gSofaMutex

//         2.3.3 wait for newMsg.nNeedSecond

//     2.4 else if newMsg.eventType_t == ending

//         2.4.1 unlock gSofaMutex

//         2.4.1 end thread

// [Requirements]
// * 3 Barbar thread -> no bust waiting
// * Gracefully shutdown
// * nNeedSeconds > 0 && nNeedSeconds <= 60

// enum eventType_t
// {
//     customer,
//     ending,
// }

// struct eventMessage_t
// {
//     eventType_t eventType;
//     int nNeedSeconds;
// };
