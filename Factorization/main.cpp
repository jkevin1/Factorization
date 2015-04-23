#include "BigIntegerLibrary.hh"
#include "Factorizer.h"
#include "Generator.h"
#include "Timer.h"
#include <stdio.h>
#include <fstream>
#include <atomic>

#define ITERATIONS 100
#define BYTES 6

//These are instances of the different factorizors
TrialDivision trial_division;
Pollard pollard_algo;

int main(int argc, char* argv[]) {
	std::ofstream out("time.txt", std::ostream::out | std::ostream::app);
	
	Factorizer& factorizer = trial_division;
	Timer timer;

	std::cout << ITERATIONS << " iterations of " << BYTES << " byte factorization" << std::endl;
	for (int i = 0; i < ITERATIONS; i++) {
		BigUnsigned value = 0;
		while (value < 2) value = generate(BYTES);
		std::cout << value << ": ";
		std::vector<BigUnsigned> factors = factorizer.factor(value);
		for (unsigned i = 0; i < factors.size(); i++)
			std::cout << factors[i] << " ";
		std::cout << std::endl;
	}

	out << BYTES << ": " << (timer.getTime()/ITERATIONS) << std::endl;
	system("pause");
}
// The number 19930864167544139 requires loading 540121 prime numbers to get 8005397, which is greater than the square root of the largest prime factor, 64086379959949
// The number 39802463889226546 requires loading 1585662 prime numbers to get 25337231, which is greater than the square root of the largest prime factor, 641975224019783