
#include <ctype.h>
#include <fstream>
#include <iostream>

void write_bits(std::ofstream& os, const uint32_t code, const int nbits) {}

struct table_entries {
	uint8_t sym;
	uint8_t len;
	uint32_t code;
};

int compress(const std::string& input, const std::string& output) {
	return 0;
}

int decompress(const std::string& input, const std::string& output) {
	return 0;
}

int main(int argc, char const* argv[]) {
	if (argc != 4) {
		std::cout << "Error! Invalid number of arguments.\n";
		return 1;
	}

	if (argv[1][0] == 'c') {
		return compress(argv[2], argv[3]);
	} else if (argv[1][0] == 'd') {
		return decompress(argv[2], argv[3]);
	}

	std::cout << "Error! Invalid argument.";

	return 1;
}
