#include "BigIntegerLibrary.hh"
#include "Factorizer.h"
#include <fstream>
#include <chrono>

using namespace std::chrono;

TrialDivision trial_division;
//other types

int main(int argc, char* argv[]) {
	// TODO use command line options for these parameters
	const char* file = "\\.\\..\\Generator\\Debug\\output.txt";
	Factorizer& factorizer = trial_division;

	std::ifstream in(file);
	
	std::string hex;
	while (in >> hex) {
		std::cout << hex << std::endl;
		BigUnsigned value = stringToBigUnsigned(hex);
	}
	BigUnsigned val = BigUnsigned(INT_MAX) * BigUnsigned(123);
	std::cout << "Factorizing " << val << "..." << std::endl;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	std::vector<BigUnsigned> factors = trial_division.factor(val);
	high_resolution_clock::time_point end = high_resolution_clock::now();
	duration<double> time = duration_cast<duration<double>>(end - start);
	std::cout << "Factors:";
	for (unsigned i = 0; i < factors.size(); i++) {
		std::cout << " " << factors[i];
	}
	std::cout << std::endl << time.count() << " seconds" << std::endl;
	system("pause");
}