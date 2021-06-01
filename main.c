#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "slow_sort.h"
#include "fast_sort.h"
#define SORTMOD 2

int get_flgth(FILE*, int*);
void cp_file(FILE*, int[]);
double do_sort(int[], int, int, int);
void print_output(int[], int, int, double);
int main(){
    FILE* sort_file = fopen("Data1.txt", "rt");
    FILE* dessort_file = fopen("Data2.txt", "rt");
    FILE* rand_file = fopen("Data3.txt", "rt");
    int sel_file, sortmod[SORTMOD];
    int size_init, temp, max_digit = -1;
    int *st_arr1, *st_arr2;
    double time_many[SORTMOD];

    //파일 오픈 실패시
    if(sort_file == NULL || dessort_file == NULL || rand_file == NULL){
        fprintf(stderr, "파일 오픈에 실패했습니다! 메시지를 확인하셨다면 아무 키를 누르세요\n");
        getchar();
        exit(-1);
    }
    
    //실제 반복 부분
    do{
        //파일 선택 부분
        do{
            puts("정렬을 수행할 파일을 고르세요.");
            puts("1. 정렬될 파일\n2. 역정렬된 파일\n3. 랜덤 파일\n0. 종료");
            printf(">>>");
            scanf("%d", &sel_file);
        }while( sel_file < 0 || sel_file > 3 );

        //종료 선택시 바로 프로그램 종료
        if(sel_file == 0){
            fclose(sort_file);
            fclose(dessort_file);
            fclose(rand_file);
            return 0;
        }
        
        //정렬모드 선택 부분
        for( int i_for = 0; i_for < SORTMOD; i_for++ ){
            do{
                printf("%d번째로 사용할 정렬방식을 고르세요.\n", i_for);
                puts("1. 선택정렬\n2. 삽입정렬\n3. 버블정렬\n4. 쉘정렬");
                puts("5. 합병정렬\n6. 퀵정렬\n7. 힙정렬\n8. 기수정렬");
                printf(">>>");
                scanf("%d", &sortmod[i_for]);
            }while( sortmod[i_for] < 1 || sortmod[i_for] > 8 );
        }
        if(sortmod[0] > sortmod[1]){
            SWAP(sortmod[0], sortmod[1], temp);
        }

        //실제 작동 부분
        switch (sel_file){
        case 1:
            size_init = get_flgth(sort_file, &max_digit);
            st_arr1 = (int*)calloc(size_init, sizeof(int));
            st_arr2 = (int*)calloc(size_init, sizeof(int));
            cp_file(sort_file, st_arr1);
            cp_file(sort_file, st_arr2);
            time_many[0] = do_sort(st_arr1, size_init, sortmod[0], max_digit);
            time_many[1] = do_sort(st_arr2, size_init, sortmod[1], max_digit);
            break;
        case 2:
            size_init = get_flgth(dessort_file, &max_digit);
            st_arr1 = (int*)calloc(size_init, sizeof(int));
            st_arr2 = (int*)calloc(size_init, sizeof(int));
            cp_file(dessort_file, st_arr1);
            cp_file(dessort_file, st_arr2);
            time_many[0] = do_sort(st_arr1, size_init, sortmod[0], max_digit);
            time_many[1] = do_sort(st_arr2, size_init, sortmod[1], max_digit);
            break;
        case 3:
            size_init = get_flgth(rand_file, &max_digit);
            st_arr1 = (int*)calloc(size_init, sizeof(int));
            st_arr2 = (int*)calloc(size_init, sizeof(int));
            cp_file(rand_file, st_arr1);
            cp_file(rand_file, st_arr2);
            time_many[0] = do_sort(st_arr1, size_init, sortmod[0], max_digit);
            time_many[1] = do_sort(st_arr2, size_init, sortmod[1], max_digit);
            break;
        default:
            fprintf(stderr, "뭔가 오류가 났어요...\n");
            exit(-1);
            break;
        }

        //출력부
        //모드가 같을 때는 하나만 출력
        if(sortmod[0] == sortmod[1]){
            print_output(st_arr1, sortmod[0], size_init, time_many[0]);
        }
        else{
            print_output(st_arr1, sortmod[0], size_init, time_many[0]);
            print_output(st_arr2, sortmod[1], size_init, time_many[1]);
        }

    }while(1);
    
    fclose(sort_file);
    fclose(dessort_file);
    fclose(rand_file);
    return 0;
}

