#include <iostream>
#include <fstream>

using namespace std;

int main() {

	ifstream fin;
	fin.open("number.txt");

	int n;
	fin >> n;

	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> arr[i];
	}

	int maxsum = 0 , thissum = 0;
	int start = 0 , temp_start = 0;
	int finish = 0 , temp_finish = 0;
	
	for (int i = 0; i < n; i++) {
		
		thissum += arr[i];

		if (thissum > maxsum) {
			maxsum = thissum;
			start = temp_start;
			finish = i;
		}
		else if( thissum < 0 ){
			thissum = 0;
			temp_start = 0;
		}

	}
	
	cout << "Max Subsequence Sum by kadane algorithm is " << maxsum << endl;
	cout << start << " to " << finish << endl;
	delete[] arr;

	return 0;
}