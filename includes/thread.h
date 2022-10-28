#ifndef FTC_THREAD_H
#define FTC_THREAD_H

#include <pthread.h>

// Thread struct
struct _thread
{
    pthread_t *threads;
    pthread_mutex_t *mutex;
    int ptr;
};
typedef struct _thread thread;

void create_thread(thread *t, pthread_t *pt, pthread_mutex_t *m);

#endif // FTC_THREAD_H
