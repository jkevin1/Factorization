#include "Generator.h"
#include <random>
#include <time.h>

//"x * shl8" is equivalent to "x << 8" which isn't supported by this library
const static BigUnsigned shl8 = 1u << 8;

BigUnsigned generate(int bytes) {
	static bool first = true;
	if (first) {
		srand(time(nullptr));
		first = false;
	}

	BigUnsigned value = 0;
	for (int j = 0; j < bytes; j++) {
		//Shift left 1 byte and add another random byte
		value = (value * shl8) + (rand() % 256);
	}
	return value;
}