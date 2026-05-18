#include <cinttypes>
#include <cmath>
#include <fstream>
#include <print>
#include <vector>

int measure_entropy(const std::vector<double>& data, int& entropy) {
	return 0;
}

int quantize(const std::vector<double>& data,
			 std::vector<int32_t>& quantized,
			 const int& q) {}

int dequantize(const std::vector<int32_t>& data, std::ostream& out) {}

int main(int argc, char const* argv[]) {
	std::vector<double> data;

	std::ifstream is("test.raw", std::ios::binary);
	if (!is) {
		std::println("Unable to open the input file");
		return 1;
	}

	int16_t sample;
	while (is >> sample) {
		data.push_back(static_cast<double>(sample));
	}

	int entropy = 0;
	measure_entropy(data, entropy);
	std::println("Read entropy value: {}", entropy);

	return 0;
}
