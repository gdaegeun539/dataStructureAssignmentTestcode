#include "fifo_queue.h"

// 큐 초기화
void init_queue(QueueType *q, int size_init){
    q->data = (element*)calloc(sizeof(element), size_init);
    q->front = q->rear = 0;
    return;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q){
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q, int size_init){
    return ((q->rear + 1) % size_init == q->front);
}

// 삽입 함수
void enqueue(QueueType *q, element item, int size_init){
    if (is_full(q, size_init)){
        q->data = (element*)realloc( q->data, sizeof(element) * (++size_init) );
    }
    q->rear = (q->rear + 1) % size_init;
    q->data[q->rear] = item;
    return;
}

// 삭제 함수
element dequeue(QueueType *q, int size_init){
    if (is_empty(q)){
        fprintf(stderr, "큐가 공백상태입니다");
        return -1;
    }
    q->front = (q->front + 1) % size_init;
    return q->data[q->front];
}