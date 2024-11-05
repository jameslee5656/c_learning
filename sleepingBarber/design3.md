#define gnBARBER_NUM    3
#define gnTOTAL_SEATS   10

int gnFreeSeat = 10;
pthread_mutex_t gSofaMutex = PTHREAD_MUTEX_INITIALIZER;

## Main Thread
1. 建立三個 Barber threads,
   1 個 IPC Queue, eventQueue, 並且清空
2. while 等待 input

    2.1 有客人上門, input 動作 1, 同時輸入所需秒數,

        2.1.1 lock gSofaMutex

        2.1.2 如果 gnFreeSeat 沒有位置了 (<= 0) , unlock gSofaMutex, 放棄這位customer

        2.1.3 建立新的 eventMessage_t, newMsg
            初始化 newMsg 的參數
                eventType = customer
                nNeedSecond = 所需秒數

        2.1.4 gnFreeSeat -= 1

        2.1.5 把建立的 newMsg 放入 eventQueue 當中

        2.1.6 unlock gSofaMutex

    2.2 input 動作 2

    lock gSofaMutex
    清空 eventQueue, gnFreeSeat = 10
    unlock gSofaMutex

    for loop 3 次 (3 個 barber threads)

        2.2.1 lock gSofaMutex

        2.2.2 建立新的 eventMessage_t, newMsg
            初始化 newMsg 的參數
                eventType = customer
                nNeedSecond = 所需秒數

        2.2.3 gnFreeSeat -= 1

        2.2.4 建立的 newMsg 放入 eventQueue 當中

        2.2.5 unlock gSofaMutex

## Barber Thread
1. 建立一個 IPC queue, eventQueue

2. while 嘗試拿 gSofaMutex

    2.1 if gnFreeSeat >= gnTOTAL_SEATS
        unlock gSofaMutex
        wait 5 sec, continue

    2.2 從 eventQueue 取出一個 newMsg, pop queue

        2.2.1 if newMsg.eventType_t == customer

            2.2.1.1 gnFreeSeat += 1

            2.2.1.2 unlock gSofaMutex

            2.2.1.3 wait for newMsg.nNeedSecond

        2.2.2 else if newMsg.eventType_t == ending

            2.2.2.1 gnFreeSeat += 1

            2.2.2.2 unlock gSofaMutex

            2.2.2.3 end thread

[Requirements]
* nNeedSeconds > 0 && nNeedSeconds <= 60

enum eventType_t
{
    customer,
    ending,
}

struct eventMessage_t
{
    eventType_t eventType;
    int nNeedSeconds;
};





