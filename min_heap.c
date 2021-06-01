#include "min_heap.h"

// 생성 및 초기화 함수
void init(HeapType* h, int size_init){
    h->heap = (elm_heap*)malloc(sizeof(elm_heap)*size_init);
    h->heap_size = 0;
}

void insert_min_heap(HeapType *h, elm_heap item){
    int i;
    i = ++(h->heap_size);
    
    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while((i != 1) && (item.key < h->heap[i/2].key)) {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item; // 새로운 노드를 삽입
}

// 삭제 함수
elm_heap delete_min_heap(HeapType* h){
    int parent, child;
    elm_heap item, temp;
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1, child = 2;
    
    while (child <= h->heap_size) {
        // 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
        if ((child < h->heap_size) && h->heap[child + 1].key < h->heap[child].key){
            child++;
        }
        if (temp.key <= h->heap[child].key){
            break;
        }

        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}