#include "Factorizer.h"

//Needs prime sieve to optimize
std::vector<BigUnsigned> TrialDivision::factor(const BigUnsigned& value) {
	std::cout << "Trial Division factorizing " << value << std::endl;

	std::vector<BigUnsigned> result;
	//TODO improve this to only use primes, still same time complexity but faster coefficients, more memory though

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

std::vector<BigUnsigned> Pollard::factor(const BigUnsigned& value) {
	std::cout << "Pollard factorizing " << value << std::endl;

	std::vector<BigUnsigned> result;
	BigUnsigned copy = value;

	BigUnsigned x = 2;
	BigUnsigned y = 2;
	BigUnsigned d = 1;

	while (d == 1) {
		x = ((x*x) + 1) % copy;
		//y = ( ( (((y*y) + 1) % copyValue) * (((y*y) + 1) % copyValue) ) + 1) % copyValue;
		//TODO make a g(x) function that is variable, maybe use lambda functions
		y = ((((y*y) + 1) * ((y*y) + 1)) + 1) % copy;
		BigUnsigned abs = (x > y) ? x - y : y - x;
		d = gcd(abs, copy);
	}

	if (d == copy) {
		//std::cout << "failed or prime";
	} else {
		//std::cout << "~~~~D~~~~: " << d << std::endl;
		result.push_back(d);
		//copy /= d;
		result.push_back(copy);
	}

	return result;
}