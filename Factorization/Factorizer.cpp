#include "Factorizer.h"
#include <assert.h>

class PrimeCache {
	std::vector<BigUnsigned> primes;
public:
	PrimeCache() : primes() {
		primes.push_back(2);
		primes.push_back(3);
	}

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

std::vector<BigUnsigned> TrialDivision::factor(const BigUnsigned& value) const {
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

std::vector<BigUnsigned> Pollard::factor(const BigUnsigned& value) const {
	std::vector<BigUnsigned> result;
	BigUnsigned copy = value;

	BigUnsigned x = 2;
	BigUnsigned y = 2;
	BigUnsigned d = 1;

	while (d == 1) {
		x = ((x*x) + 1) % copy;
		y = ((((y*y) + 1) * ((y*y) + 1)) + 1) % copy;
		BigUnsigned abs = (x > y) ? x - y : y - x;
		d = gcd(abs, copy);
	}

	if (d != copy) {
		result.push_back(d);
		result.push_back(copy);
	}

	return result;
}