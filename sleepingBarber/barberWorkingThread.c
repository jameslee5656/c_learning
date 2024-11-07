#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "definitions.h"
#include "barberWorkingThread.h"

int gnFreeSeat = gnTOTAL_SEATS;
pthread_mutex_t gSofaMutex = PTHREAD_MUTEX_INITIALIZER;

// ## Barber Thread
void *barberWorkingThread(void *arg)
{
    key_t eventQueueKey = 0;
    int nBarberId = 0;
    int nEventQueueId = 0;
    int nEventQueueRcvResult = 0;
    struct eventMessage_t newMsg;
    pthread_t self;

    ////////////////////////////////////////////
    // 1. 建立一個 IPC queue, eventQueue
        // int nRecvResult = 0;
    ////////////////////////////////////////////
    nBarberId = *((int *) arg);
    eventQueueKey = ftok(gsEVENT_QUEUE_NAME, 65);
    if((nEventQueueId = msgget(eventQueueKey, 0666 | IPC_EXCL)) < 0)
    {
        printf(ERROR_EVENT_QUEUE_CREATION_FAILURE);
        return NULL;
    }

    while(nEventQueueRcvResult =
        msgrcv(nEventQueueId, &newMsg, sizeof(newMsg), gnEVENT_MTYPE, IPC_NOWAIT))
    {
        if(nEventQueueRcvResult < 0 && errno == ENOMSG)
        {
            printf("理髮師[%d]正在睡覺\n", nBarberId);
            nEventQueueRcvResult =
                msgrcv(nEventQueueId, &newMsg, sizeof(newMsg), gnEVENT_MTYPE, 0);
        }

        ////////////////////////////////////////////
        // 2.1 lock gSofaMutex
        ////////////////////////////////////////////
        pthread_mutex_lock(&gSofaMutex);

        ////////////////////////////////////////////
        // 2.2 msgrcv 各項檢查
            // 如果 nRecvResult <= 0
        ////////////////////////////////////////////
        if(nEventQueueRcvResult < 0)
        {
            ////////////////////////////////////////////
            // 2.2.1 檢查 msgrcv 的資訊是否是剛好"正在"清理 eventQueue,
                // 如果是繼續等待下一訊息
            ////////////////////////////////////////////
            if(errno == E2BIG && gnFreeSeat >= 10)  continue;

            ////////////////////////////////////////////
            // 2.2.2 如果是其他種狀況, print 結果,
                // unlock gSofaMutex, end thread
            ////////////////////////////////////////////
            printf("%s", ERROR_EVENT_QUEUE_RECV_FAILURE);
            printf("%d\n", errno);

            break;
        }

        ////////////////////////////////////////////
        // 2.3 if newMsg.eventType_t == customer
        ////////////////////////////////////////////
        if(newMsg.eventType == customer)
        {
            ////////////////////////////////////////////
            // 2.3.1 gnFreeSeat += 1
            ////////////////////////////////////////////
            if(gnFreeSeat < gnTOTAL_SEATS)  gnFreeSeat += 1;

            ////////////////////////////////////////////
            // 2.3.2 unlock gSofaMutex
            ////////////////////////////////////////////
            pthread_mutex_unlock(&gSofaMutex);

            printf("理髮師[%d] 正在理髮 需要%d秒\n", nBarberId, newMsg.nNeedSeconds);

            ////////////////////////////////////////////
            // 2.3.3 wait for newMsg.nNeedSecond
            ////////////////////////////////////////////
            sleep(newMsg.nNeedSeconds);
        }
        // 2.4 else if newMsg.eventType_t == ending
        else if(newMsg.eventType == ending)
        {
            ////////////////////////////////////////////
            // 2.4.1 unlock gSofaMutex
            ////////////////////////////////////////////
            pthread_mutex_unlock(&gSofaMutex);

            ////////////////////////////////////////////
            // 2.4.1 end thread
            ////////////////////////////////////////////
            break;
        }
    }

    printf("理髮師[%d]離開\n", nBarberId);
    return NULL;
}