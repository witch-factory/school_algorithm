#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	unsigned int score;
	float data[3];
	char comments[16];
}ELEMENT;

typedef int _Cmpfun(const void*, const void*);



void swap_element(ELEMENT* a, ELEMENT* b, size_t size) {
	ELEMENT* buf = (ELEMENT*)malloc(size);
	memcpy(buf, a, size);
	memcpy(a, b, size);
	memcpy(b, buf, size);
	free(buf);
}

void qsort_orig(void* arr, size_t n, size_t size, _Cmpfun* cmp) {
	//printf("%d ", n);
	if (n > 1) {
		int i;
		ELEMENT* pivot_pointer = (ELEMENT*)arr;
		//피벗은 가장 앞에 있는 원소로
		ELEMENT* array_pointer = (ELEMENT*)arr;
		ELEMENT* smaller_than_pivot_pointer = (ELEMENT*)arr;
		int smaller_count = 0;
		//pivot보다 작은 원소 개수를 센다

		swap_element(pivot_pointer, array_pointer + n - 1, size);
		//첫 원소에 있던 피벗을 맨 끝으로 보낸다

		pivot_pointer = array_pointer + n - 1;
		//이제 맨 끝에 피벗이 있다
		for (i = 0; i < n; i++) {
			//현재 확인하는 원소는 i번째 인덱스. 만약 이게 피벗보다 작으면 smaller_than_pivot_pointer 위치로 보낸디
			if (cmp(array_pointer + i, pivot_pointer) == -1) {
				swap_element(array_pointer + i, smaller_than_pivot_pointer, size);
				smaller_than_pivot_pointer++;
				smaller_count++;
			}
		}

		swap_element(pivot_pointer, smaller_than_pivot_pointer, size);

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
		while ((j > 0) && cmp(buf, array_pointer + j - 1) == -1) {
			memcpy(array_pointer + j, array_pointer + j - 1, size);
			j--;
		}
		memcpy(array_pointer + j, buf, size);
	}
}



void qsort_median_insert(void* arr, size_t n, size_t size, _Cmpfun* cmp) {
	int i;
	if (n <= 8) { return; }
	//8 미만의 사이즈는 놔준다
	ELEMENT* array_pointer = (ELEMENT*)arr;
	ELEMENT* pivot_pointer;
	ELEMENT* left_pointer = array_pointer;
	ELEMENT* right_pointer = array_pointer + (n - 1);
	ELEMENT* median_pointer = array_pointer + (n / 2);
	ELEMENT* smaller_than_pivot_pointer = (ELEMENT*)arr;
	int smaller_count = 0;

	if (cmp(left_pointer, median_pointer) == 1) {
		swap_element(left_pointer, median_pointer, size);
	}
	if (cmp(median_pointer, right_pointer) == 1) {
		swap_element(median_pointer, right_pointer, size);
	}
	if (cmp(left_pointer, median_pointer) == 1) {
		swap_element(left_pointer, median_pointer, size);
	}

	pivot_pointer = median_pointer;
	swap_element(pivot_pointer, array_pointer + n - 1, size);
	pivot_pointer = array_pointer + n - 1;
	//이제 피벗은 맨 끝에 있다

	for (i = 0; i < n; i++) {
		//현재 확인하는 원소는 i번째 인덱스. 만약 이게 피벗보다 작으면 smaller_than_pivot_pointer 위치로 보낸디
		if (cmp(array_pointer + i, pivot_pointer) == -1) {
			swap_element(array_pointer + i, smaller_than_pivot_pointer, size);
			smaller_than_pivot_pointer++;
			smaller_count++;
		}
	}

	swap_element(pivot_pointer, smaller_than_pivot_pointer, size);

	qsort_median_insert(array_pointer, smaller_count, size, cmp);
	qsort_median_insert(array_pointer + smaller_count + 1, n - smaller_count - 1, size, cmp);
	//마지막에 삽입 정렬
	insertion_sort(array_pointer, n, size, cmp);
}

void qsort_median_insert_iter(void* arr, size_t n, size_t size, _Cmpfun* cmp) {
	int i;
	ELEMENT* array_pointer = (ELEMENT*)arr;
	//arr의 시작 포인터
	ELEMENT* pivot_pointer;
	ELEMENT* left_pointer = array_pointer;
	ELEMENT* right_pointer = array_pointer + (n - 1);
	ELEMENT* median_pointer = array_pointer + (n / 2);
	ELEMENT* smaller_than_pivot_pointer = array_pointer;
	int smaller_count = 0;

	while (n > 1) {
		left_pointer = array_pointer;
		right_pointer = array_pointer + (n - 1);
		median_pointer = array_pointer + (n / 2);
		smaller_than_pivot_pointer = array_pointer;
		smaller_count = 0;

		if (cmp(left_pointer, median_pointer) == 1) {
			swap_element(left_pointer, median_pointer, size);
		}
		if (cmp(median_pointer, right_pointer) == 1) {
			swap_element(median_pointer, right_pointer, size);
		}
		if (cmp(left_pointer, median_pointer) == 1) {
			swap_element(left_pointer, median_pointer, size);
		}

		pivot_pointer = median_pointer;
		swap_element(pivot_pointer, array_pointer + n - 1, size);
		pivot_pointer = array_pointer + n - 1;
		//이제 피벗은 맨 끝에 있다

		for (i = 0; i < n; i++) {
			//현재 확인하는 원소는 i번째 인덱스. 만약 이게 피벗보다 작으면 smaller_than_pivot_pointer 위치로 보낸디
			if (cmp(array_pointer + i, pivot_pointer) == -1) {
				swap_element(array_pointer + i, smaller_than_pivot_pointer, size);
				smaller_than_pivot_pointer++;
				smaller_count++;
			}
		}
		//pivot 원소는 smaller_count+1 인덱스에 위치한다.
		swap_element(pivot_pointer, smaller_than_pivot_pointer, size);

		if (smaller_count < n / 2) {
			//앞쪽이 더 짧다
			qsort_median_insert_iter(array_pointer, smaller_count, size, cmp);
			//앞쪽을 먼저 처리해 준 후 뒤쪽으로 가자
			array_pointer = array_pointer + smaller_count + 1;
			n = n - smaller_count - 1;
		}
		else {
			//뒤쪽이 더 짧다
			qsort_median_insert_iter(array_pointer + smaller_count + 1, n - smaller_count - 1, size, cmp);
			n = smaller_count;
		}

	}

}