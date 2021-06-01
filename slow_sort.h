#ifndef __SLOW_SORT_H__

#define __SLOW_SORT_H__

#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) ) 

extern void selection_sort(int [], int);
extern void insertion_sort(int [], int);
extern void bubble_sort(int [], int);

#else

#endif