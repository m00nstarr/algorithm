#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>

#define _CRT_SECURE_NO_WARNINGS
#define Is_2D false
#define N_Sequence 10
#define Final_n Is_2D?N_Sequence*N_Sequence:N_Sequence
#define Max_Sequence_Elements N_Sequence*10
#define Positive_Probability 0.55

void main(void) {
	int target;
	float prob;
	char c_string[256];
	sprintf(c_string,"HW01_%s_%d.in.bin", Is_2D?"2D":"1D", N_Sequence);
	std::ofstream File(std::string(c_string).data(), std::ios::out | std::ios::binary);

	srand((unsigned)time(NULL));
	if (File.is_open()) {
		target = Final_n;
		File.write((char*)(&target), sizeof(int));
		for (int i = 0; i < (Final_n); i++) {
			target = rand() % (Max_Sequence_Elements);
			
			prob = (float)rand() / RAND_MAX;
			if (prob > Positive_Probability)
				target *= -1;
			File.write((char*)(&target), sizeof(int));
			
		}
		
		File.close();
	}

	std::ifstream inFile(std::string(c_string).data(), std::ios::in | std::ios::binary);
	if (inFile.is_open()) {
		std::string str;
		int n;
		inFile.read((char*)(&n), sizeof(int));
		std::cout << "Generated Data Count: " << n << std::endl;
		/*
		for (int i = 0; i < n; i++) {
			inFile.read((char*)(&target), sizeof(int));
			std::cout << target << " ";
		}*/
		std::cout <<std::endl;
		inFile.close();
	}
	
}


