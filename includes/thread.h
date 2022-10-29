#ifndef FTC_THREAD_H
#define FTC_THREAD_H

#include <pthread.h>
#include <stdlib.h>

// Thread struct
struct _thread
{
    pthread_t *threads;
    pthread_mutex_t *mutex;
    int active;
};
typedef struct _thread thread;

struct _thread_collection
{
    thread *threads;
    int size;
    int ptr;
    int selected;
};
typedef struct _thread_collection thread_collection;

void create_thread(thread *t, pthread_t *pt, pthread_mutex_t *m);

void create_thread_collection(thread_collection *t, int size);
void add_thread(thread_collection *t, thread *th);
thread *get_thread(thread_collection *t);
void destroy_thread_collection(thread_collection *t);

#endif // FTC_THREAD_H
