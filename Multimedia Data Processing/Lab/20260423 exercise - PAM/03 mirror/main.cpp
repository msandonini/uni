#include <array>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
struct matrix {
	int rows_, cols_;
	std::vector<T> data_;

	matrix() {}
	matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(rows * cols) {}

	const T& operator()(int r, int c) const {
		assert(0 <= r && r < rows_ && 0 <= c && c < cols_);
		return data_[r * cols_ + c];
	}
	T& operator()(int r, int c) {
		return const_cast<T&>(
			static_cast<const matrix*>(this)->operator()(r, c));
	}

	auto empty() const { return data_.empty(); }

	auto rows() const { return rows_; }
	auto cols() const { return cols_; }
	auto data() const { return data_; }
	auto size() const { return data_.size(); }

	void resize(h, w) {
		//*this =
	}

	const char* rawdata() const {
		return reinterpret_cast<const char*>(data_.data());
	}
	char* rawdata() { return reinterpret_cast<char*>(data_.data()); }

	size_t rawsize() const { return size() * sizeof(T); }
};

using rgb = std::array<uint8_t, 3>;
matrix<rgb> loadPAM_rgb(const std::string& filename) {
	std::ifstream is(filename, std::ios::binary);

	matrix<rgb> img;
	if (!is) {
		return img;
	}

	std::string token;
	is >> token;
	if (token != "P7") {
		return img;
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

	if (w < 0 || h < 0 || depth != 1 || maxval != 255 || type != "GRAYSCALE") {
		return img;
	}

	img = matrix<rgb>(h, w);

	if (!is.read(img.rawdata(), img.size())) {
		img = matrix<rgb>();
	}

	return img;
}

bool savePAM_gs(const std::string& filename, const matrix<uint8_t>& img) {
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

	os.write(img.rawdata(), img.rawsize());
	return true;
}
bool savePAM_rgb(const std::string& filename, const matrix<rgb>& img) {
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
	os.write(img.rawdata(), img.rawsize());
	return true;
}

auto makeVerticalGradient() {
	matrix<uint8_t> img(256, 256);
	for (int r = 0; r < img.rows(); ++r) {
		for (int c = 0; c < img.cols(); ++c) {
			img(r, c) = static_cast<uint8_t>(r);
		}
	}
	return img;
}

template <typename T>
void flip(matrix<T>& mat) {
	for (size_t i = 0; i < mat.rows() / 2; i++) {
		for (size_t j = 0; j < mat.cols(); j++) {
			std::swap(mat(i, j), mat(mat.rows() - i - 1, j));
		}
	}
}

template <typename T>
void mirror(matrix<T>& mat) {
	for (size_t i = 0; i < mat.rows(); i++) {
		for (size_t j = 0; j < mat.cols() / 2; j++) {
			std::swap(mat(i, j), mat(i, mat.cols() - j - 1));
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		return 1;
	}

	matrix img = loadPAM_rgb(argv[1]);

	if (img.empty()) {
		return 1;
	}

	flip(img);

	savePAM_rgb(argv[2], img);

	return 0;
}