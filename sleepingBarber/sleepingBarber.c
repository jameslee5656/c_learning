#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "definitions.h"
#include "barberWorkingThread.h"

// ## Main Thread
int main()
{
    int i = 0;
    int nAction = 0, nSeconds = 0;
    int nCustomerId = 0;
    char acInput[20];
    size_t uInputSize = 0;

    int anBarberId[gnBARBER_NUM];
    pthread_t aBarberThread[gnBARBER_NUM];
    key_t eventQueueKey;
    int nEventQueueId = 0;
    struct eventMessage_t newMsg;
    struct timespec threadJoinTimeout;

    ////////////////////////////////////////////
    // 1. 建立三個 Barber threads,
        // 1 個 IPC Queue, eventQueue, 並且清空,
        // 初始化 gSofaMutex
    ////////////////////////////////////////////

    eventQueueKey = ftok(gsEVENT_QUEUE_NAME, 65);
    if((nEventQueueId = msgget(eventQueueKey, 0666 | IPC_CREAT)) < 0)
    {
        printf(ERROR_EVENT_QUEUE_CREATION_FAILURE);
        goto errexit;
    }

    for(i = 0; i < gnBARBER_NUM; ++i)
    {
        anBarberId[i] = i + 1;
        if(pthread_create(
            &aBarberThread[i], NULL, barberWorkingThread, (void*)(&anBarberId[i])) != 0)
        {
            printf(ERROR_PTHREAD_CREATION_FAILURE);
            goto errexit;
        }
    }

    pthread_mutex_init(&gSofaMutex, NULL);

    ////////////////////////////////////////////
    // 2. while 等待 input
    ////////////////////////////////////////////
    while(1)
    {
        printf("*** 開店中 ***\n");
        printf("輸入 1, 動作1: 顧客上門\n");
        printf("輸入 2, 動作2: 關店\n");
        scanf("%s", acInput);
        uInputSize = strlen(acInput);
        if(uInputSize > 1 || uInputSize <= 0 || (acInput[0] != '1' && acInput[0] != '2'))
        {
            printf("錯誤輸入, 請輸入 '1' 或 '2'\n");
            while(getchar() != '\n');
            continue;
        }
        nAction = acInput[0] - '0';

        ////////////////////////////////////////////
        // 2.1 有客人上門, input 動作 1, 同時輸入所需秒數,
        ////////////////////////////////////////////
        switch(nAction)
        {
        case 1:
            printf("輸入一數字, 1 ~ 60, 是這位客人需要理髮的時間\n");
            scanf("%s", acInput);
            uInputSize = strlen(acInput);

            // checking the size and the first digits of the number
            if(uInputSize > 2 || acInput[0] < '0' || acInput[0] > '9')
            {
                printf("錯誤輸入, 請輸入 1 ~ 60 的數字\n");
                while(getchar() != '\n');
                continue;
            }
            nSeconds = acInput[0] - '0';

            // getting the second digits
            if(uInputSize > 1)
            {
                if(acInput[1] < '0' || acInput[1] > '9')
                {
                    printf("錯誤輸入, 請輸入 1 ~ 60 的數字\n");
                    while(getchar() != '\n');
                    continue;
                }
                nSeconds *= 10;
                nSeconds += acInput[1] - '0';

                if(nSeconds < 1 || nSeconds > 60)
                {
                    printf("錯誤輸入, 請輸入 1 ~ 60 的數字\n");
                    while(getchar() != '\n');
                    continue;
                }
            }

            ++nCustomerId;
            printf("客人[%d]上門\n", nCustomerId);
            ////////////////////////////////////////////
            // 2.1.1 lock gSofaMutex
            ////////////////////////////////////////////
            pthread_mutex_lock(&gSofaMutex);

            ////////////////////////////////////////////
            // 2.1.2 如果 gnFreeSeat 沒有位置了 (<= 0),
                // unlock gSofaMutex,
                // 放棄這位customer, continue
            ////////////////////////////////////////////
            if(gnFreeSeat <= 0)
            {
                pthread_mutex_unlock(&gSofaMutex);
                printf("沙發滿了，客人[%d]直接離開\n", nCustomerId);
                continue;
            }

            ////////////////////////////////////////////
            // 2.1.3 建立新的 eventMessage_t, newMsg
                // 初始化 newMsg 的參數
                    // eventType = customer
                    // nNeedSecond = 所需秒數
            ////////////////////////////////////////////
            newMsg.mtype = gnEVENT_MTYPE;
            newMsg.eventType = customer;
            newMsg.nNeedSeconds = nSeconds;

            ////////////////////////////////////////////
            // 2.1.4 gnFreeSeat -= 1
            ////////////////////////////////////////////
            if(gnFreeSeat > 0)  gnFreeSeat -= 1;

            ////////////////////////////////////////////
            // 2.1.5 unlock gSofaMutex
            ////////////////////////////////////////////
            pthread_mutex_unlock(&gSofaMutex);

            ////////////////////////////////////////////
            // 2.1.6 把建立的 newMsg 放入 eventQueue 當中
                // msgsnd eventQueue 要放在 lock 的外面
                // 這樣 Barber thread 才可以順利 recv
            ////////////////////////////////////////////
            if(msgsnd(nEventQueueId, &newMsg, sizeof(newMsg), 0) < 0)
            {
                printf(ERROR_EVENT_QUEUE_SEND_FAILURE);
                continue;
            }
            break;
        ////////////////////////////////////////////
        // 2.2 input 動作 2
        ////////////////////////////////////////////
        case 2:
            pthread_mutex_lock(&gSofaMutex);
            ////////////////////////////////////////////
            // 2.2.1 lock gSofaMutex
                // gnFreeSeat = 10
                // unlock gSofaMutex
            ////////////////////////////////////////////
            gnFreeSeat = 10;
            pthread_mutex_unlock(&gSofaMutex);

            ////////////////////////////////////////////
            // 2.2.2 清空 eventQueue
            ////////////////////////////////////////////
            while(msgrcv(nEventQueueId, &newMsg, sizeof(newMsg), gnEVENT_MTYPE, IPC_NOWAIT) == 0)
            {}

            ////////////////////////////////////////////
            // 2.2.3 for loop 3 次 (3 個 barber threads)
            ////////////////////////////////////////////
            for(i = 0; i < gnBARBER_NUM; ++i)
            {
                // 2.2.3.1 建立新的 eventMessage_t, newMsg
                    // 初始化 newMsg 的參數
                        // eventType = ending
                        // nNeedSecond = 0
                newMsg.mtype = gnEVENT_MTYPE;
                newMsg.eventType = ending;
                newMsg.nNeedSeconds = 0;

                ////////////////////////////////////////////
                // 2.2.3.2 建立的 newMsg 放入 eventQueue 當中
                    // msgsnd eventQueue 要放在 lock 的外面
                    // 這樣 Barber thread 才可以順利 recv
                ////////////////////////////////////////////
                if(msgsnd(nEventQueueId, &newMsg, sizeof(newMsg), 0) < 0)
                {
                    --i;
                    printf(ERROR_EVENT_QUEUE_SEND_FAILURE);
                    continue;
                }
            }
            goto errexit;

        default:
            printf("錯誤輸入, 請輸入 '1' 或 '2'\n");
            while(getchar() != '\n');
            break;
        } // end of switch(nAction)
    } // end of while(1)

errexit:
    ////////////////////////////////////////////
    // 2.2.4 timeout pthread join, with some timeout
        // otherwise kill the process
    ////////////////////////////////////////////
    threadJoinTimeout.tv_sec += 10;
    threadJoinTimeout.tv_nsec = 0;
    for(i = 0; i < gnBARBER_NUM; ++i)
    {
        pthread_join(aBarberThread[i], NULL);
        // pthread_timedjoin_np(&aBarberThread[i], NULL, &threadJoinTimeout);
    }

    printf("關店\n");

    pthread_mutex_destroy(&gSofaMutex);

    msgctl(nEventQueueId, IPC_RMID, NULL);

    return 0;
}