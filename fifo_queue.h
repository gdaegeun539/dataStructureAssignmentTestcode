#ifndef __FIFO_QUEUE_H__

#define __FIFO_QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct { // 큐 타입
    element* data;
    int front, rear;
} QueueType;

extern void init_queue(QueueType*, int);
extern int is_empty(QueueType*);
extern int is_full(QueueType*, int);
extern void enqueue(QueueType*, element, int);
extern element dequeue(QueueType*, int);

#else

#endif