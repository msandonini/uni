#include <cstdint>
#include <fstream>
#include <iostream>
#include <print>
#include <vector>

int main(int argc, char const* argv[]) {
	if (argc != 3) {
		std::println("Error: wrong number of parameters");
		return 1;
	}

	std::ifstream is(argv[1], std::ios::binary);

	if (!is) {
		std::println("Error: unable to open input file");
		is.close();
		return 1;
	}

	is.close();
	return 0;
}
