#ifndef BARBER_WORKING_THREAD
#define BARBER_WORKING_THREAD
#include <pthread.h>

#include "sleepingBarberDefinitions.h"

extern int gnFreeSeat;
extern pthread_mutex_t gSofaMutex;

enum eventType_t
{
    CUSTOMER,
    ENDING,
};

struct eventMessage_t
{
    long mtype;
    char mtext[gnEVENT_MSG_BUFSIZE];
};

void *barberWorkingThread(void *arg);

#endif // BARBER_WORKING_THREAD