#include "Factorizer.h"

//Needs prime sieve to optimize
std::vector<BigUnsigned> TrialDivision::factor(const BigUnsigned& value) {
	std::vector<BigUnsigned> result;
	//TODO improve this to only use primes, still same time complexity but faster coefficients
	BigUnsigned copy = value;
	while (copy % 2 == 0) {
		copy /= 2;
		result.push_back(2);
	}
	for (BigUnsigned i = 3; i*i <= value; i += 2) {
		while (copy % i == 0) {
			copy /= i;
			result.push_back(i);
		}
	}
	if (copy > 1) result.push_back(copy);
	return result;
}
