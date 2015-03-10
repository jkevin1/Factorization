#include "BigIntegerLibrary.hh"
#include "Factorizer.h"
#include "Generator.h"
#include "Timer.h"
#include <stdio.h>
#include <fstream>
#include <atomic>

#define ITERATIONS 32
#define BYTES 6

//These are instances of the different factorizors
TrialDivision trial_division;
Pollard pollard_algo;

int main(int argc, char* argv[]) {
	std::ofstream out("data.txt", std::ostream::out | std::ostream::app);
	// TODO use command line options for these parameters
	Factorizer& factorizer = pollard_algo;
	Timer timer;

	std::cout << ITERATIONS << " iterations of " << BYTES << " byte factorization" << std::endl;
	for (int i = 0; i < ITERATIONS; i++) {
		BigUnsigned value = 0;
		while (value < 2) value = generate(BYTES);
		factorizer.factor(value);
	}

	out << BYTES << ": " << (timer.getTime()/ITERATIONS) << std::endl;
	system("pause");
}