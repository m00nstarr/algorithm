#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include <cmath>

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

int MSS[3] = { 0, };
int MSS_2D[5] = { 0, };

ELEM maxsubsum(int *, int, int);
void solve_1(int, int*);
int solve_2(int, int*);
ELEM_2D solve_3(int, int*);
void solve_4(int, int*);
void solve_5(int, int*);



int main() {

	FILE* fp;		// HW1_config.txt file pointer
	FILE* fp_input; // input binary file
	FILE* fp_output;// ouptut binary file

	int main_loop_index, i; // for loop index var.
	int testcase;			// number of testcase
	
	int temp;
	int alg_num; // solution number
	int N;		 // input Size
	int* arr;	 // sequence

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

		switch (alg_num) {
			case 1:
				solve_1(N, arr);
				for (i = 0; i < N; i++) printf("%d ", arr[i]);
				fp_output = fopen(output, "wb");
				printf("MSS is %d %d %d\n", MSS[2], MSS[0], MSS[1]);
				fclose(fp_output);
				break;
			
			case 2:

				temp = solve_2(N, arr);
				for (i = 0; i < N; i++) printf("%d ", arr[i]);
				printf("MSS is %d %d %d\n", MSS[2], MSS[0], MSS[1]);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;
	
			case 3:
				ELEM_2D result;

				result = solve_3(int(sqrt(N)), arr);

				printf("MSS is %d index: %d %d %d %d\n", result.value, result.start_r, result.start_c, result.finish_r, result.finish_c);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;

			case 4:

				solve_4(N, arr);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;
			
			case 5:

				solve_5(sqrt(N), arr);
				fp_output = fopen(output, "wb");
				printf("MSS is %d\n", MSS[2]);

				fclose(fp_output);
				break;
			default:
				printf("err/ No solution number : %2d\n", alg_num);
		}

		free(arr);
	}
	fclose(fp);
}

void solve_1(int N, int *arr) {
	
	ELEM result;
	result = maxsubsum(arr, 0, N - 1);
	
	MSS[0] = result.start;
	MSS[1] = result.finish;
	MSS[2] = result.value;
	
	return;
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


int solve_2(int N, int* arr) {

	int local_MSS;
	int thissum;
	int i;
	int local_start = 0;
	
	MSS[2] = INT_MIN;
	MSS[1] = -1;
	MSS[0] = -1; // initializing

	local_MSS = INT_MIN;
	thissum = 0;

	for (i = 0; i < N; i++) {
		thissum += arr[i];

		if (thissum > local_MSS) {
			local_MSS = thissum;
			MSS[0] = local_start; MSS[1] = i;
		}
		else if (thissum < 0) {
			thissum = 0; 
			local_start = i+1;
		}
	}

	if (MSS[1] == -1) { // for nonempty sequence
		local_MSS = arr[0];
		MSS[0] = MSS[1] = 0;
		for (i = 0; i < N; i++) {
			if (arr[i] > local_MSS) { // find largest negative number among arr
				local_MSS = arr[i];
				MSS[0] = MSS[1] = i;
			}
		}
	}
	else {
		MSS[2] = local_MSS;
		return local_MSS;
	}

	MSS[2] = local_MSS;
	return local_MSS;
} //solved by kadane algorithm , O(N)

ELEM_2D solve_3(int N, int* arr) {
	int **sumtable = new int*[N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i * N + j] << " ";
		}
		cout << endl;
	}
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
							thissum = sumtable[q][k] - sumtable[q][j];
						}
						else if (j == 0) {
							thissum = sumtable[q][k] - sumtable[i][k];
						}
					}
					else {
						thissum = sumtable[q][k] - sumtable[q][j] - sumtable[i][k] + sumtable[i][j];
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

void solve_4(int N, int* arr) {

	return;
}

void solve_5(int N, int* arr) {

	int maxsum = INT_MIN;
	ELEM_2D result;
	
	int thissum = 0;
	int* temp = new int[N];


	for (int left = 0; left < N; left++) {

		for (int i = 0; i < N; i++) temp[i] = 0;

		for (int right = left; right < N; right++) {
			
			for (int i = 0; i < N; i++) {
				temp[i] += arr[i*N+ right];
			}

			int result = solve_2(N, temp);
			
			if (result > maxsum) maxsum = result;
		}
	}
	printf("maxsum : %d\n ", maxsum);

	delete[] temp;
	return;
}