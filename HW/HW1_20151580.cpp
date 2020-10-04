#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include <cmath>
#include <windows.h>

#define CHECK_TIME_START QueryPerformanceFrequency ((_LARGE_INTEGER*)&freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a=(float)((float) (end - start)/freq)

using namespace std;

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
typedef struct elem {
	int start;
	int finish;
	int value;
}ELEM;

typedef struct elem_2d {
	int start_c;
	int finish_c;
	int start_r;
	int finish_r;
	int value;
}ELEM_2D;

ELEM maxsubsum(int *, int, int);
ELEM solve_1(int, int*);
ELEM solve_2(int, int*);
ELEM_2D solve_3(int, int*);
ELEM_2D solve_4(int, int*);
ELEM_2D solve_5(int, int*);

float resulttime;

int main() {

	FILE* fp;		// HW1_config.txt file pointer
	FILE* fp_input; // input binary file
	FILE* fp_output;// ouptut binary file
	FILE* result_file;

	int main_loop_index, i,j; // for loop index var.
	int testcase;			// number of testcase

	int alg_num; // solution number
	int N;		 // input Size
	int* arr;	 // sequence
	__int64 start, freq, end;

	char input[33], output[33]; // filename of input file, output file 
	
	fp = fopen("HW1_config.txt", "r");
	result_file = fopen("result.txt", "w");
	testcase = 0;
	fscanf(fp,"%d\n", &testcase);

	for (main_loop_index = 0; main_loop_index < testcase; main_loop_index++) {

		fscanf(fp, "%d %s %s\n", &alg_num, input, output);

		fp_input = fopen(input, "rb");
		fread(&N, sizeof(int), 1, fp_input);
	

		if (alg_num > 2) {
			int arrsize = N * N;

			arr = (int*)calloc( arrsize , sizeof(int));
			for (i = 0; i <arrsize; i++) {
				fread(&arr[i], sizeof(int), 1, fp_input);
			}

		}
		else if (alg_num > 0 && alg_num < 3) {
			arr = (int*)calloc(N, sizeof(int));
			for (i = 0; i < N; i++) {
				fread(&arr[i], sizeof(int), 1, fp_input);
			}
		}
		else {
			continue;
		}

		fclose(fp_input);

		ELEM result_1D;
		ELEM_2D result_2D;
		switch (alg_num) {
			case 1:
				
				CHECK_TIME_START;
				result_1D = solve_1(N, arr);
				CHECK_TIME_END(resulttime);
				
				printf("MSS is %d %d %d\n", result_1D.value, result_1D.start, result_1D.finish);
				printf("N :: %d / time :: %f\n\n", N, resulttime);

				fprintf(result_file,"MSS is %d %d %d\n", result_1D.value, result_1D.start, result_1D.finish);
				fprintf(result_file, "N :: %d / time :: %f\n\n", N, resulttime);

				fp_output = fopen(output, "wb");
				fwrite(&result_1D.value, sizeof(int), 1, fp_output);
				fwrite(&result_1D.start, sizeof(int), 1, fp_output);
				fwrite(&result_1D.finish, sizeof(int), 1, fp_output);

				fclose(fp_output);

				break;
			
			case 2:
				CHECK_TIME_START;
				result_1D = solve_2(N, arr);
				CHECK_TIME_END(resulttime);

				printf("MSS is %d %d %d\n", result_1D.value, result_1D.start, result_1D.finish);
				printf("N :: %d / time :: %f\n\n", N, resulttime);

				fprintf(result_file, "MSS is %d %d %d\n", result_1D.value, result_1D.start, result_1D.finish);
				fprintf(result_file, "N :: %d / time :: %f\n\n", N, resulttime);

				fp_output = fopen(output, "wb");
				fwrite(&result_1D.value, sizeof(int), 1, fp_output);
				fwrite(&result_1D.start, sizeof(int), 1, fp_output);
				fwrite(&result_1D.finish, sizeof(int), 1, fp_output);
				
				fclose(fp_output);
				
				break;
	
			case 3:
				
				CHECK_TIME_START;
				result_2D = solve_3(N, arr);
				CHECK_TIME_END(resulttime);

				printf("MSS is %d index: %d %d %d %d\n", result_2D.value, result_2D.start_r, result_2D.start_c, result_2D.finish_r, result_2D.finish_c);
				printf("N :: %d / time :: %f\n\n", N, resulttime);

				fprintf(result_file,"MSS is %d index: %d %d %d %d\n", result_2D.value, result_2D.start_r, result_2D.start_c, result_2D.finish_r, result_2D.finish_c);
				fprintf(result_file,"N :: %d / time :: %f\n\n", N, resulttime);

				fp_output = fopen(output, "wb");

				fwrite(&result_2D.value, sizeof(int), 1, fp_output);
				fwrite(&result_2D.start_r,sizeof(int), 1, fp_output);
				fwrite(&result_2D.start_c, sizeof(int), 1, fp_output);
				fwrite(&result_2D.finish_r, sizeof(int), 1, fp_output);
				fwrite(&result_2D.finish_c, sizeof(int), 1, fp_output);

				fclose(fp_output);
		
				break;

			case 4:
	
				CHECK_TIME_START;
				result_2D = solve_4(N, arr);
				CHECK_TIME_END(resulttime);
				
				printf("MSS is %d index: %d %d %d %d\n", result_2D.value, result_2D.start_r, result_2D.start_c, result_2D.finish_r, result_2D.finish_c);
				printf("N :: %d / time :: %f\n\n", N, resulttime);
				
				fprintf(result_file, "MSS is %d index: %d %d %d %d\n", result_2D.value, result_2D.start_r, result_2D.start_c, result_2D.finish_r, result_2D.finish_c);
				fprintf(result_file, "N :: %d / time :: %f\n\n", N, resulttime);

				fp_output = fopen(output, "wb");

				fwrite(&result_2D.value, sizeof(int), 1, fp_output);
				fwrite(&result_2D.start_r, sizeof(int), 1, fp_output);
				fwrite(&result_2D.start_c, sizeof(int), 1, fp_output);
				fwrite(&result_2D.finish_r, sizeof(int), 1, fp_output);
				fwrite(&result_2D.finish_c, sizeof(int), 1, fp_output);

				fclose(fp_output);
				
				break;
			
			case 5:
	
				CHECK_TIME_START;
				result_2D = solve_5(N, arr);
				CHECK_TIME_END(resulttime);
				
				printf("MSS is %d index: %d %d %d %d\n", result_2D.value, result_2D.start_r, result_2D.start_c, result_2D.finish_r, result_2D.finish_c);
				printf("N :: %d / time :: %f\n\n", N, resulttime);

				fprintf(result_file, "MSS is %d index: %d %d %d %d\n", result_2D.value, result_2D.start_r, result_2D.start_c, result_2D.finish_r, result_2D.finish_c);
				fprintf(result_file, "N :: %d / time :: %f\n\n", N, resulttime);

				fp_output = fopen(output, "wb");

				fwrite(&result_2D.value, sizeof(int), 1, fp_output);
				fwrite(&result_2D.start_r, sizeof(int), 1, fp_output);
				fwrite(&result_2D.start_c, sizeof(int), 1, fp_output);
				fwrite(&result_2D.finish_r, sizeof(int), 1, fp_output);
				fwrite(&result_2D.finish_c, sizeof(int), 1, fp_output);
				
				fclose(fp_output);
				
				break;
			default:
				printf("err/ No solution number : %2d\n", alg_num);
		}

		free(arr);
	}
	fclose(fp);
	fclose(result_file);
}

