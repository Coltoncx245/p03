#include <fstream>
#include <iostream>
#include <math.h>


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

std::string parseFile(std::string fileName)
{
	std::ifstream inputFile = std::ifstream(fileName);
	std::string result = "";

	while (inputFile)
	{
		char w;

		while (inputFile >> w)
		{
			std::cout << ef0(w - '0') << "\t" << af0(w-'0') << "\n";
		}
	}

	return result;
}

int main()
{

	parseFile("i03.dat");
	// std::cout << ef0(5);
	return 0;
}