#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX3(A,B,C, temp) {\
if (A > B) {\
	if (A > C)\
		temp = A;\
	else\
		temp = C;\
}\
else if(B>C) {\
	if (B>A)\
		temp = B;\
	else\
		temp = A;\
}\
else if( C > A){\
	if(C > B)\
		temp = C;\
	else\
		temp = B;\
}\
}
int maxsubsum(int *, int, int, int *, int *);
int solve_1(int, int*, int*, int*);
int solve_2(int, int*, int*, int*);
int solve_3(int, int*, int*, int*);
int solve_4(int, int*, int*, int*);
int solve_5(int, int*, int*, int*);

int start, finish;

int main() {

	FILE* fp;		// HW1_config.txt file pointer
	FILE* fp_input; // input binary file
	FILE* fp_output;// ouptut binary file

	int main_loop_index, i; // for loop index var.
	int testcase;			// number of testcase
	
	int alg_num; // solution number
	int N;		 // input Size
	int* arr;	 // sequence
	int start;	 // start index of MSS
	int finish;  // finish index of MSS
	int MSS;	 // result of MSS

	char input[33], output[33]; // filename of input file, output file 
	
	fp = fopen("HW1_config.txt", "r");

	testcase = 0;
	fscanf(fp,"%d\n", &testcase);

	for (main_loop_index = 0; main_loop_index < testcase; main_loop_index++) {

		fscanf(fp, "%d %s %s\n", &alg_num, input, output);

		fp_input = fopen(input, "rb");
		fread(&N, sizeof(int), 1, fp_input);
		arr = (int*)calloc(N, sizeof(int));

		for (i = 0; i < N; i++) {
			fread(&arr[i], sizeof(int), 1, fp_input);
		} // read binary file // read binary file

		fclose(fp_input);

		start =  finish = 0;

		switch (alg_num) {
			case 1:
				MSS = solve_1(N, arr , &start, &finish);
				fp_output = fopen(output, "wb");
				for (i = 0; i < N; i++) {
					printf("%d ", arr[i]);
				}
				printf("\n");
				printf("MSS is %d %d %d\n", MSS, start, finish);
				fclose(fp_output);
				break;
			
			case 2:

				MSS = solve_2(N, arr, &start, &finish);
				for (i = 0; i < N; i++) {
					printf("%d ", arr[i]);
				}
				printf("\n");
				printf("MSS is %d %d %d\n", MSS, start, finish);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;
	
			case 3:

				MSS = solve_3(N, arr, &start, &finish);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;

			case 4:

				MSS = solve_4(N, arr, &start, &finish);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;
			
			case 5:

				MSS = solve_5(N, arr, &start, &finish);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;
			default:
				printf("err/ No solution number : %2d\n", alg_num);
		}

		free(arr);
	}
	fclose(fp);
}

int solve_1(int N, int *arr, int *start, int *finish) {
	
	int MSS;
	MSS = maxsubsum(arr, 0, N-1, start, finish);
	return MSS;
}

int maxsubsum(int* arr, int left, int right, int *start, int *finish) {

	int center, i;
	int leftmaxsum, rightmaxsum;
	int leftbordersum, cur_leftbordersum;
	int rightbordersum, cur_rightbordersum;
	int temp;
	int local_start_l = 0, local_finish_l = 0;
	int local_start_r = 0, local_finish_r = 0;
	int local_start_b = 0, local_finish_b = 0;

	if (left == right) {
		local_start_l = left;
		local_finish_l = right;
		return arr[left];
	}
	center = (left + right) / 2;

	leftmaxsum = maxsubsum(arr, left, center, &local_start_l, &local_finish_l);
	rightmaxsum = maxsubsum(arr, center + 1, right, &local_start_r, &local_finish_r);

	leftbordersum = INT_MIN; cur_leftbordersum = 0;
	local_start_b = center;
	for (i = center; i >= left; i--) {
		cur_leftbordersum += arr[i];
		if (cur_leftbordersum > leftbordersum) {

			local_start_b = i;
			leftbordersum = cur_leftbordersum;

		}
	}

	rightbordersum = INT_MIN; cur_rightbordersum = 0;
	local_finish_b = center;
	for (i = center + 1; i <= right; i++) {
		cur_rightbordersum += arr[i];
		if (cur_rightbordersum > rightbordersum) {
			
			local_finish_b = i;
			rightbordersum = cur_rightbordersum;
		}
	}

	temp = 0;
	MAX3(leftmaxsum, rightmaxsum, leftbordersum + rightbordersum, temp);

	if (temp == rightmaxsum) {
		*finish = right;
		*start = center+1;
	}
	else if (temp == (leftbordersum + rightbordersum)) {
		*finish = local_finish_b;
		*start = local_start_b;
	}
	else {
		*finish = center;
		*start = left;
	}

	return temp;

}


int solve_2(int N, int* arr, int* start, int* finish) {

	int MSS;
	int thissum;
	int i;
	int local_start = 0;
	
	*finish = -1;
	MSS = INT_MIN;
	thissum = 0;

	for (i = 0; i < N; i++) {
		thissum += arr[i];

		if (thissum > MSS) {
			MSS = thissum;
			*start = local_start; *finish = i;
		}
		else if (thissum < 0) {
			thissum = 0; 
			local_start = i+1;
		}
	}

	if (*finish == -1) { // for nonempty sequence
		MSS = arr[0];
		*start = *finish = 0;
		for (i = 0; i < N; i++) {
			if (arr[i] > MSS) { // find largest negative number among arr
				MSS = arr[i];
				*start = *finish = i;
			}
		}
	}
	else {
		return MSS;
	}

	return MSS;
} //solved by kadane algorithm , O(N)

int solve_3(int N, int* arr, int* start, int* finish) {

	return N;
}

int solve_4(int N, int* arr, int* start, int* finish) {

	return N;
}

int solve_5(int N, int* arr, int* start, int* finish) {

	return N;
}