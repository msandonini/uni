#include <array>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// STEP 1: Define type as enum in order to have it at compile time
// Enum classes are scoped (they need to have the type of the class specified)
enum class pixel_type { grayscale = 1, rgb = 3 };
// END STEP 1

struct matrix {
	pixel_type type_;
	int rows_, cols_;
	std::vector<uint8_t> data_;

	// STEP 2: Apply improvement to constructor
	matrix() {}
	matrix(pixel_type type, int rows, int cols)
		: type_(type), rows_(rows), cols_(cols) {
		if (type == pixel_type::rgb) {
			data_.resize(rows * cols * 3);
		} else if (type == pixel_type::grayscale) {
			data_.resize(rows_ * cols_ * 1);
		} else {
			// We throw an exception if no known type is set
			throw std::runtime_error("No known pixel type has been specified.");
		}
	}
	// END STEP 2

	// STEP 3: Fix the error
	/*
	const T& operator()(int r, int c) const {
		assert(0 <= r && r < rows_ && 0 <= c && c < cols_);
		return data_[r * cols_ + c];
	}
	T& operator()(int r, int c) {
		return const_cast<T&>(
			static_cast<const matrix*>(this)->operator()(r, c));
	}
	*/
	template <typename T>
	const T& at(int r, int c) const {
		assert(0 <= r && r < rows_ && 0 <= c && c < cols_);
		if (type == pixel_type::rgb) {
			return *reinterpret_cast<rgb*>(&data_[(r * cols_ + c) * 3]);
		} else if (type == pixel_type::grayscale) {
			return data_[r * cols_ + c]);
		}
	}
	template <typename T>
	T& at(int r, int c) {
		return const_cast<T&>(
			static_cast<const matrix*>(this)->operator()(r, c));
	}
	// END STEP 3

	auto empty() const { return data_.empty(); }

	auto type() const { return type_; }
	auto rows() const { return rows_; }
	auto cols() const { return cols_; }
	auto data() const { return data_; }
	auto size() const { return rows_ * cols_; }

	const char* rawdata() const {
		return reinterpret_cast<const char*>(data_.data());
	}
	char* rawdata() { return reinterpret_cast<char*>(data_.data()); }

	size_t rawsize() const { return size(); }
};

// STEP 4: Unified load function
using rgb = std::array<uint8_t, 3>;
matrix loadPAM(const std::string& filename) {
	std::ifstream is(filename, std::ios::binary);

	matrix img;
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

	if (w < 0 || h < 0 || maxval != 255 ||
		(type != "GRAYSCALE" && type != "RGB")) {
		return img;
	}

	if (type == "RGB") {
		if (depth != 3) {
			return img;
		}

		img = matrix(pixel_type::rgb, h, w);
	} else if (type == "GRAYSCALE") {
		if (depth != 1) {
			return img;
		}

		img = matrix(pixel_type::grayscale, h, w);
	}

	return img;
}
// END STEP 4

// STEP 5: Unified saving
/*
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
	os.write(img.rawdata(), img.rawsize());
	return true;
}
*/
bool savePAM(const std::string& filename, const matrix& img) {
	std::ofstream os(filename, std::ios::binary);
	if (!os) {
		return false;
	}
	os << "P7\n"
	   << "WIDTH " << img.cols() << "\n"
	   << "HEIGHT " << img.rows() << "\n"
	   << "MAXVAL 255\n";
	if (img.type() == pixel_type::rgb) {
		os << "DEPTH 3\n"
		   << "TUPLTYPE RGB\n";
	} else if (img.type() == pixel_type::grayscale) {
		os << "DEPTH 1\n"
		   << "TUPLTYPE GRAYSCALE";
	}
	os << "ENDHDR\n";

	os.write(img.rawdata(), img.rawsize());
	return true;
}
// END STEP 5

// STEP 6: Fix the functions
auto makeVerticalGradient() {
	matrix img(pixel_type::grayscale, 256, 256);
	for (int r = 0; r < img.rows(); ++r) {
		for (int c = 0; c < img.cols(); ++c) {
			img.at<uint8_t>(r, c) = static_cast<uint8_t>(r);
		}
	}
	return img;
}

template <typename T>
void flip_impl(matrix& mat) {
	for (size_t i = 0; i < mat.rows() / 2; i++) {
		for (size_t j = 0; j < mat.cols(); j++) {
			std::swap(mat.at<T>(i, j), mat.at<T>(mat.rows() - i - 1, j));
		}
	}
}

template <typename T>
void mirror_impl(matrix& mat) {
	for (size_t i = 0; i < mat.rows(); i++) {
		for (size_t j = 0; j < mat.cols() / 2; j++) {
			std::swap(mat.at<T>(i, j), mat.at<T>(i, mat.cols() - j - 1));
		}
	}
}

// The previous templated functions should work, but they still need the usage
// of compile-time types (the templates). To fix this we need to use runtime
// versions of the images

void flip(matrix& img) {
	if (img.type() == pixel_type::rgb) {
		flip_impl<rgb>(img);
	} else if (img.type() == pixel_type::grayscale) {
		flip_impl<uint8_t>(img);
	}
}

void mirror(matrix& img) {
	if (img.type() == pixel_type::rgb) {
		mirror_impl<rgb>(img);
	} else if (img.type() == pixel_type::grayscale) {
		mirror_impl<uint8_t>(img);
	}
}

// This works, but it definitely is not scalable.
// To fix the scalability issue we could use a dictionary of types and lambda
// functions associated with that function, or maybe use a decorator if we were
// in Python. Since we are in C++ and we have OOP we can use inheeritance and
// polymorphism to create multiple classes with different types in the hierarchy
// and then switch between them

// END STEP 6

int main(int argc, char* argv[]) {
	if (argc != 3) {
		return 1;
	}

	matrix img = loadPAM(argv[1]);

	if (img.empty()) {
		return 1;
	}

	flip(img);
	mirror(img);

	savePAM(argv[2], img);

	return 0;
}