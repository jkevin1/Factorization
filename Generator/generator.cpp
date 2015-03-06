#include "BigIntegerLibrary.hh"
#include <fstream>
#include <random>
#include <time.h>

//How many 32-bit integers compose each big integer (x8 to get num bits)
#define NUM_BYTES 16

//"x * shl8" is equivalent to "x << 8" which isn't supported by this library
const BigUnsigned shl8 = 1u << 8;

int main(int argc, char* argv[]) {
	// TODO use command line arguments to override these parameters
	int num = 100;
	int seed = time(nullptr);
	char* file = "output.txt";

	srand(seed);
	std::ofstream out(file, std::ostream::out);

	for (int i = 0; i < num; i++) {
		BigUnsigned value = 0;
		for (int j = 0; j < NUM_BYTES; j++) {
			//Shift left 1 byte and add another random byte
			value = (value * shl8) + (rand() % 256);
		}
		//possibly omit even numbers
//		if (value % 2 == 0) value += 1;
		//possibly output in binary instead of as text
		out << std::string(BigUnsignedInABase(value, 16)) << std::endl;
	}

	out.close();
}