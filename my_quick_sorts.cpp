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
		//�ǹ��� ���� �տ� �ִ� ���ҷ�
		ELEMENT* array_pointer = (ELEMENT*)arr;
		ELEMENT* smaller_than_pivot_pointer = (ELEMENT*)arr;
		int smaller_count = 0;
		//pivot���� ���� ���� ������ ����

		swap_element(pivot_pointer, array_pointer + n - 1, size);
		//ù ���ҿ� �ִ� �ǹ��� �� ������ ������

		pivot_pointer = array_pointer + n - 1;
		//���� �� ���� �ǹ��� �ִ�
		for (i = 0; i < n; i++) {
			//���� Ȯ���ϴ� ���Ҵ� i��° �ε���. ���� �̰� �ǹ����� ������ smaller_than_pivot_pointer ��ġ�� ������
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
	//8 �̸��� ������� ���ش�
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
	//���� �ǹ��� �� ���� �ִ�

	for (i = 0; i < n; i++) {
		//���� Ȯ���ϴ� ���Ҵ� i��° �ε���. ���� �̰� �ǹ����� ������ smaller_than_pivot_pointer ��ġ�� ������
		if (cmp(array_pointer + i, pivot_pointer) == -1) {
			swap_element(array_pointer + i, smaller_than_pivot_pointer, size);
			smaller_than_pivot_pointer++;
			smaller_count++;
		}
	}

	swap_element(pivot_pointer, smaller_than_pivot_pointer, size);

	qsort_median_insert(array_pointer, smaller_count, size, cmp);
	qsort_median_insert(array_pointer + smaller_count + 1, n - smaller_count - 1, size, cmp);
	//�������� ���� ����
	insertion_sort(array_pointer, n, size, cmp);
}

void qsort_median_insert_iter(void* arr, size_t n, size_t size, _Cmpfun* cmp) {
	int i;
	ELEMENT* array_pointer = (ELEMENT*)arr;
	//arr�� ���� ������
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
		//���� �ǹ��� �� ���� �ִ�

		for (i = 0; i < n; i++) {
			//���� Ȯ���ϴ� ���Ҵ� i��° �ε���. ���� �̰� �ǹ����� ������ smaller_than_pivot_pointer ��ġ�� ������
			if (cmp(array_pointer + i, pivot_pointer) == -1) {
				swap_element(array_pointer + i, smaller_than_pivot_pointer, size);
				smaller_than_pivot_pointer++;
				smaller_count++;
			}
		}
		//pivot ���Ҵ� smaller_count+1 �ε����� ��ġ�Ѵ�.
		swap_element(pivot_pointer, smaller_than_pivot_pointer, size);

		if (smaller_count < n / 2) {
			//������ �� ª��
			qsort_median_insert_iter(array_pointer, smaller_count, size, cmp);
			//������ ���� ó���� �� �� �������� ����
			array_pointer = array_pointer + smaller_count + 1;
			n = n - smaller_count - 1;
		}
		else {
			//������ �� ª��
			qsort_median_insert_iter(array_pointer + smaller_count + 1, n - smaller_count - 1, size, cmp);
			n = smaller_count;
		}

	}

}