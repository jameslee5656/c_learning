#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define gnBARBER_NUM    3
#define gnTOTAL_SEATS   2
#define gnEVENT_MTYPE   1
#define gnEVENT_MSG_BUFSIZE     20
#define gsEVENT_QUEUE_NAME      "sleeping_barber_event_queue"

#define ERROR_PTHREAD_CREATION_FAILURE      "[Error] Pthread 建立失敗\n"
#define ERROR_EVENT_QUEUE_CREATION_FAILURE  "[Error] Event Queue 建立失敗\n"
#define ERROR_EVENT_QUEUE_SEND_FAILURE      "[Error] Event Queue 傳送訊息失敗\n"
#define ERROR_EVENT_QUEUE_RECV_FAILURE      "[Error] Event Queue 收到訊息失敗\n"

#endif // DEFINITIONS_H