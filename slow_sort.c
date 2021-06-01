#include "slow_sort.h"

//선택정렬 함수
void selection_sort(int list[], int n){
    int i, j, least, temp;
    
    for(i=0; i<n-1; i++) {
        least = i;
        
        for(j=i+1; j<n; j++){// 최솟값 탐색
            if(list[j]<list[least]){
                least = j;
            }
            SWAP(list[i], list[least], temp);
        }

    }
}

//삽입정렬 함수
void insertion_sort(int list[], int n) { 
    int i, j, key;
    
    for(i=1; i<n; i++){
        key = list[i];
        
        for(j=i-1; j>=0 && list[j]>key; j--){
            list[j+1] = list[j]; // 레코드의 오른쪽 이동
        }
        list[j+1] = key;
    }
}

//버블정렬 함수
void bubble_sort(int list[], int n){ 
    int i, j, temp;
    
    for(i=n-1; i>0; i--){

        for(j=0; j<i; j++){

            if(list[j]>list[j+1]){// 앞뒤의 레코드를 비교한 후 교체
                SWAP(list[j], list[j+1], temp);
            }
        }
    }
}