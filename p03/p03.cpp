/*
Author:			Colton Cox
Student ID:		20511024
Course:			CMSC 2123 - Discrete Structures
CRN:			10748, Fall, 2022
Project:		p03
Due:			October 12, 2022
Account:		tt001
*/

#include <fstream>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <cstring>


int ef0(int n)
{
	
	int counter = 0;
	
	int sum = 1;		counter++;
	int a = 0;			counter++;

	
	while (a < n){		counter++;

		sum = sum * 2;	counter+=2;
		a++;			counter++;
	}					counter++;

	while (sum > 0){	counter++;
		
	sum--;				counter++;
	}					counter++;

	return counter;
}

int af0(int n) { return 2 * (pow(2, n)) + 4*n + 4; }


int main(int argc, char* argv[])
{
	char inputFileName[255];
	char outputFileName[255];

	switch (argc) 
	{
	case 1:
		std::cout << "Enter the input file name: ";
		std::cin >> inputFileName;
		std::cout << "Enter the output file name: ";
		std::cin >> outputFileName;
		break;

	case 2:
		strcpy(inputFileName, argv[1]);
		std::cout << "Enter the output file name: ";
		std::cin >> outputFileName;
		break;
	
	case 3:
		strcpy(inputFileName, argv[1]);
		strcpy(outputFileName, argv[2]);
		break;
	}
		

	std::ifstream inputFile = std::ifstream(inputFileName);
	std::ofstream outputFile = std::ofstream(outputFileName);
	std::string result = "";

	outputFile << "Code Fragment 3\nN" << std::setw(13) << "Analytical" << std::setw(14) << "Empirical\n";

	while (inputFile)
	{
		char w;

		while (inputFile >> w)
		{
			outputFile << w << std::setw(13) << ef0(w - '0') << std::setw(13) << af0(w - '0') << "\n";
		}
	}


	return 0;
}