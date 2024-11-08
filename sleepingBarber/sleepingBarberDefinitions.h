#ifndef SLEEPINGBARBERDEFINITIONS_H
#define SLEEPINGBARBERDEFINITIONS_H

#define gnBARBER_PROJECT_NUM            2
#define gnBARBER_NUM                    3
#define gnTOTAL_SEATS                   2
#define gnEVENT_MTYPE                   1
#define gnEVENT_MSG_BUFSIZE             20
#define gnINPUT_BUFFER                  20
#define gnMAX_WAIT_THREAD_JOIN_SEC      30
#define gsEVENT_QUEUE_NAME      "sleeping_barber_event_queue"

#define INFO_BARBER_IS_SLEEPING             "理髮師[%d]正在睡覺\n"
#define INFO_BARBER_IS_CUTTING              "理髮師[%d] 正在理髮 需要%d秒\n"
#define INFO_BARBER_IS_LEAVING              "理髮師[%d]離開\n"
#define INFO_BARBERSHOP_OPEN                "*** 開店中 ***\n"
#define INFO_BARBER_ACTION_1                "輸入 1, 動作1: 顧客上門\n"
#define INFO_BARBER_ACTION_2                "輸入 2, 動作2: 關店\n"
#define INFO_WRONG_INPUT_CHOOSE_ACTION      "錯誤輸入, 請輸入 '1' 或 '2'\n"
#define INFO_INPUT_CUSTOMER_NEEDED_TIME     "輸入一數字, 1 ~ 60, 是這位客人需要理髮的時間\n"
#define INFO_WRONG_INPUT_CHOOSE_TIME        "錯誤輸入, 請輸入 1 ~ 60 的數字\n"
#define INFO_CUSTOMER_ENTER                 "客人[%d]上門\n"
#define INFO_SOFA_IS_FULL                   "沙發滿了，客人[%d]直接離開\n"
#define INFO_SHOP_CLOSED                    "關店\n"

#define ERROR_PTHREAD_CREATION_FAILURE      "[Error] Pthread 建立失敗\n"
#define ERROR_EVENT_QUEUE_CREATION_FAILURE  "[Error] Event Queue 建立失敗\n"
#define ERROR_EVENT_QUEUE_SEND_FAILURE      "[Error] Event Queue 傳送訊息失敗\n"
#define ERROR_EVENT_QUEUE_RECV_FAILURE      "[Error] Event Queue 收到訊息失敗\n"

#endif // SLEEPINGBARBERDEFINITIONS_H