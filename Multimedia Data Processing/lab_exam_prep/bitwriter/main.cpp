#include <fstream>

class bitwriter {
	std::ostream& os_;

	uint8_t buffer_;
	size_t buflen_;

  public:
	bitwriter(std::ostream& os) : buffer_(0), buflen_(0), os_(os) {}
	~bitwriter() { flush(); }

	void write(uint8_t c, int nbits) {
		for (int i = 0; i < nbits; i++) {
			uint8_t bit = (c >> (nbits - 1 - i)) & 1;
			buffer_ = (buffer_ << 1) | bit;
			buflen_++;

			if (buflen_ == 8) {
				os_.put(buffer_);
				buffer_ = 0;
				buflen_ = 0;
			}
		}
	}

	void operator()(uint8_t c) { write(c, 8); }
	void operator()(uint8_t c, int n) { write(c, n); }

	void flush() {
		if (buflen_ != 0) {
			buffer_ = buffer_ << (8 - buflen_);
			os_.put(buffer_);
			buffer_ = 0;
			buflen_ = 0;
		}
	}
};

int main(int argc, char const* argv[]) {
	std::ofstream os("test.sand", std::ios::binary);
	bitwriter out(os);

	out('a');
	out(3, 2);
	out(0, 2);
	out(15, 2);
	out(5);
	out(2, 2);

	return 0;
}
