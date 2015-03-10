#pragma once

#include "BigIntegerLibrary.hh"
#include <vector>

class Factorizer {
public:
	virtual ~Factorizer() { }

	virtual std::vector<BigUnsigned> factor(const BigUnsigned& value) = 0;
};

class TrialDivision : public Factorizer {
public:
	std::vector<BigUnsigned> factor(const BigUnsigned& value);
};

class Pollard : public Factorizer {
public:
	std::vector<BigUnsigned> factor(const BigUnsigned& value);
};