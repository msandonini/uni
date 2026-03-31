#include <fstream>
#include <print>
#include <string>

void print_usage() {
	std::println("Usage: ");
	std::println("huffman1 [c|d] <filein> <fileout>");
}

int compress(std::string filein, std::string fileout) {
	std::ifstream is(filein, std::ios::binary);

	if (!is) {
		std::println("Error: unable to open file \"{}\"", filein);
		return 1;
	}

	return 0;
}

int decompress(std::string filein, std::string fileout) {
	std::ifstream is(filein, std::ios::binary);

	if (!is) {
		std::println("Error: unable to open file \"{}\"", filein);
		return 1;
	}

	return 0;
}

int main(int argc, char const* argv[]) {
	if (argc != 4) {
		std::println("Error: wrong number of arguments.");
		print_usage();
		return 1;
	}

	std::string mode = argv[1];

	if (mode == "c") {
		return compress(argv[2], argv[3]);
	} else if (mode == "d") {
		return decompress(argv[2], argv[3]);
	} else {
		std::println("Error: provided invalid mode.");
		print_usage();
		return 1;
	}

	return 0;
}
