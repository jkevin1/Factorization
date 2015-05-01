#include "BigIntegerLibrary.hh"
#include "Factorizer.h"
#include "Generator.h"
#include "Timer.h"
#include <stdio.h>
#include <fstream>
#include <thread>

#define ITERATIONS 500
#define MAX_BYTES 7

TrialDivision trial_division;
Pollard pollard_rho;

// The input data set
std::vector<BigUnsigned> numbers[MAX_BYTES];

void runTest(const Factorizer& factorizer) {
	std::ofstream out(factorizer.name + ".txt", std::ostream::out);
	Timer timer;

	out << "Running " << factorizer.name << " tests:";
	for (int bytes = 1; bytes <= MAX_BYTES; bytes++) {
		printf("Running %s %d byte tests...\n", factorizer.name.c_str(), bytes);
		out << std::endl << bytes << " bytes:";
		double total = 0.0;
		for (int i = 0; i < ITERATIONS; i++) {
			timer.start();
			std::vector<BigUnsigned> factors = factorizer.factor(numbers[bytes-1][i]);
			out << " " << timer.getTime();
			total += timer.getTime();
		}
		out << std::endl << "Average: " << (total / ITERATIONS) << "sec";
	}

	out.close();
	printf("%s tests complete.\n", factorizer.name.c_str());
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < MAX_BYTES; i++) {
		numbers[i] = std::vector<BigUnsigned>();
		for (int j = 0; j < ITERATIONS; j++) {
			BigUnsigned value = 0;
			while (value < 2) value = generate(i + 1);
			numbers[i].push_back(value);
		}
	}

	std::thread td = std::thread([]{ runTest(trial_division); });
	std::thread pr = std::thread([]{ runTest(pollard_rho); });
	td.join();
	pr.join();
}
// 