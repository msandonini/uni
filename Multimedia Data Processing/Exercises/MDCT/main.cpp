#include <cinttypes>
#include <cmath>
#include <fstream>
#include <numbers>
#include <print>
#include <ranges>
#include <unordered_map>
#include <vector>

double measure_entropy(const std::vector<int16_t>& data) {
	std::unordered_map<int16_t, size_t> freq;

	for (const auto& s : data) {
		freq[s]++;
	}

	double entropy = 0.0;
	double n = static_cast<double>(data.size());

	for (const auto& [sym, count] : freq) {
		double p = static_cast<double>(count) / n;
		entropy -= p * std::log2(p);
	}

	return entropy;
}

int main(int argc, char const* argv[]) {
	std::vector<int16_t> data;

	std::ifstream is("test.raw", std::ios::binary);
	if (!is) {
		std::println("Unable to open the input file");
		return 1;
	}

	int16_t sample;
	while (is.read(reinterpret_cast<char*>(&sample), sizeof(sample))) {
		data.push_back(sample);
	}

	double entropy = measure_entropy(data);
	std::println("Read entropy value: {:.5f}", entropy);

	int Q = 2600;

	auto quantized = data | std::views::transform([Q](int16_t s) {
						 return static_cast<int32_t>(lround(double(s)) / Q);
					 })
					 | std::ranges::to<std::vector<int32_t>>();

	return 0;
}
