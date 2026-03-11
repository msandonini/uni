#include <array>
#include <fstream>
#include <map>
#include <ostream>
#include <print>

int main(int argc, char const* argv[]) {
	if (argc != 3) {
		std::println("3 arguments needed. Usage:");
		std::println("\tfrequencies <input_file> <output_file>");
		return 1;
	}

	std::ifstream is(argv[1], std::ios::binary);

	if (!is) {
		std::println("Error: unable to open file \"%s\"", argv[1]);
		return 1;
	}

	std::map<unsigned char, unsigned int> m;

	/*
	unsigned char d;
	while (is >> std::noskipws >> d) {
		if (m.contains(d)) {
			m[d]++;
		} else {
			m[d] = 1;
		}
	}
	*/

	/*
	char d;
	while (is.get(d)) {
		unsigned char c = d;

		if (m.contains(c)) {
			m[c]++;
		} else {
			m[c] = 1;
		}
	}
	*/

	is.close();

	std::ofstream os(argv[2]);

	if (!os) {
		std::println("Error: Output stream not open");
		return 1;
	}

	for (const auto& pair : m) {
		unsigned char k = pair.first;
		unsigned int v = pair.second;
		std::println(os, "{:02x}\t{}", k, v);
	}

	return 0;
}
