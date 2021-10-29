#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    unsigned int score;
    float data[3];
    char comments[16];
}ELEMENT;

typedef int _Cmpfun(const void *, const void *);

int my_element_score_compare(const void *a, const void *b){
    ELEMENT *elem_a, *elem_b;
    elem_a=(ELEMENT*)a;
    elem_b=(ELEMENT*)b;
    if(elem_a->score==elem_b->score){
        return 0;
    }
    else if(elem_a->score<elem_b->score){
        return -1;
    }
    else{
        return 1;
    }
}

void qsort_orig(void* array, size_t n, size_t size, _Cmpfun* cmp){
    char* pivot;

    if(n>1){
        size_t left=0;
        size_t right=n-1;
        //끝 인덱스를 가리킨다

        char* left_pointer=(char*)array;
        char* right_pointer=left_pointer+size*right;
        pivot=left_pointer;
        //이 메모리를 ELEMENT로 읽을 것. 맨 왼쪽을 pivot으로 지정한다
        ELEMENT* buf;
        buf=(ELEMENT*)malloc(size);
        for(;left_pointer<right_pointer;left_pointer+=size){
            if((*cmp)(left_pointer, right_pointer)<0){
                memcpy(buf, left_pointer, size);
                memcpy(left_pointer, right_pointer, size);
                memcpy(right_pointer, buf, size);
                //SWAP
                pivot+=size;
            }
        }
        memcpy(buf, right_pointer, size);
        memcpy(right_pointer, pivot, size);
        memcpy(pivot, buf, size);

        qsort_orig(array, (pivot-left_pointer)/size, size, cmp);
        qsort_orig(pivot+size, (right_pointer-pivot)/size, size, cmp);
    }

}

void qsort_median_insert(void*, size_t, size_t, _Cmpfun*);
void qsort_median_insert_iter(void*, size_t, size_t, _Cmpfun*);

int main(){
    FILE* command_file;
    FILE* unsorted_file, *sorted_file;
    int qsort_type;
    int array_length;
    char unsorted_file_name[30];
    char sorted_file_name[30];
    ELEMENT* unsorted_list, *sorted_list;
    int i,j;

    command_file=fopen("HW2_commands.txt", "r");
    fscanf(command_file, "%d", &qsort_type);
    fscanf(command_file, "%d", &array_length);
    fscanf(command_file, "%s", unsorted_file_name);
    fscanf(command_file, "%s", sorted_file_name);
    fclose(command_file);

    unsorted_file=fopen(unsorted_file_name, "rb");
    unsorted_list=(ELEMENT*)malloc(sizeof(ELEMENT)*array_length);
    sorted_list=(ELEMENT*)malloc(sizeof(ELEMENT)*array_length);
    for(i=0;i<array_length;i++){
        fscanf(unsorted_file, "%d", &(unsorted_list[i].score));
    }
    qsort(unsorted_list, array_length, sizeof(ELEMENT), my_element_score_compare);
    //c 표준 라이브러리의 qsort

    sorted_file=fopen(sorted_file_name, "wb");


    return 0;
}

