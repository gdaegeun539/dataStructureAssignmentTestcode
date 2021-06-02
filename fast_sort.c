#include "fast_sort.h"

//기수정렬 함수
void radix_sort(int list[], int size_init, int digit){
    int i, b, d, factor=1;
    QueueType queues[BUCKETS];
    
    for(b=0;b<BUCKETS;b++){
        init_queue(&queues[b], size_init); // 큐들의 초기화
    }

    for(d=0; d<digit; d++){
        for(i=0; i<size_init; i++){// 데이터들을 자리수에 따라 큐에 입력
            enqueue( &queues[(list[i]/factor)%10], list[i], size_init);
        } 
        
        for(b=i=0;b<BUCKETS;b++){
            while( !is_empty(&queues[b]) ){
                list[i++] = dequeue(&queues[b], size_init);
            }
        } // 버켓에서 꺼내어 list로 합친다.
        factor *= 10; // 그 다음 자리수로 간다.
    }
}

//퀵정렬 비교부 함수
int compare(const void *arg1, const void *arg2){
    if (*(int *)arg1 > *(int *)arg2){
        return 1;
    }
    else if (*(int *)arg1 == *(int *)arg2){
        return 0;
    }
    else{
        return -1;
    }
}

//합병정렬 정렬부 함수
void merge(int list[], int left, int mid, int right, int size_init){
    int i, j, k, l;
    element* sorted = (element*)calloc(sizeof(element), size_init);
    i=left; j=mid+1; k=left;
    
    // 분할 정렬된 list의 합병
    while(i<=mid && j<=right){
        if(list[i]<=list[j]){
            sorted[k++] = list[i++];
        }
        else{
            sorted[k++] = list[j++];
        }
    }

    if(i>mid){ // 남아 있는 레코드의 일괄 복사
        for(l=j; l<=right; l++){
            sorted[k++] = list[l];
        }
    }
    
    else{ // 남아 있는 레코드의 일괄 복사
        for(l=i; l<=mid; l++){
            sorted[k++] = list[l];
        }
    }
    
    // 배열 sorted[]의 리스트를 배열 list[]로 복사
    for(l=left; l<=right; l++){
        list[l] = sorted[l];
    }

    free(sorted);
    return;
}

//합병정렬 재귀부 함수
void merge_sort(int list[], int left, int right, int size_init){
    int mid;
    
    if(left<right){
        mid = (left+right)/2; // 리스트의 균등분할
        merge_sort(list, left, mid, size_init); // 부분리스트 정렬
        merge_sort(list, mid+1, right, size_init); //부분리스트 정렬
        merge(list, left, mid, right, size_init); // 합병
    }

    return;
}

//힙 정렬 함수
void heap_sort(elm_heap a[], int size_init){
    int i;
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    init(h, size_init);
    
    for (i = 0; i<size_init; i++) {
        insert_max_heap(h, a[i]);
    }
    for (i = (size_init - 1); i >= 0; i--) {
        a[i] = delete_max_heap(h);
    }
    
    free(h->heap);
    free(h);
}

//쉘정렬 전용 삽입정렬 함수
void inc_insertion_sort(int list[], int first, int last, int gap){
    int i, j, key;
    for(i=first+gap; i<=last; i=i+gap){
        key = list[i];
        for(j=i-gap; j>=first && key<list[j];j=j-gap){
            list[j+gap]=list[j];
        }
        list[j+gap]=key;
    }
}

//쉘정렬 함수
void shell_sort( int list[], int n ){ // n = size
    int i, gap;
    for( gap=n/2; gap>0; gap = gap/2 ) {
        if( (gap%2) == 0 ){
            gap++;
        }
        for(i=0;i<gap;i++){
            inc_insertion_sort(list, i, n-1, gap);
        } // 부분 리스트의 개수는 gap
    }
}