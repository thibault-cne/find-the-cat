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

void create_thread(thread *t, pthread_t *pt, pthread_mutex_t *m)
{
    t->threads = pt;
    t->mutex = m;
    t->ptr = 0;
}
