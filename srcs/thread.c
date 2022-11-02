/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// thread.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 20/08/17
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/thread.h"

#include <stdio.h>

void create_thread(thread *t, pthread_t *pt, pthread_mutex_t *m)
{
    t->threads = pt;
    t->mutex = m;
    t->active = 0;
}

void create_thread_collection(thread_collection *t, int size)
{
    t->size = 1;
    t->ptr = 0;
    t->threads = (thread *)malloc(sizeof(thread) * size);
    t->selected = 0;
}

void add_thread(thread_collection *t, thread *th)
{
    if (t->ptr == t->size)
    {
        t->size *= 2;
        t->threads = (thread *)realloc(t->threads, sizeof(thread) * t->size);
    }

    create_thread(&t->threads[t->ptr], th->threads, th->mutex);
    t->ptr++;
}

thread *get_thread(thread_collection *t)
{
    if (t->selected >= t->ptr)
    {
        t->selected = 0;
    }

    while (t->threads[t->selected].active == 1)
    {
        t->selected++;
        if (t->selected >= t->ptr)
        {
            t->selected = 0;
        }
    }

    t->threads[t->selected].active = 1;
    return &t->threads[t->selected++];
}

void destroy_thread_collection(thread_collection *t)
{
    free(t->threads);
}