ELEM solve_1(int N, int *arr) {
	
	ELEM result;
	result = maxsubsum(arr, 0, N - 1);
	
	return result;
}
ELEM maxsubsum(int* arr, int left, int right) {

	int center, i;
	int leftbordersum, cur_leftbordersum;
	int rightbordersum, cur_rightbordersum;
	int temp;
	ELEM l, r, border;

	if (left == right) {
	
		l.start = left;
		l.finish = left;
		l.value = arr[left];
		return l;
	}
	center = (left + right) / 2;

	l = maxsubsum(arr, left, center);
	r = maxsubsum(arr, center + 1, right);

	leftbordersum = INT_MIN; cur_leftbordersum = 0;
	border.start = border.finish = center;
	for (i = center; i >= left; i--) {
		cur_leftbordersum += arr[i];
		if (cur_leftbordersum > leftbordersum) {
			border.start = i;
			leftbordersum = cur_leftbordersum;

		}
	}

	rightbordersum = INT_MIN; cur_rightbordersum = 0;
	for (i = center + 1; i <= right; i++) {
		cur_rightbordersum += arr[i];
		if (cur_rightbordersum > rightbordersum) {
			border.finish = i;
			rightbordersum = cur_rightbordersum;
		}
	}

	temp = 0;
	MAX3(l.value , r.value, leftbordersum + rightbordersum, temp);

	if (temp == r.value) {
		return r;
	}
	else if (temp == leftbordersum + rightbordersum) {
		border.value = temp;
		return border;
	}
	else {
		return l;
	}


}
ELEM solve_2(int N, int* arr) {

	int local_MSS;
	int thissum;
	int i;
	int local_start = 0;
	ELEM result;

	result.value = INT_MIN;
	result.finish = -1;
	result.start = -1; // initializing

	local_MSS = INT_MIN;
	thissum = 0;

	for (i = 0; i < N; i++) {
		thissum += arr[i];

		if (thissum < 0) {
			thissum = 0;
			local_start = i + 1;
			continue;
		}

		if (thissum > local_MSS) {
			local_MSS = thissum;
			result.start = local_start; 
			result.finish = i;
		}
	
	}

	if (result.finish == -1) { // for nonempty sequence
		local_MSS = arr[0];
		result.start = result.finish = 0;
		for (i = 0; i < N; i++) {
			if (arr[i] > local_MSS) { // find largest negative number among arr
				local_MSS = arr[i];
				result.start = result.finish = i;
			}
		}
	}
	else {
		result.value = local_MSS;
		
		//printf("MSS : %d , start : %d, finish %d\n", result.value, result.start, result.finish);
		
		return result;
	}
	result.value = local_MSS;
	return result;
} //solved by kadane algorithm , O(N)
ELEM_2D solve_3(int N, int* arr) {
	int **sumtable = new int*[N];

	
	for (int i = 0; i < N; i++) {
		sumtable[i] = new int[N];
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			sumtable[i][j] = 0;
	}

	sumtable[0][0] = arr[0];
	for (int i = 1; i < N; i++) sumtable[i][0] = sumtable[i-1][0]+ arr[i*N];
	for (int i = 1; i < N; i++) sumtable[0][i] = sumtable[0][i - 1] + arr[i];


	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			sumtable[i][j] = sumtable[i - 1][j] + sumtable[i][j - 1] - sumtable[i - 1][j - 1] + arr[i*N+j];
		}
	}
	int thissum = 0;
	int maxsum = INT_MIN;
	
	ELEM_2D result;
	result.start_c = 0, result.finish_c = 0, result.start_r = 0, result.finish_r = 0;

	for (int i = 0; i < N; i++) { // start of row
		for (int j = 0; j < N; j++) { // start of col

			for (int q = i; q < N; q++) { //finish of row
				for (int k = j; k < N; k++) { // finish of col

					if (i == 0 || j == 0) {

						if (i == 0 && j == 0) {
							thissum = sumtable[q][k];
						}
						else if (i == 0) {
							thissum = sumtable[q][k] - sumtable[q][j-1];
						}
						else if (j == 0) {
							thissum = sumtable[q][k] - sumtable[i-1][k];
						}
					}
					else {
						thissum = sumtable[q][k] - sumtable[q][j-1] - sumtable[i-1][k] + sumtable[i-1][j-1];
					}

					if (thissum > maxsum) {
						maxsum = thissum;
						result.finish_c = k;
						result.finish_r = q;
						result.start_c = j;
						result.start_r = i;
					}
				}
			}
		}
	}

	result.value = maxsum;

	for (int i = 0; i < N; i++) {
		delete[] sumtable[i];
	}
	delete[] sumtable;
	return result;
}
ELEM_2D solve_4(int N, int* arr) {
	
	int maxsum = INT_MIN;

	int thissum = 0;
	int* temp = new int[N];

	int left, right;


	ELEM result;
	ELEM_2D rresult;
	for (left = 0; left < N; left++) {

		for (int i = 0; i < N; i++) temp[i] = 0;

		for (right = left; right < N; right++) {

			for (int k = 0; k < N; k++) {
				temp[k] += arr[k * N + right];
			}

			result = solve_1(N, temp);


			if (result.value > maxsum) {
				maxsum = result.value;
				rresult.start_c = left;
				rresult.finish_c = right;
				rresult.start_r = result.start;
				rresult.finish_r = result.finish;
			}
		}
	}
	rresult.value = maxsum;

	delete[] temp;
	return rresult;
	
}
ELEM_2D solve_5(int N, int* arr) {

	int maxsum = INT_MIN;
	
	int thissum = 0;
	int* temp = new int[N];
	
	int left, right;
	

	ELEM result;
	ELEM_2D rresult;
	for ( left = 0; left < N; left++) {

		for (int i = 0; i < N; i++) temp[i] = 0;

		for (right = left; right < N; right++) {

			for (int k = 0; k < N; k++) {
				temp[k] += arr[k * N + right];
			}

			result = solve_2(N, temp);

			if (result.value > maxsum) {
				maxsum = result.value;
				rresult.start_c = left;
				rresult.finish_c = right;
				rresult.start_r = result.start;
				rresult.finish_r = result.finish;
			}
		}
	}

	rresult.value = maxsum;

	delete[] temp;
	return rresult;
}