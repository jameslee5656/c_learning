#ifndef BARBER_WORKING_THREAD
#define BARBER_WORKING_THREAD

#include <pthread.h>

extern int gnFreeSeat;
extern pthread_mutex_t gSofaMutex;

void *barberWorkingThread(void *arg);

#endif // BARBER_WORKING_THREAD