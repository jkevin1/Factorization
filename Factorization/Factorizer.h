#pragma once

#include "BigIntegerLibrary.hh"
#include <vector>
#include <string>

class Factorizer {
public:
	const std::string name;
	Factorizer(const char* name) : name(name) { }
	virtual ~Factorizer() { }

	virtual std::vector<BigUnsigned> factor(const BigUnsigned& value) const = 0;
};

class TrialDivision : public Factorizer {
public:
	TrialDivision() : Factorizer("Trial Division") { }
	std::vector<BigUnsigned> factor(const BigUnsigned& value) const;
};

class Pollard : public Factorizer {
public:
	Pollard() : Factorizer("Pollard's Rho") { }
	std::vector<BigUnsigned> factor(const BigUnsigned& value) const;
};