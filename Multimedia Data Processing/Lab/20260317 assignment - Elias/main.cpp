#include <cmath>
#include <fstream>
#include <ostream>
#include <print>
#include <string>
#include <vector>

template <typename T>
std::ostream& raw_write(std::ostream& os, const T& x, size_t size = sizeof(T)) {
	return os.write(reinterpret_cast<const char*>(&x), size);
}

template <typename T>
std::ostream& raw_write(std::ostream& os, const std::vector<T>& x) {
	return os.write(reinterpret_cast<const char*>(x.data()),
					x.size() * sizeof(T));
}

class bitwriter {
	uint8_t buffer_;
	size_t n_;
	std::ostream& os_;

	void writebit(uint8_t curbit) {
		buffer_ = (buffer_ << 1) | curbit;
		++n_;
		if (n_ == 8) {
			os_.put(buffer_);
			n_ = 0;
		}
	}

  public:
	bitwriter(std::ostream& os) : buffer_(0), n_(0), os_(os) {}
	~bitwriter() { flush(); }
	void operator()(uint32_t x, int n) {
		for (int i = n - 1; i >= 0; --i) {
			uint8_t curbit = (x >> i) & 1;
			writebit(curbit);
		}
	}
	void flush(uint8_t bit = 0) {
		while (n_ > 0) {
			writebit(bit);
		}
	}
};

void print_usage() {
	std::println("Usage: ");
	std::println("elias [c|d] <filein> <fileout>");
}

uint32_t map_signed(int32_t n) { return (n < 0) ? -2 * n : 2 * n + 1; }
int32_t map_positive(uint32_t n) {
	return (n % 2) ? (n - 1) / 2 : -(int32_t)(n / 2);
}

int compress(const std::string& filein, const std::string& fileout) {
	std::ifstream is(filein /*, std::ios::binary*/);
	std::ofstream os(fileout, std::ios::binary);

	if (!is) {
		std::println("Error: unable to open file \"{}\"", filein);
		return 1;
	}
	if (!os) {
		std::println("Error: unable to open file \"{}\"", fileout);
		return 1;
	}

	uint32_t zeros = 0;
	int nbits = 0;

	bitwriter bw(os);

	int32_t val;
	while (is >> val) {
		std::println("Read value: {}", val);

		uint32_t n = map_signed(val);

		int l = floor(log2(n));
		bw(zeros, l);
		bw(n, l + 1);
	}

	return 0;
}

int decompress(const std::string& filein, const std::string& fileout) {
	std::ifstream is(filein, std::ios::binary);
	std::ofstream os(fileout /*, std::ios::binary*/);

	if (!is) {
		std::println("Error: unable to open file \"{}\"", filein);
		return 1;
	}
	if (!os) {
		std::println("Error: unable to open file \"{}\"", fileout);
		return 1;
	}

	int nbits = 0;
	bool counting = true;

	uint32_t buffer = 0;

	while (true) {
		int c = is.get();
		if (is.eof()) {
			break;
		}

		uint8_t b = static_cast<uint8_t>(c);

		for (int i = 7; i >= 0; --i) {
			bool bit = (b >> i) & 1;
			// std::print("{}", bit ? "1" : "0");

			if (counting) {
				if (!bit) {
					nbits++;
				} else {
					buffer = 1;
					counting = false;
					std::println("Counted {} zeros", nbits);

					if (!nbits) {
						int32_t val = map_positive(buffer);
						std::println(os, "{}", val);
						counting = true;
					}
				}
			} else {
				buffer = (buffer << 1) | bit;
				nbits--;

				if (!nbits) {
					int32_t val = map_positive(buffer);
					std::println(os, "{}", val);
					counting = true;
				}
			}
		}
		// std::println();
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
