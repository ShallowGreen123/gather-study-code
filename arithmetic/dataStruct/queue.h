#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// config
#define DEF_RING_QUEUE_SIZE 5

typedef struct _queue_ {
    int buf[DEF_RING_QUEUE_SIZE];
    int front;
    int tail;
} queue_t;

void QueueInit(queue_t *q);
void QueueInput(queue_t *q, int val);
void QueueOutput(queue_t *q, int *val);
#endif