//끌고온 파일 스트림에서 길이 구하는 함수
int get_flgth(FILE* fp, int* max_digit){
    int lgth = 0;
    int digit = 0;

    while ( !feof(fp) ){
        if( fseek(fp, 1, SEEK_CUR) == "\n"){
            lgth++;
            if(digit > *max_digit){
                *max_digit = digit;
            }
            digit = 0;
        }
        else{
            digit++;
        }
    }
    fseek(fp, 0, SEEK_SET);
    return lgth;
}

//끌고온 파일 스트림에서 배열에 복사하는 함수
void cp_file(FILE* fp, int arr[]){
    int idx = 0;
    while( !feof(fp) ){
        fscanf(fp, "%d", &arr[idx++]);
    }
    fseek(fp, 0, SEEK_SET);
    return;
}

//배열 정렬하면서 시간 구하는 함수
double do_sort(int arr[], int size_init, int sortmod, int max_digit){
    clock_t start, stop;
    double during_time;

    start = clock();
    switch (sortmod){
    case 1: //선택정렬
        selection_sort(arr, size_init);
        break;
    case 2: //삽입정렬
        insertion_sort(arr, size_init);
        break;
    case 3: //버블정렬
        bubble_sort(arr, size_init);
        break;
    case 4: //쉘정렬
        shell_sort(arr, size_init);
        break;
    case 5: //합병정렬
        merge_sort(arr, 0, size_init-1, size_init);
        break;
    case 6: //퀵정렬
        qsort((void*)arr, size_init, sizeof(int), compare);
        break;
    case 7: //힙정렬
        heap_sort(arr, size_init);
        break;
    case 8: //기수정렬
        radix_sort(arr, size_init, max_digit);
        break;
    default:
        fprintf(stderr, "잘못된 값이 들어온 것 같아요...\n");
        exit(-1);
        break;
    }
    stop = clock();

    during_time = (double) (stop-start) / CLOCKS_PER_SEC;
    return during_time;
}

//결과 출력부 함수
void print_output(int arr[], int sortmod, int size_init, double during_time){
    FILE* fp = NULL;
    
    switch (sortmod){
    case 1: //선택정렬
        fp = fopen("Data_Sort1.txt", "wt");
        for (int i_for = 0; i_for < size_init; i_for++){
            fprintf(fp, "%d\n", arr[i_for]);
        }
        printf("선택정렬: %lf초\n", during_time);
        break;
    case 2: //삽입정렬
        fp = fopen("Data_Sort2.txt", "wt");
        for (int i_for = 0; i_for < size_init; i_for++){
            fprintf(fp, "%d\n", arr[i_for]);
        }
        printf("삽입정렬: %lf초\n", during_time);
        break;
    case 3: //버블정렬
        fp = fopen("Data_Sort3.txt", "wt");
        for (int i_for = 0; i_for < size_init; i_for++){
            fprintf(fp, "%d\n", arr[i_for]);
        }
        printf("버블정렬: %lf초\n", during_time);
        break;
    case 4: //쉘정렬
        fp = fopen("Data_Sort4.txt", "wt");
        for (int i_for = 0; i_for < size_init; i_for++){
            fprintf(fp, "%d\n", arr[i_for]);
        }
        printf("쉘정렬: %lf초\n", during_time);
        break;
    case 5: //합병정렬
        fp = fopen("Data_Sort5.txt", "wt");
        for (int i_for = 0; i_for < size_init; i_for++){
            fprintf(fp, "%d\n", arr[i_for]);
        }
        printf("합병정렬: %lf초\n", during_time);
        break;
    case 6: //퀵정렬
        fp = fopen("Data_Sort6.txt", "wt");
        for (int i_for = 0; i_for < size_init; i_for++){
            fprintf(fp, "%d\n", arr[i_for]);
        }
        printf("퀵정렬: %lf초\n", during_time);
        break;
    case 7: //힙정렬
        fp = fopen("Data_Sort7.txt", "wt");
        for (int i_for = 0; i_for < size_init; i_for++){
            fprintf(fp, "%d\n", arr[i_for]);
        }
        printf("힙정렬: %lf초\n", during_time);
        break;
    case 8: //기수정렬
        fp = fopen("Data_Sort8.txt", "wt");
        for (int i_for = 0; i_for < size_init; i_for++){
            fprintf(fp, "%d\n", arr[i_for]);
        }
        printf("기수정렬: %lf초\n", during_time);
        break;
    default:
        fprintf(stderr, "뭔가 오류가 났어요...\n");
        exit(-1);
        break;
    }

    return;
}