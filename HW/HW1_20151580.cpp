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

int MSS[3] = { 0, };

ELEM maxsubsum(int *, int, int);
void solve_1(int, int*);
void solve_2(int, int*);
void solve_3(int, int*);
void solve_4(int, int*);
void solve_5(int, int*);



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

				solve_2(N, arr);
				for (i = 0; i < N; i++) printf("%d ", arr[i]);
				printf("MSS is %d %d %d\n", MSS[2], MSS[0], MSS[1]);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;
	
			case 3:
				printf("%d\n", N);

				solve_3(int(sqrt(N)), arr);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;

			case 4:

				solve_4(N, arr);
				fp_output = fopen(output, "wb");
				fclose(fp_output);
				break;
			
			case 5:

				solve_5(N, arr);
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


void solve_2(int N, int* arr) {

	int local_MSS;
	int thissum;
	int i;
	int local_start = 0;
	
	MSS[1] = -1;
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
		return;
	}

	MSS[2] = local_MSS;
	return;
} //solved by kadane algorithm , O(N)

void solve_3(int N, int* arr) {
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
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = i; k < N; k++) {
				for (int q = j; q < N; q++) {
					thissum = sumtable[k][q] - sumtable[j - 1][i] - sumtable[k][i - 1] + sumtable[i - 1][j - 1];
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		delete[] sumtable[i];
	}
	delete[] sumtable;
	return;
}

void solve_4(int N, int* arr) {

	return;
}

void solve_5(int N, int* arr) {

	return;
}