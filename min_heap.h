#ifndef __MIN_HEAP_H__

#define __MIN_HEAP_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int key;
}elm_heap;

typedef struct { //힙 타입
    elm_heap* heap;
    int heap_size;
} HeapType;

extern void init(HeapType*, int);
extern void insert_min_heap(HeapType*, elm_heap);
extern elm_heap delete_min_heap(HeapType*);

#else

#endif