#pragma once
typedef int _Cmpfun(const void*, const void*);
typedef struct {
	unsigned int score;
	float data[3];
	char comments[16];
}ELEMENT;

void swap_element(ELEMENT* a, ELEMENT* b, size_t size);
void qsort_orig(void* arr, size_t n, size_t size, _Cmpfun* cmp);
void qsort_median_insert(void* arr, size_t n, size_t size, _Cmpfun* cmp);
void qsort_median_insert_iter(void* arr, size_t n, size_t size, _Cmpfun* cmp);