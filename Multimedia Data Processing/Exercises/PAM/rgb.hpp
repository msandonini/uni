#include <fstream>
#include <sstream>

#include "matrix.hpp"

struct rgbImage : public matrix<std::array<uint8_t, 3>> {
	rgbImage() : matrix() {}
	rgbImage(size_t rows, size_t cols) : matrix(rows * 3, cols * 3) {}

	void loadPAM(const std::string& filename) override {
		std::ifstream is(filename, std::ios::binary);
		if (!is) {
			throw std::runtime_error("Unable to open input stream");
		}
		std::string token;
		is >> token;
		if (token != "P7") {
			throw std::runtime_error("File has bad header");
		}
		std::string line;
		int w = -1, h = -1, depth = -1, maxval = -1;
		std::string type;
		while (std::getline(is, line)) {
			if (line[0] == '#') {
				continue;
			}
			std::stringstream ss(line);
			ss >> token;
			if (token == "ENDHDR") {
				break;
			}
			if (token == "WIDTH") {
				ss >> w;
			} else if (token == "HEIGHT") {
				ss >> h;
			} else if (token == "DEPTH") {
				ss >> depth;
			} else if (token == "MAXVAL") {
				ss >> maxval;
			} else if (token == "TUPLTYPE") {
				ss >> type;
			}
		}
		if (w < 0 || h < 0 || depth != 3 || maxval != 255 || type != "RGB") {
			throw std::runtime_error("File has bad header");
		}

		rows_ = h;
		cols_ = w;

		if (!is.read(rawdata(), rawsize())) {
			rows_ = 0;
			cols_ = 0;
			throw std::runtime_error("Unable to read raw image data");
		}
	}

	void savePAM(const std::string& filename) override {
		std::ofstream os(filename, std::ios::binary);
		if (!os) {
			throw std::runtime_error("Unable to open output stream");
		}
		os << "P7\n"
		   << "WIDTH " << cols() << "\n"
		   << "HEIGHT " << rows() << "\n"
		   << "DEPTH 3\n"
		   << "MAXVAL 255\n"
		   << "TUPLTYPE RGB\n"
		   << "ENDHDR\n";

		os.write(rawdata(), rawsize());
	}

	void flip() override {
		for (int r = 0; r < rows() / 2; ++r) {
			for (int c = 0; c < cols(); ++c) {
				std::swap(at(r, c), at(rows() - 1 - r, c));
			}
		}
	}
	void mirror() override {
		for (int r = 0; r < rows(); ++r) {
			for (int c = 0; c < cols() / 2; ++c) {
				std::swap(at(r, c), at(r, cols() - 1 - c));
			}
		}
	}
};