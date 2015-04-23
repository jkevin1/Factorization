#include "Factorizer.h"
#include <assert.h>

// TODO: parameter for max size to avoid memory issues
class PrimeCache {
	std::vector<BigUnsigned> primes;
public:
	// ITS A LOT OF MEMORY
	PrimeCache() : primes() {
		primes.push_back(2);
		primes.push_back(3);
	}

/*	// This function will guarentee that all primes under sqrt(maxSquared) are loaded
	// Returns false if cache is full
	bool loadPrimes(BigUnsigned maxSquared) {
		BigUnsigned max = primes.back();
		while (max*max < maxSquared) {
			max += 2;
			bool prime = true;
			for (unsigned i = 0; i < primes.size(); i++) {
				if (primes[i] == 0) fprintf(stderr, "Zero!!!!! index=%d", i);
				if (max % primes[i] == 0) {
					prime = false;
					break;
				}
			}
			if (prime) {
				try {
					primes.push_back(max);
				} catch (...) {
					fprintf(stderr, "Couldn't allocate memory for prime cache\n");
					return false;
				}
			}
		}
		printf("Prime Cache is storing %d primes\n", primes.size());
		return true;
	}	*/

	const BigUnsigned& operator[](unsigned index) {
		while (index >= primes.size()) {
			BigUnsigned v = primes.back();
			while (true) {
				v += 2;
				bool prime = true;
				for (int i = 0; ; i++) {
					if (primes[i] * primes[i] > v) break;
					if (v % primes[i] == 0) {
						prime = false;
						break;
					}
				}
				if (prime) {
					primes.push_back(v);
					break;
				}
			}
		}
		return primes[index];
	}

	unsigned size() {
		return primes.size();
	}
};

std::vector<BigUnsigned> TrialDivision::factor(const BigUnsigned& value) {
	static PrimeCache primes;
	std::vector<BigUnsigned> result;
	BigUnsigned copy = value;
	for (unsigned i = 0; ; i++) {
		if (primes[i] * primes[i] > copy) break;
		while (copy % primes[i] == 0) {
			copy /= primes[i];
			result.push_back(primes[i]);
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