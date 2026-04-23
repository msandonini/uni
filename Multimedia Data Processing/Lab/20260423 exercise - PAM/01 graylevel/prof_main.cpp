#include <cassert>
#include <cstdint>
#include <fstream>
#include <vector>

struct matrix {
	int rows_, cols_;
	std::vector<uint8_t> data_;

	matrix() {}
	matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(rows * cols) {}

	const uint8_t& operator()(int r, int c) const {
		assert(0 <= r && r < rows_ && 0 <= c && c < cols_);
		return data_[r * cols_ + c];
	}
	uint8_t& operator()(int r, int c) {
		return const_cast<uint8_t&>(
			static_cast<const matrix*>(this)->operator()(r, c));
	}

	auto rows() const { return rows_; }
	auto cols() const { return cols_; }
	auto data() const { return data_; }
	auto size() const { return rows_ * cols_; }

	const char* rawdata() const {
		return reinterpret_cast<const char*>(data_.data());
	}
};

bool savePAM(const std::string& filename, const matrix& img) {
	std::ofstream os(filename, std::ios::binary);
	if (!os) {
		return false;
	}
	os << "P7\n"
	   << "WIDTH " << img.cols() << "\n"
	   << "HEIGHT " << img.rows() << "\n"
	   << "DEPTH 1\n"
	   << "MAXVAL 255\n"
	   << "TUPLTYPE GRAYSCALE\n"
	   << "ENDHDR\n";
	// for (int r = 0; r < img.rows(); ++r) {
	//	for (int c = 0; c < img.cols(); ++c) {
	//		os.put(img(r, c));
	//	}
	// }
	os.write(img.rawdata(), img.size());
	return true;
}

matrix makeVerticalGradient() {
	matrix img(256, 256);
	for (int r = 0; r < img.rows(); ++r) {
		for (int c = 0; c < img.cols(); ++c) {
			img(r, c) = static_cast<uint8_t>(r);
		}
	}
	return img;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		return 1;
	}

	matrix img = makeVerticalGradient();
	savePAM(argv[1], img);

	return 0;
}