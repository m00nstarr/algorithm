// Program to find maximum sum subarray  
// in a given 2D array  
#include <iostream>  
using namespace std;

int N;
// Implementation of Kadane's algorithm for  
// 1D array. The function returns the maximum  
// sum and stores starting and ending indexes  
// of the maximum sum subarray at addresses  
// pointed by start and finish pointers  
// respectively.  
int kadane(int* arr, int* start,
    int* finish, int n)
{
    // initialize sum, maxSum and  
    int sum = 0, maxSum = INT_MIN, i;

    // Just some initial value to check 
    // for all negative values case  
    *finish = -1;

    // local variable  
    int local_start = 0;

    for (i = 0; i < n; ++i)
    {
        sum += arr[i];
        if (sum < 0)
        {
            sum = 0;
            local_start = i + 1;
        }
        else if (sum > maxSum)
        {
            maxSum = sum;
            *start = local_start;
            *finish = i;
        }
    }

    // There is at-least one  
    // non-negative number  
    if (*finish != -1)
        return maxSum;

    // Special Case: When all numbers 
    // in arr[] are negative  
    maxSum = arr[0];
    *start = *finish = 0;

    // Find the maximum element in array  
    for (i = 1; i < n; i++)
    {
        if (arr[i] > maxSum)
        {
            maxSum = arr[i];
            *start = *finish = i;
        }
    }
    return maxSum;
}

// The main function that finds 
// maximum sum rectangle in M[][]  
void findMaxSum(int **M, int N)
{
    // Variables to store the final output  
    int maxSum = INT_MIN, finalLeft, finalRight,
        finalTop, finalBottom;

    int left, right, i;
    int sum, start, finish;

    int* temp = new int [N];
    // Set the left column  
    for (left = 0; left < N; ++left)
    {
        // Initialize all elements of temp as 0  
        for (int qqq = 0; qqq < N; qqq++) {
            temp[qqq] = 0;
        }

        // Set the right column for the left 
        // column set by outer loop  
        for (right = left; right < N; ++right)
        {

            // Calculate sum between current left  
            // and right for every row 'i'  
            for (i = 0; i < N; ++i)
                temp[i] += M[i][right];

            // Find the maximum sum subarray in temp[].  
            // The kadane() function also sets values   
            // of start and finish. So 'sum' is sum of  
            // rectangle between (start, left) and  
            // (finish, right) which is the maximum sum  
            // with boundary columns strictly as left  
            // and right.  
            sum = kadane(temp, &start, &finish, N);

            // Compare sum with maximum sum so far.  
            // If sum is more, then update maxSum and  
            // other output values  
            if (sum > maxSum)
            {
                maxSum = sum;
                finalLeft = left;
                finalRight = right;
                finalTop = start;
                finalBottom = finish;
            }
        }
    }

    // Print final values  
    cout << "(Top, Left) (" << finalTop
        << ", " << finalLeft << ")" << endl;
    cout << "(Bottom, Right) (" << finalBottom
        << ", " << finalRight << ")" << endl;
    cout << "Max sum is: " << maxSum << endl;
}


// Driver Code 
int main()
{
    FILE* fp;		// HW1_config.txt file pointer
    FILE* fp_input; // input binary file
    FILE* fp_output;// ouptut binary file

    int main_loop_index, i; // for loop index var.
    int testcase;			// number of testcase

    int alg_num; // solution number
    fp_input = fopen("HW01_1_2D_10.in.bin", "rb");
    fread(&N, sizeof(int), 1, fp_input);


    int** arr = new int*[N];

    for (int i = 0; i < N; i++) {
       arr[i] = new int[N];
    }


    for (int i = 0; i < sqrt(N); i++) {
        for (int j = 0; j < sqrt(N); j++) {
            fread(&arr[i][j], sizeof(int), 1, fp_input);
            printf("%d ", arr[i][j]);

        }
        printf("\n");
    } // read binary file // read binary file

    fclose(fp_input);


    findMaxSum(arr, sqrt(N));

    return 0;
}
