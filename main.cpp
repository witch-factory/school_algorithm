#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ELEMENT_DATA_LENGTH 3
#define ELEMENT_COMMENT_LENGTH 16

typedef struct {
	unsigned int score;
	float data[3];
	char comments[16];
}ELEMENT;

typedef int _Cmpfun(const void *, const void *);

void copy_element(ELEMENT* dist, ELEMENT* source) {
	int i;
	dist->score=source->score;
	for(i=0; i<ELEMENT_DATA_LENGTH; i++) {
		dist->data[i]=source->data[i];
	}
	for(i=0; i<ELEMENT_COMMENT_LENGTH; i++) {
		dist->comments[i]=source->comments[i];
	}
}

void init_score_array(unsigned int* data, int n) {
	int i, j;
	unsigned int tmp;
	for(i=0; i<n; i++) {
		data[i]=i;
	}

	srand((unsigned int)time(NULL));

	for(i = n - 1; i >= 1; i--) {
		j = rand() % (i + 1);

		tmp = data[i]; data[i] = data[j]; data[j] = tmp;
	}
}

int my_element_score_compare(const void *a, const void *b) {
	ELEMENT *elem_a, *elem_b;
	elem_a=(ELEMENT*)a;
	elem_b=(ELEMENT*)b;
	if(elem_a->score==elem_b->score) {
		return 0;
	}
	else if((elem_a->score)<(elem_b->score)) {
		//뒤쪽이 더 크면 -1
		return -1;
	}
	else {
		return 1;
	}
}

void qsort_orig(void* arr, size_t n, size_t size, _Cmpfun* cmp) {
	//printf("%d ", n);
	if(n>1) {
		int i, j;
		ELEMENT* pivot=(ELEMENT*)arr;
		ELEMENT* array_pointer=(ELEMENT*)arr;
		//맨 왼쪽 인덱스의 점수를 따 온다
		int pivot_position=0;
		for(i=0; i<n; i++) {
			if(my_element_score_compare(array_pointer+i, pivot)==-1) {
				pivot_position++;
				//pivot보다 더 작은 것들의 수를 센다.
				//pivot보다 크거나 같은건 right에 들어갈것
			}
		}
		ELEMENT* left_array=(ELEMENT*)malloc(size*pivot_position);
		ELEMENT* right_array=(ELEMENT*)malloc(size*(n-pivot_position));
		//pivot 위치는 left, right array의 사이
		//printf("%d\n", pivot_position);
		int left_cursor=0, right_cursor=0;
		for(i=0; i<n; i++) {
			//pivot을 기준으로 작은 배열, 큰 배열 나눔
			if(my_element_score_compare(array_pointer+i, pivot)==-1) {
				memcpy(left_array+left_cursor, array_pointer+i, size);
				left_cursor++;
			}
			else {
				memcpy(right_array+right_cursor, array_pointer+i, size);
				right_cursor++;
			}
		}

		memcpy(array_pointer, left_array, size*pivot_position);
		memcpy(array_pointer+pivot_position, right_array, size*(n-pivot_position));

		qsort_orig(array_pointer, pivot_position, size, cmp);
		qsort_orig(array_pointer+pivot_position+1, n-pivot_position-1, size, cmp);
	}

}

void insertion_sort(void* arr, int n);

void qsort_median_insert(void*, size_t, size_t, _Cmpfun*);
void qsort_median_insert_iter(void*, size_t, size_t, _Cmpfun*);

int main() {
	int i, j;
	unsigned int arr[105];
	init_score_array(arr, 50);
	for(i=0; i<50; i++) {
		printf("%d\n", arr[i]);
	}
	printf("\n");

	ELEMENT unsorted_list[105];
	for(i=0; i<50; i++) {
		unsorted_list[i].score=arr[i];
	}
	qsort_orig(unsorted_list, 50, sizeof(ELEMENT), my_element_score_compare);
	for(i=0; i<50; i++) {
		printf("%d\n", unsorted_list[i].score);
	}

	/*FILE* command_file;
	FILE* unsorted_file, *sorted_file;
	int qsort_type;
	int array_length;
	char unsorted_file_name[30];
	char sorted_file_name[30];
	ELEMENT* unsorted_list, *sorted_list;
	int i, j;

	command_file=fopen("HW2_commands.txt", "r");
	fscanf(command_file, "%d", &qsort_type);
	fscanf(command_file, "%d", &array_length);
	fscanf(command_file, "%s", unsorted_file_name);
	fscanf(command_file, "%s", sorted_file_name);
	fclose(command_file);

	unsorted_file=fopen(unsorted_file_name, "rb");
	unsorted_list=(ELEMENT*)malloc(sizeof(ELEMENT)*array_length);
	sorted_list=(ELEMENT*)malloc(sizeof(ELEMENT)*array_length);
	for(i=0; i<array_length; i++) {
		fscanf(unsorted_file, "%d", &(unsorted_list[i].score));
	}
	qsort(unsorted_list, array_length, sizeof(ELEMENT), my_element_score_compare);
	//c 표준 라이브러리의 qsort

	sorted_file=fopen(sorted_file_name, "wb");*/


	return 0;
}
