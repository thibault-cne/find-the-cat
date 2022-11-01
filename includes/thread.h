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

// Create a new thread
// @param t the thread pointer
// @param pt the pthread_t pointer
// @param mutex the mutex pointer
void create_thread(thread *t, pthread_t *pt, pthread_mutex_t *m);

// Create a new thread collection
// @param t the thread collection pointer
// @param size the size of the thread collection
void create_thread_collection(thread_collection *t, int size);

// Add a thread to the thread collection
// @param t the thread collection pointer
// @param th the thread pointer to add
void add_thread(thread_collection *t, thread *th);

// Get the next available thread
// @param t the thread collection pointer
// @return the next available thread
thread *get_thread(thread_collection *t);

// Free the thread collection
// @param t the thread collection pointer
void destroy_thread_collection(thread_collection *t);

#endif // FTC_THREAD_H
