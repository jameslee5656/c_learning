# Sleeping Barber

[顧客沙發] -> [理髮座位]   -> Barber1
                        -> Barber2
                        -> Barber3

enum eventType_t
{
    customer,
    ending
};

// nNeedSeconds 最少 1, 最多 60
struct eventMessage_t
{
    eventType_t eventType;
    int nNeedSeconds;
};

* eventMessage_t
    * event, customer or ending
    * second, 需要多少時間理髮

* int totalBarber, 店內的 barber
-> availBarber[3], 標示空閒的 barber

* msg_queue: barberOccupied
* sofaMutex, 保護沙發
* consumerSofa (沙發), queue, max 10;

* 動作1: 客人上門, 理髮 ? 秒
* 動作2: 關門

## main
1. 建立 3 個 barber thread, customer 1 mutex
2. main thread 等待 input
2.1 有客人上門, input 動作1
    呼叫 processConsumer(consumer*)

2.2 關門, input 動作2
    等待 availBarber, 傳送
    結束 main thread

## processConsumer
processConsumer(consumer*)
    1. if mutex used -> blocking and wait for mutex
    2. lock mutex,

    2.1.1 如果 consumerSofa.size() == 10
        沙發滿了，放棄這位客人, unlock mutex return;

    2.1.2 如果沒有滿，把顧客放到沙發區

    2.2  check availBarber[3], 看是否有barber有空

        2.2.1 有空的 barber 是 x
            aviableBarber[x] = false;
            unlock mutex
            msgsnd(mqID, msg, sizeof(msg), 0);

        2.2.2 沒有 barber 有空, unlock mutex, return

## barberAvail
barberAvail(barber)
    1. wait until mutex not used
    2. lock mutex,

        2.1 availBarber[barber] = true;

        2.1 if consumerSofa == 0, unlock mutex and return.

        2.2  check availBarber[3], 看是否有barber有空

        2.2.1 有空的 barber 是 x
            aviableBarber[x] = false;
            unlock mutex
            msgsnd(mqID, msg, sizeof(msg), 0);

        2.2.2 沒有 barber 有空, unlock mutex, return

## Barber Thread
    1. msgget, 等待 message
    2.1 if message == CLOSE_EVENT
        end

    2.2 wait until mutex not used
        lock mutex
        從 queue 取一 customer, pop queue
        unlock mutex

    2.3 wait the second for the consumer

    2.4 barberAvail(thisBarber)