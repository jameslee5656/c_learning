#ifndef BARBER_WORKING_THREAD
#define BARBER_WORKING_THREAD

#include <pthread.h>

#include "definitions.h"

extern int gnFreeSeat;
extern pthread_mutex_t gSofaMutex;

enum eventType_t
{
    customer,
    ending,
};

struct eventMessage_t
{
    long mtype;
    char mtext[gnEVENT_MSG_BUFSIZE];
};

void *barberWorkingThread(void *arg);

#endif // BARBER_WORKING_THREAD