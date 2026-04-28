#include <fstream>
#include <sstream>

#include "matrix.hpp"

class grayscaleImage : public matrix<uint8_t> {
  public:
	grayscaleImage() : matrix() {}
	grayscaleImage(size_t rows, size_t cols) : matrix(rows, cols) {}

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
				ss >> maxval;
			} else if (token == "TUPLTYPE") {
				ss >> type;
			}

			if (w < 0 || h < 0 || maxval != 255 || type != "GRAYSCALE" ||
				depth != 1) {
				throw std::runtime_error("File has bad header");
			}

			rows_ = h;
			cols_ = w;

			if (!is.read(rawdata(), size())) {
				rows_ = 0;
				cols_ = 0;
				throw std::runtime_error("Unable to read raw image data");
			}
		}
	}

	void savePAM(const std::string& filename) override {
		std::ofstream os(filename, std::ios::binary);

		if (!os) {
			throw std::runtime_error("Unable to open output stream");
		}

		os << "P7\n"
		   << "WIDTH" << cols() << "\n"
		   << "HEIGHT" << rows() << "\n"
		   << "DEPTH 1\n"
		   << "MAXVAL 255\n"
		   << "TUPLTYPE GRAYSCALE\n"
		   << "ENDHDR\n";
		os.write(rawdata(), size());
	}

	void flip() override {
		for (size_t i = 0; i < rows(); i++) {
			for (size_t j = 0; j < cols(); j++) {
				std::swap(at(i, j), at(rows() - i - 1, j));
			}
		}
	}
	void mirror() override {
		for (size_t i = 0; i < rows(); i++) {
			for (size_t j = 0; j < cols(); j++) {
				std::swap(at(i, j), at(i, cols() - j - 1));
			}
		}
	}
};