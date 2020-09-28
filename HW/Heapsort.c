#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void adjust(int* , int , int );
void swap(int*, int*);

int main() {
	FILE* fp;		// HW1_config.txt file pointer
	FILE* fp_input; // input binary file
	FILE* fp_output;// ouptut binary file

	int main_loop_index, i; // for loop index var.
	int testcase;			// number of testcase

	int alg_num; // solution number
	int N;		 // input Size
	int* arr;	 // sequence


	char input[33], output[33]; // filename of input file, output file 

	fp = fopen("HW1_config.txt", "r");

	testcase = 0;
	fscanf(fp, "%d\n", &testcase);

	for (main_loop_index = 0; main_loop_index < testcase; main_loop_index++) {

		fscanf(fp, "%d %s %s\n", &alg_num, input, output);

		fp_input = fopen(input, "rb");
		fread(&N, sizeof(int), 1, fp_input);
		arr = (int*)calloc(N+1, sizeof(int));

		for (i = 1; i < N+1; i++) {
			fread(&arr[i], sizeof(int), 1, fp_input);
		} // read binary file // read binary file

		for (i = N/2; i >= 1; i--) {
			adjust(arr, i, N+1);
		} // make heap

		for (i = N-1; i > 0 ; i--) {
			swap(&arr[1], &arr[i+1]);
			adjust(arr, 1, i);
		}

		for (i = 1; i <= N; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		fclose(fp_input);

	
		free(arr);
	}
	fclose(fp);

	return 0;
}

void swap(int* a, int* b) {
	int temp;

	temp = *b;
	*b = *a;
	*a = temp;

	return;
}

void adjust(int* arr, int root, int n) {

	int rootkey;
	int child;

	rootkey = arr[root];
	child = 2 * root;
	
	while (child <= n) {
	
		if (child < n && (arr[child] < arr[child + 1])) 
			child++;
	
		if (rootkey > arr[child]) break;
		else {
			arr[child / 2] = arr[child];
			child *= 2;
		}
	}

	arr[ child / 2 ] = rootkey;

	return;
}