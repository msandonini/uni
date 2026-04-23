#include <cassert>
#include <fstream>
#include <print>
#include <vector>

struct Image {
	std::vector<uint8_t> img_;
	unsigned int w_, h_;

	Image() {}
	Image(int w, int h) : w_(w), h_(h), img_(w * h) {}

	auto width() const { return w_; }
	auto height() const { return h_; }
	auto size() const { return w_ * h_; }
	auto data() const { return img_; }

	const char* rawdata() const {
		return reinterpret_cast<const char*>(img_.data());
	}

	const uint8_t& at(unsigned int x, unsigned int y) const {
		/*
		assert(0 <= x <= w_ && 0 <= y <= h_);
		return img_[y * w_ + x];
		*/
		return this->at(x, y);
	}

	uint8_t& at(unsigned int x, unsigned int y) {
		/*
		return const_cast<uint8_t&>(
			static_cast<const Image*>(this)->at(x, y)
		);
		*/

		assert(0 <= x <= w_ && 0 <= y <= h_);
		return img_[y * w_ + x];
	}

	uint8_t& operator[](unsigned int x, unsigned int y) {
		return this->at(x, y);
	}

	const uint8_t& operator[](unsigned int x, unsigned int y) const {
		return this->at(x, y);
	}
};

int savePAM(char const* fpath, const Image& img) {
	using std::print;

	std::ofstream os(fpath, std::ios::binary);

	if (!os) {
		std::println("Error! Unable to open the image.");
		return 1;
	}

	os << "P7" << "\n";
	os << "WIDTH " << img.width() << "\n";
	os << "HEIGHT " << img.height() << "\n";
	os << "DEPTH 3" << "\n";
	os << "MAXVAL 255" << "\n";
	os << "TUPLTYPE RGB" << "\n";
	os << "ENDHDR" << "\n";

	/*
	for (size_t i = 0; i < 256; i++) {
		for (size_t j = 0; j < 256; j++) {
			os.put(img[i, j]);
		}
	}
	*/

	os.write(img.rawdata(), img.size());

	os.close();

	return 0;
}

int main(int argc, char const* argv[]) {
	if (argc != 2) {
		std::println("Error! Wrong number of arguments.");
		return 1;
	}

	Image img(256, 256);
	for (size_t i = 0; i < 256; i++) {
		for (size_t j = 0; j < 256; j++) {
			img[i, j] = (uint8_t)i;
		}
	}

	return savePAM(argv[1], img);
}
