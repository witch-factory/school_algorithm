#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "my_quick_sorts.h"

void init_score_array(ELEMENT* arr, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		arr[i].score = i;
		arr[i].data[0] = i + 1;
		arr[i].data[1] = i + 2;
		arr[i].data[2] = i + 3;
		itoa(i, arr[i].comments, 16);
	}

	srand((unsigned int)time(NULL));

	for (i = n - 1; i >= 1; i--) {
		j = rand() % (i + 1);
		//random shuffle
		swap_element(arr + i, arr + j, sizeof(ELEMENT));
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

int main() {
	FILE* command_file;
	FILE* unsorted_file, *sorted_file;
	int qsort_type;
	int array_length;
	char unsorted_file_name[50];
	char sorted_file_name[50];
	ELEMENT* unsorted_list;
	int i, j;

	command_file=fopen("HW2_commands.txt", "r");
	fscanf(command_file, "%d", &qsort_type);
	fscanf(command_file, "%d", &array_length);
	fscanf(command_file, "%s", unsorted_file_name);
	fscanf(command_file, "%s", sorted_file_name);
	fclose(command_file);

	unsorted_file = fopen(unsorted_file_name, "rb");
	unsorted_list = (ELEMENT*)malloc(sizeof(ELEMENT) * array_length);

	for (i = 0; i < array_length; i++) {
		fread(unsorted_list + i, sizeof(ELEMENT), 1, unsorted_file);
	}
	fclose(unsorted_file);

	if (qsort_type == 1) {
		qsort(unsorted_list, array_length, sizeof(ELEMENT), my_element_score_compare);
		//c 표준 라이브러리의 qsort
	}
	else if (qsort_type == 21) {
		qsort_orig(unsorted_list, array_length, sizeof(ELEMENT), my_element_score_compare);
	}
	else if (qsort_type == 22) {
		qsort_median_insert(unsorted_list, array_length, sizeof(ELEMENT), my_element_score_compare);
	}
	else if (qsort_type == 23) {
		qsort_median_insert_iter(unsorted_list, array_length, sizeof(ELEMENT), my_element_score_compare);
	}

	sorted_file = fopen(sorted_file_name, "wb");
	for (i = 0; i < array_length; i++) {
		fwrite(unsorted_list + i, sizeof(ELEMENT), 1, sorted_file);
	}
	fclose(sorted_file);
	free(unsorted_list);

	return 0;
}