## Main Thread
1. 建立 3 個 barber threads, barberThread,
    1 個 conditional variable, sofaSignal,
    1 個 mutex, sofaMutex,
    1 個 int, 代表初始有 10 個空閒的位置, nfreeSeat,
    1 個 IPC Queue, eventQueue,

2. main thread while 等待 input

    2.1 有客人上門, input 動作 1, 同時輸入所需秒數:

        2.1.1 check sofaMutex

            2.1.1.1 如果沒有取得 sofaMutex, wait for sofaSignal
                signal 進來，並且搶到 mutex, lock 住

        2.1.2 如果 nfreeSeat <= 0, 放棄這位customer

        2.1.3 建立新的 eventMessage_t, newMsg

            2.1.3.1 初始化 newMsg 的參數
                eventType = customer
                nNeedSecond = 所需秒數

        2.1.4 建立的 newMsg 放入 eventQueue 當中

        2.1.5 nfreeSeat -= 1

        2.1.6 unlock sofaMutex

        2.1.7 signal(sofaSignal)

    2.2 input 動作 2
    for 回圈 3 次 (3 個 barber thread)

        2.2.1 check sofaMutex

            2.2.1.1 如果沒有取得 sofaMutex, wait for sofaSignal
                    signal 進來，並且搶到 mutex, lock 住

        2.2.2 建立新的 eventMessage_t newMsg

            2.2.2.1 初始化 newMsg 的參數
                eventType = ending
                nNeedSecond = 0

        2.2.3 建立的 newMsg 放入 eventQueue 當中

        2.2.4 unlock mutex

        2.2.5 signal(sofaSignal)

## Barber Thread
1. while 檢查 eventQueue 的 size

    1.1. 如果 size 為 0 或者 sofaMute unavailable, 等待 sofaSignal
        sofaSignal 進來，並且搶到 mutex, lock 住

2. 從 eventQueue 取出一個 newMsg, pop queue

    2.1 if newMsg.eventType_t == customer

        2.1.1 freeSeat += 1

        2.1.2 unlock mutex

        2.1.3 signal(sofaSignal)

        2.1.4 wait for newMsg.nNeedSecond

    2.2 else if newMsg.eventType_t == ending;

        2.2.1 unlock mutex

        2.2.2 signal(sofaSignal)

        2.2.3 end thread

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


