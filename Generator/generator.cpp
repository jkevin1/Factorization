#include "BigIntegerLibrary.hh"
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

//How many 32-bit integers compose each big integer
#define NUM_INTS 4

int main(int argc, char* argv[]) {
	// TODO use command line arguments to override these parameters
	int num = 100;
	int seed = time(nullptr);
	char* file = "output.txt";

	std::ofstream out(file, std::ostream::out);
	srand(seed);

	//"x * shl32" is equivalent to "x << 32" which isn't supported by this library
	const BigInteger shl32 = BigInteger(2147483648u) + BigInteger(2147483648u);
	BigInteger value;
	for (int i = 0; i < num; i++) {
		value = 0;
		for (int j = 0; j < NUM_INTS; j++) {
			int next = rand();
			//make sure all 32 bytes are used, no negatives
			value = (value * shl32) + *(unsigned*)&next;
			//Omit even numbers
			if (value % 2 == 0) value += 1;
		}
		//possibly output in binary instead of as text
		out << value << std::endl;
		//showing output for debug purposes
		std::cout << value << std::endl;
	}

	out.close();
	//showing output for debug purposes
	system("pause");

	return 0;
}