#ifndef __FAST_SORT_H__

#define __FAST_SORT_H__

#include "fifo_queue.h"
#include "min_heap.h"
#define BUCKETS 10

extern void radix_sort(int[], int, int);
extern int compare(const void*, const void*);
extern void merge(int[], int, int, int, int);
extern void merge_sort(int[], int, int, int);
extern void heap_sort(elm_heap[], int);
extern void inc_insertion_sort(int[], int, int, int);
extern void shell_sort(int[], int);

#else

#endif