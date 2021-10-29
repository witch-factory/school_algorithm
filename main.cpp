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

typedef int _Cmpfun(const void*, const void*);

void copy_element(ELEMENT* dist, ELEMENT* source) {
	int i;
	dist->score = source->score;
	for (i = 0; i < ELEMENT_DATA_LENGTH; i++) {
		dist->data[i] = source->data[i];
	}
	for (i = 0; i < ELEMENT_COMMENT_LENGTH; i++) {
		dist->comments[i] = source->comments[i];
	}
}

void init_score_array(unsigned int* data, int n) {
	int i, j;
	unsigned int tmp;
	for (i = 0; i < n; i++) {
		data[i] = i;
	}

	srand((unsigned int)time(NULL));

	for (i = n - 1; i >= 1; i--) {
		j = rand() % (i + 1);

		tmp = data[i]; data[i] = data[j]; data[j] = tmp;
	}
}

int my_element_score_compare(const void* a, const void* b) {
	ELEMENT* elem_a, * elem_b;
	elem_a = (ELEMENT*)a;
	elem_b = (ELEMENT*)b;
	if (elem_a->score == elem_b->score) {
		return 0;
	}
	else if ((elem_a->score) < (elem_b->score)) {
		//뒤쪽이 더 크면 -1
		return -1;
	}
	else {
		return 1;
	}
}

void qsort_orig(void* arr, size_t n, size_t size, _Cmpfun* cmp) {
	//printf("%d ", n);
	if (n > 1) {
		int i, j;
		ELEMENT* pivot_pointer = (ELEMENT*)arr;
		ELEMENT* array_pointer = (ELEMENT*)arr;
		ELEMENT* buf = (ELEMENT*)malloc(size);
		ELEMENT* smaller_than_pivot_pointer = (ELEMENT*)arr;
		int smaller_count = 0;
		//pivot보다 작은 원소 개수를 센다

		memcpy(buf, pivot_pointer, size);
		memcpy(pivot_pointer, array_pointer + n - 1, size);
		memcpy(array_pointer + n - 1, buf, size);
		//첫 원소에 있던 피벗을 맨 끝으로 보낸다

		pivot_pointer = array_pointer + n - 1;
		//이제 맨 끝에 피벗이 있다
		for (i = 0; i < n; i++) {
			//현재 확인하는 원소는 i번째 인덱스. 만약 이게 피벗보다 작으면 smaller_than_pivot_pointer 위치로 보낸디
			if (cmp(array_pointer + i, pivot_pointer) == -1) {
				memcpy(buf, array_pointer + i, size);
				memcpy(array_pointer + i, smaller_than_pivot_pointer, size);
				memcpy(smaller_than_pivot_pointer, buf, size);
				smaller_than_pivot_pointer++;
				smaller_count++;
			}
		}

		memcpy(buf, pivot_pointer, size);
		memcpy(pivot_pointer, smaller_than_pivot_pointer, size);
		memcpy(smaller_than_pivot_pointer, buf, size);

		qsort_orig(array_pointer, smaller_count, size, cmp);
		qsort_orig(array_pointer + smaller_count + 1, n - smaller_count - 1, size, cmp);
	}

}

void insertion_sort(void* arr, size_t n, size_t size, _Cmpfun* cmp) {
	ELEMENT* array_pointer = (ELEMENT*)arr;
	int i, j;
	ELEMENT* buf = (ELEMENT*)malloc(size);

	for (i = 1; i < n; i++) {
		memcpy(buf, array_pointer + i, size);
		j = i;
		while ((j > 0) && cmp(buf, array_pointer + j - 1)==-1) {
			memcpy(array_pointer + j, array_pointer + j - 1, size);
			j--;
		}
		memcpy(array_pointer + j, buf, size);
	}
}

void qsort_median_insert(void*, size_t, size_t, _Cmpfun*);
void qsort_median_insert_iter(void*, size_t, size_t, _Cmpfun*);

int main() {

	int n;
	int i, j;
	int arr[1005];
	//init_score_array(arr, 10);
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", arr+i);
	}

	ELEMENT unsorted_list[1005];
	for (i = 0; i < n; i++) {
		unsorted_list[i].score = arr[i];
	}
	insertion_sort(unsorted_list, n, sizeof(ELEMENT), my_element_score_compare);
	for (i = 0; i < n; i++) {
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
