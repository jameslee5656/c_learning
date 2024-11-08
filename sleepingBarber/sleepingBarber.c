// to use pthread_timedjoin_np
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "sleepingBarberDefinitions.h"
#include "barberWorkingThread.h"

// Main Thread
int main()
{
    int i = 0, j = 0;
    int nAction = 0, nSeconds = 0;
    int nCustomerId = 0;
    char acInput[gnINPUT_BUFFER];
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
    eventQueueKey = ftok(gsEVENT_QUEUE_NAME, gnBARBER_PROJECT_NUM);
    if((nEventQueueId = msgget(eventQueueKey, 0666 | IPC_CREAT)) < 0)
    {
        printf(ERROR_EVENT_QUEUE_CREATION_FAILURE);
        goto errExit;
    }

    for(i = 0; i < gnBARBER_NUM; ++i)
    {
        anBarberId[i] = i + 1;
        if(pthread_create(
            &aBarberThread[i], NULL, barberWorkingThread, (void*)(&anBarberId[i])) != 0)
        {
            printf(ERROR_PTHREAD_CREATION_FAILURE);

            // Try to exit the thread that has already been created
            for(j = 0; j < i; ++j)
            {
                pthread_kill(aBarberThread[j], 9);
            }
            goto threadCreateErrExit;
        }
    }

    pthread_mutex_init(&gSofaMutex, NULL);

    ////////////////////////////////////////////
    // 2. while 等待 input
    ////////////////////////////////////////////
    while(1)
    {
        printf(INFO_BARBERSHOP_OPEN);
        printf(INFO_BARBER_ACTION_1);
        printf(INFO_BARBER_ACTION_2);
        scanf("%s", acInput);
        uInputSize = strlen(acInput);
        if(uInputSize > 1 || uInputSize <= 0 || (acInput[0] != '1' && acInput[0] != '2'))
        {
            printf(INFO_WRONG_INPUT_CHOOSE_ACTION);
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
            printf(INFO_INPUT_CUSTOMER_NEEDED_TIME);
            scanf("%s", acInput);
            uInputSize = strlen(acInput);

            // checking the size and the first digits of the number
            if(uInputSize > 2 || acInput[0] < '0' || acInput[0] > '9')
            {
                printf(INFO_WRONG_INPUT_CHOOSE_TIME);
                while(getchar() != '\n');
                continue;
            }
            nSeconds = acInput[0] - '0';

            // getting the second digits
            if(uInputSize > 1)
            {
                if(acInput[1] < '0' || acInput[1] > '9')
                {
                    printf(INFO_WRONG_INPUT_CHOOSE_TIME);
                    while(getchar() != '\n');
                    continue;
                }
                nSeconds *= 10;
                nSeconds += acInput[1] - '0';

                if(nSeconds < 1 || nSeconds > 60)
                {
                    printf(INFO_WRONG_INPUT_CHOOSE_TIME);
                    while(getchar() != '\n');
                    continue;
                }
            }

            ++nCustomerId;
            printf(INFO_CUSTOMER_ENTER, nCustomerId);
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
                printf(INFO_SOFA_IS_FULL, nCustomerId);
                continue;
            }

            ////////////////////////////////////////////
            // 2.1.3 建立新的 eventMessage_t, newMsg
                // 初始化 newMsg 的參數
                    // eventType = customer
                    // nNeedSecond = 所需秒數
            ////////////////////////////////////////////
            newMsg.mtype = gnEVENT_MTYPE;
            newMsg.mtext[0] = CUSTOMER;
            newMsg.mtext[1] = nSeconds;

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
            if(msgsnd(nEventQueueId, &newMsg, gnEVENT_MSG_BUFSIZE, 0) < 0)
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
                // gnFreeSeat = gnTOTAL_SEATS
                // unlock gSofaMutex
            ////////////////////////////////////////////
            gnFreeSeat = gnTOTAL_SEATS;
            pthread_mutex_unlock(&gSofaMutex);

            ////////////////////////////////////////////
            // 2.2.2 清空 eventQueue
            ////////////////////////////////////////////
            while(msgrcv(
                nEventQueueId, &newMsg, gnEVENT_MSG_BUFSIZE, gnEVENT_MTYPE, IPC_NOWAIT) == 0)
            {
                continue;
            }

            ////////////////////////////////////////////
            // 2.2.3 for loop 3 次 (3 個 barber threads)
            ////////////////////////////////////////////
            for(i = 0; i < gnBARBER_NUM; ++i)
            {
                ////////////////////////////////////////////
                // 2.2.3.1 建立新的 eventMessage_t, newMsg
                    // 初始化 newMsg 的參數
                        // eventType = ending
                        // nNeedSecond = 0
                ////////////////////////////////////////////
                newMsg.mtype = gnEVENT_MTYPE;
                newMsg.mtext[0] = ENDING;
                newMsg.mtext[1] = 0;

                ////////////////////////////////////////////
                // 2.2.3.2 建立的 newMsg 放入 eventQueue 當中
                    // msgsnd eventQueue 要放在 lock 的外面
                    // 這樣 Barber thread 才可以順利 recv
                ////////////////////////////////////////////
                if(msgsnd(nEventQueueId, &newMsg, gnEVENT_MSG_BUFSIZE, 0) < 0)
                {
                    --i;
                    printf(ERROR_EVENT_QUEUE_SEND_FAILURE);
                }
            }
            goto errExit;

        default:
            printf(INFO_WRONG_INPUT_CHOOSE_ACTION);
            while(getchar() != '\n');
            break;
        } // end of switch(nAction)
    } // end of while(1)

errExit:
    ////////////////////////////////////////////
    // 2.2.4 timeout pthread join, with some timeout
        // otherwise kill the process
    ////////////////////////////////////////////
    clock_gettime(CLOCK_REALTIME, &threadJoinTimeout);
    threadJoinTimeout.tv_sec += gnMAX_WAIT_THREAD_JOIN_SEC;
    for(i = 0; i < gnBARBER_NUM; ++i)
    {
        // pthread_join(aBarberThread[i], NULL);
        pthread_timedjoin_np(aBarberThread[i], NULL, &threadJoinTimeout);
    }

threadCreateErrExit:
    pthread_mutex_destroy(&gSofaMutex);

    msgctl(nEventQueueId, IPC_RMID, NULL);

    printf(INFO_SHOP_CLOSED);

    return 0;
}