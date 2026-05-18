#include <cmath>
#include <cstdint>
#include <fstream>
#include <numbers>
#include <vector>

int main(void) {
	int sps = 44100;  // Sampling rate [samples/s]
	std::vector<uint16_t> samples;
	int duration = 2;	// [s]
	int A = INT16_MAX;	// Amp
	double f = 440;		// [Hz] -> 440 Hz corresponds to the A chord

	for (size_t i = 0; i < sps * duration; i++) {
		double t = static_cast<double>(i) / sps;
		double val = A * sin(2 * std::numbers::pi * f * t);

		int16_t sample = static_cast<int16_t>(lround(val));

		samples.push_back(sample);
	}

	std::ofstream os("output.raw", std::ios::binary);
	if (!os) {
		return 1;
	}

	os.write(reinterpret_cast<char*>(samples.data()),
			 samples.size() * sizeof(int16_t));

	return 0;
}
