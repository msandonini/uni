#include <cinttypes>
#include <fstream>
#include <iostream>
#include <print>
#include <string>

int read_string(std::ifstream& is, int nindent = 0);
int read_int(std::ifstream& is, int nindent = 0);
int read_list(std::ifstream& is, int nindent = 0);
int read_dict(std::ifstream& is, int nindent = 0);

int main(int argc, char const* argv[]) {
	if (argc != 2) {
		std::println(std::cerr, "Error: invalid number of arguments");
		return 1;
	}

	std::ifstream is(argv[1]);
	if (!is) {
		std::println(std::cerr, "Error: unable to open input stream");
		return 1;
	}

	int retcode = read_dict(is);

	is.close();

	return retcode;
}

int read_string(std::ifstream& is, int nindent) {
	char peeked = is.peek();
	if (peeked < '0' || peeked > '9') {
		std::println(std::cerr,
					 "\nError: file is malformed (read_string on non string)");
		return 1;
	}

	std::string nchstr = "";
	char c;
	while (c = is.peek()) {
		if (c == ':') {
			if (nchstr.empty()) {
				std::println(std::cerr, "\nError: file is malformed (empty strlen)");
				return 1;
			}

			is.get();  // Discard ':'

			std::cout << '\n';	// Format
			for (size_t i = 0; i < nindent; i++) {
				std::cout << '\t';
			}

			int nch = std::stoll(nchstr);
			char read[nch + 1];
			is.read(read, nch);

			if (std::string(read).empty()) {
				std::println(std::cerr, "\nError: reading error (str)");
				return 1;
			}

			std::cout << read;

			return 0;
		}
		if (c < '0' || c > '9') {
			std::println(std::cerr,
						 "\nError: file is malformed (string contains bad value)");
			return 1;
		}

		nchstr.push_back(is.get());
	}

	std::println(std::cerr, "\nError: peek failed [in string]");
	return 1;
}

int read_int(std::ifstream& is, int nindent) {
	if (is.get() != 'i') {
		std::println(std::cerr,
					 "\nError: file is malformed (read_int on non integer)");
		return 1;
	}

	std::string val = "";
	char c;
	while (c = is.peek()) {
		if (c == 'e') {
			if (val.empty()) {
				std::println(std::cerr,
							 "\nError: file is malformed (empty integer)");
				return 1;
			}

			std::cout << '\n';	// Format
			for (size_t i = 0; i < nindent; i++) {
				std::cout << '\t';
			}

			std::cout << std::stoll(val);
			return 0;
		}
		if (c < '0' || c > '9') {
			std::println(std::cerr,
						 "\nError: file is malformed (integer contains bad value)");
			return 1;
		}

		val.push_back(is.get());
	}

	std::println(std::cerr, "\nError: peek failed [in int]");
	return 1;
}

int read_list(std::ifstream& is, int nindent) {
	if (is.get() != 'l') {
		std::println(std::cerr,
					 "\nError: file is malformed (read_list on non list)");
		return 1;
	}

	std::cout << '\n';	// Format
	for (size_t i = 0; i < nindent; i++) {
		std::cout << '\t';
	}
	std::cout << '[';

	char c;
	while (c = is.peek()) {
		switch (c) {
			case 'e':
				std::cout << "\n]";
				return 0;
			case 'i': {
				if (read_int(is)) {
					return 1;
				}
				break;
			}
			case 'l': {
				if (read_list(is)) {
					return 1;
				}
				break;
			}
			case 'd': {
				if (read_dict(is)) {
					return 1;
				}
				break;
			}
			default: {
				if (c < '0' || c > '9') {
					std::println(
						std::cerr,
						"\nError: file is malformed (unknown type [in list])");
					return 1;
				}
				if (read_string(is)) {
					return 1;
				}
			}
		}
	}

	std::println(std::cerr, "\nError: peek failed [in list]");
	return 1;
}

int read_dict(std::ifstream& is, int nindent) {
	if (is.get() != 'd') {
		std::println(std::cerr,
					 "\nError: file is malformed (read_dict on non dict)");
		return 1;
	}

	std::cout << '\n';
	for (size_t i = 0; i < nindent; i++) {
		std::cout << '\t';
	}
	std::cout << "{";

	char c;
	while (c = is.peek()) {
		if (c == 'e') {
			return 0;
		}

		switch (c) {
			case 'e': {
				std::cout << "\n}";
				return 0;
			}
			case 'i': {
				if (read_int(is)) {
					return 1;
				}
				break;
			}
			case 'l': {
				if (read_list(is)) {
					return 1;
				}
				break;
			}
			case 'd': {
				if (read_dict(is)) {
					return 1;
				}
				break;
			}
			default: {
				if (c < '0' || c > '9') {
					std::println(
						std::cerr,
						"\nError: file is malformed (unknown type [in list])");
					return 1;
				}
				if (read_string(is)) {
					return 1;
				}
			}
		}
	}

	std::println("\nError: peek failed [in dict]");
	return 1;
}
