#include <print>

#include "rgb.hpp"

int main(int argc, char const* argv[]) {
	if (argc != 3) {
		return 1;
	}

	try {
		rgbImage img();
	} catch (std::runtime_error err) {
		std::println("Error: {}", err.what());
	}

	return 0;
}
