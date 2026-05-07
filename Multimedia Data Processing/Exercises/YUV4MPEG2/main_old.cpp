#include <cstdint>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
using mat = std::vector<std::vector<T>>;

struct y4m_header {
	int w, h;
	std::string c;
	char i;
	int fn, fd;
	int an, ad;
	std::string x;
};

bool y4m_extract_header(std::ifstream& is, y4m_header& header) {
	if (!is) {
		return false;
	}

	std::string line;
	std::getline(is, line);

	std::stringstream ss(line);

	std::string token;
	ss >> token;
	if (token != "YUV4MPEG2") {
		return false;
	}

	while (ss >> token) {
		switch (token.c_str()[0]) {
			case 'H':
				header.h = std::stoi(token.substr(1));
				break;
			case 'W':
				header.w = std::stoi(token.substr(1));
				break;
			case 'C':
				header.c = token.substr(1);
				break;
			case 'I':
				header.i = token.c_str()[1];
				break;
			case 'F':
				int del = token.find(':');
				header.fn = std::stoi(token.substr(1, del));
				header.fd = std::stoi(token.substr(del));
				break;
			case 'A':
				int del = token.find(':');
				header.an = std::stoi(token.substr(1, del));
				header.ad = std::stoi(token.substr(del));
				break;
			case 'X':
				header.x = token.substr(1);
				break;
			default:
				return false;
				break;
		}
	}

	if (header.c != "C420jpeg") {
		return false;
	}
	if (header.i != 'p') {
		return false;
	}

	return true;
}

/**
 * Ignores header fields
 */
bool y4m_extract_frames(std::ifstream& is,
						std::vector<std::vector<uint8_t>> frames) {
	std::string line;
	std::getline(is, line);

	if (line.substr(0, 5) != "FRAME") {
		return false;
	}

	while (std::getline(is, line)) {
		std::stringstream ss(line);
		std::vector<uint8_t> frame;
		uint8_t val;
		while (ss >> val) {
			frame.push_back(val);
		}
		frames.push_back(frame);
	}

	return true;
}

/**
 * The function must load a file in YUV4MPEG2 format and save the Y planes of
 * all frames in the grayscale image vector frames. The program should only
 * support C420jpeg encoding with progressive interlacing (i.e. no interlacing)
 * and ignore frame rate, aspect ratio or other parameters. In case of an error
 * it must end with false. If the loading of the YUV4MPEG2 stream is successful
 * the function must terminate by returning true.
 */
bool y4m_extract_gray(const std::string& filename,
					  std::vector<mat<uint8_t>>& frames) {
	std::ifstream is(filename, std::ios::binary);
	if (!is) {
		return false;
	}

	y4m_header header;
	if (!y4m_extract_header(is, header)) {
		return false;
	}

	std::vector<std::vector<uint8_t>> extracted;
	if (!y4m_extract_frames(is, extracted)) {
		return false;
	}

	if (!frames.empty()) {
		return false;
	}

	for (auto& frame : extracted) {
		mat<uint8_t> yframe;

		int ycount = 0;	 // Counter used to skip the Cb and Cr values
		int vcount = 0;	 // Counter used to go to a new line
		std::unique_ptr<std::vector<uint8_t>> pvec =
			std::make_unique<std::vector<uint8_t>>();  // Pointer to the current
													   // matrix frame line
		for (size_t i = 0; i < frame.size(); i++, ycount++) {
			if (ycount == 4) {
				ycount = -2;
				continue;
			}
			if (ycount < 0) {
				continue;
			}

			if ((*pvec).size() == header.w) {
				yframe.emplace_back(pvec);
				pvec = std::make_unique<std::vector<uint8_t>>();
			}

			(*pvec).push_back(frame[i]);
		}

		if (yframe.size() != header.h) {
			return false;
		}

		frames.push_back(yframe);
	}

	return true;
}

int main(int argc, char const* argv[]) {
	return 0;
}
